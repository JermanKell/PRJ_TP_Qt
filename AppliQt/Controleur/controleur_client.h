#ifndef CONTROLEUR_CLIENT_H
#define CONTROLEUR_CLIENT_H

#include "Modele/client.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include "controleur_BD.h"
#include <map>

class Controleur_Client
{
private:
    QSqlQuery query;

public:
    Controleur_Client();
    ~Controleur_Client();

    bool ClientExiste(Client * cl);
    bool AjouterClient(Client * cl);
    bool AjouterRDVClient(int idClient, int idRessource);
    bool SupprimerRDVClient(int idClient);
    bool ModifierClient(Client * cl);

    bool SupprimerClient();
    map<int, Client*>* GetListeClient();
    Client* GetClient(int idClient);
    Client* GetClientFromName(QString nom, QString prenom);
    vector<int>* GetListeIdRessourcesClient(int idClient);
    int NbClient();
    int MaxIdClient();
    QSqlTableModel* RechercheClient(int id, QString nom, QString prenom, QString dateDebut, QString dateFin);
    QString DateMinimum();
    QString DateMaximum();
};

#endif // CONTROLEUR_CLIENT_H
