#ifndef DEF_CRENEAU_H
#define DEF_CRENEAU_H

#include<map>
#include "QMultiMap"
#include<iostream>
#include"Modele/client.h"
#include"Modele/RendezVous.h"
#include"GestionTemps_Planif.h"

using namespace std;

class Creneau {
private:	
	/*
		1er int: idRessource
		2eme : duree RDV en fonction du precedent
		3eme: heure debut
	*/
    QMultiMap<int, QMultiMap<int, int>> stockRDV;
    QMultiMap<int, QMultiMap<int, int>>::iterator itMap;

	/*
		Multimap des RDV possibles par ressource
			=> Tableau secondaire (que pour une methode)
	*/
    QMultiMap<int, int> tableau;

	/*
		Multimap de taille NbPatients, repertoriant les 
		dernieres dates horaires de RDV par patient
	*/
    QMultiMap<int, int> lastHClient;

    QMultiMap<int, int>::iterator itTab;
	multimap<int, int>::iterator itRefPVal;
	TimeHandler gestion;

	int	rdvDur;
    int rdvDeb;

    inline QMultiMap<int, int>::iterator LastHRDVClient(int idRes) {
        itTab = lastHClient.find(idRes);
        return itTab;
    }

    inline void UpdateHRDVClient(int idRes, int time) {
        itTab = lastHClient.find(idRes);
        itTab.value() = time;
	}

    void TrouverHoraireRDV(int idRes, int duree, int idClient);

public:
	Creneau();
	~Creneau();

	void setTimeHandler(TimeHandler & time);

    RendezVous * OrdoRDV(Client * client, int IdRes, int dureeParClient);
};

#endif // !DEF_CRENEAU_H
