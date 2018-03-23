#include"Gestion_Creneau.h"
#include <QDebug>

Creneau::Creneau() {
	rdvDur = 0;
	rdvDeb = 0;
	gestion = TimeHandler();
}

Creneau::~Creneau() {

}

void Creneau::setTimeHandler(TimeHandler & time)	{
    gestion = time;
}

void Creneau::TrouverHoraireRDV(int idRes, int duree, int idClient) {
    bool var = true;
    QMultiMap<int, int> coucou;
    QMultiMap<int, int>::iterator iterator;
    int ecart;
    int lastHRdv;

    iterator = LastHRDVClient(idClient);
    if (iterator == lastHClient.end()) {
        lastHClient.insert(idClient, 0);
        iterator = LastHRDVClient(idClient);
        lastHRdv = iterator.value();
    }

    itMap = stockRDV.find(idRes);
    if (itMap == stockRDV.end())
        stockRDV.insert(idRes, coucou);

    tableau = itMap.value();
    itTab = tableau.begin();

    // Quand il n'y a rien dans le tableau, creation 1er RDV

    if (itTab++ == tableau.end()) {
        tableau.insert(800, 1000);
    }

    // Quand le tableau contient au moins 2 RDV
    while (var && (itTab != tableau.end())) {
        if (gestion.EndDateRDV(itTab.key(), itTab.value()) > gestion.EndDateRDV(lastHRdv, duree)) {
            if (lastHRdv == 0) {
                rdvDur = duree;
                rdvDeb = itTab.key();
                tableau.replace(itTab.key(), gestion.DecalRDVSup(gestion.EndDateRDV(rdvDeb, duree)));
                itTab = tableau.begin();
                var = false;        // Ce créneau est selectionne pour devenir le futur RDV
            }
            else {
                rdvDur = duree;
                rdvDeb = lastHRdv;

                var = false;    // Ce créneau est selectionne pour devenir le futur RDV

                if (lastHRdv > itTab.key()) {
                    if (itTab.value() == 1000) {
                        tableau.insert(gestion.DecalRDVSup(gestion.EndDateRDV(lastHRdv, duree)), 1000);
                    }
                    else {
                        ecart = gestion.CalculEcart(gestion.DecalRDVSup(gestion.EndDateRDV(lastHRdv, duree)+2), gestion.DecalRDVSup(gestion.EndDateRDV(itTab.key(), duree)));
                        if (ecart > 10) tableau.insert(gestion.DecalRDVSup(gestion.EndDateRDV(lastHRdv, duree)+2), ecart);

                        ecart = gestion.CalculEcart(itTab.key(), lastHRdv);
                        if (ecart-2 > 10)   tableau.replace(itTab.key(), ecart - 2);  // On modifie la duree du nouveau creneau possible
                        else {
                            int key = itTab.key();
                            itTab = tableau.begin();
                            tableau.remove(key);
                        }
                    }
                }
            }
        }

        if ((itTab.key() >= lastHRdv) && (itTab.value() >= duree)) {
            rdvDur = duree;
            rdvDeb = itTab.key();

            int nvlVal;
            int nvlCle;

            if (itTab.value() == 1000)  nvlVal = 1000;
            else nvlVal = itTab.value() - (duree + gestion.CalculEcart(gestion.EndDateRDV(lastHRdv, duree), gestion.DecalRDVSup(gestion.EndDateRDV(lastHRdv, duree))));

            nvlCle = gestion.DecalRDVSup(gestion.EndDateRDV(lastHRdv, duree));

            int key = itTab.key();
            itTab = tableau.begin();
            tableau.remove(key);

            tableau.insert(nvlCle, nvlVal);

            var = false;
        }
        else itTab++;
    }

    if (!var)
        qDebug() << "Aucun rendez-vous n'a pu etre pris pour ce client" << endl;
}

RendezVous * Creneau::OrdoRDV(Client * client, int IdRes, int dureeParClient) {
    RendezVous * rdv;

    TrouverHoraireRDV(IdRes, dureeParClient, client->getId());
    if ((rdvDur == 0) && (rdvDeb == 0)) qDebug() << "Un creneau pour un rendez vous n'a pu etre trouve" << endl;
    else {
        rdv = new RendezVous(IdRes, client->getId());
    }

    return rdv;
    delete rdv;
}
