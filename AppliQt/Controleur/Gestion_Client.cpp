#include "Gestion_Client.h"
#include "FoncteurTrieRessource.h"
#include "Modele/client.h"
#include <iostream>
#include <algorithm>

using namespace std;


Gestion_Client::Gestion_Client(vector<Client> * vecteur) {
    gCreneau = Creneau();
    vecClient = vecteur;

}
Gestion_Client::~Gestion_Client() {
    for (RDVecIterator = RDVector.begin(); RDVecIterator != RDVector.end(); RDVecIterator++) {
        delete *RDVecIterator;
        RDVector.erase(RDVecIterator);
    }
    delete vecClient;
}

void Gestion_Client::AjouterClient(Client client) {
    vecClient->push_back(client);
}

/*
	Utilisation d'un foncteur pour ordonnancer la liste de Patient
*/
void Gestion_Client::TriParPrio(void) {
    sort(vecClient->begin(), vecClient->end(), FoncteurSortResource());
}

void Gestion_Client::ProgRDV(void) {
	TriParPrio();
    RendezVous * rdv;

    unsigned int uiBoucle;
    unsigned int uiVar;
    for (uiBoucle = 0; uiBoucle < vecClient->size(); uiBoucle++) {
        Client client = vecClient->at(uiBoucle);
        vector<int> RessourceId = client.getIdRessources();
        for (uiVar = 0; uiVar < RessourceId.size(); uiVar++) {
            rdv = gCreneau.OrdoRDV(&client, RessourceId.at(uiVar), (client.getDureeRDV()/RessourceId.size())); // Comment récupérer l'id du personnel en passant par un objet client
            if (rdv != nullptr)  RDVector.push_back(rdv);
        }

	}
}

vector<Client> * Gestion_Client::getVectorClient(void) {
    return vecClient;
}

void Gestion_Client::StockageRDVsurBD() {
    // Faire les requetes vers la base de donnée pour les stocker
}
