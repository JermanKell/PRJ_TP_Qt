#ifndef DEF_GESTION_CLIENT_H
#define	DEF_GESTION_CLIENT_H

#include"Modele/RendezVous.h"
#include "Modele/client.h"
#include "Controleur/Gestion_Creneau.h"
#include<vector>

using namespace std;

class Gestion_Client {
private:
    vector<Client> * vecClient;
    vector<Client>::iterator itPrio;

    vector<RendezVous*> RDVector;
    vector<RendezVous*>::iterator RDVecIterator;

    Creneau gCreneau;

	void TriParPrio(void);

public:
    Gestion_Client(vector<Client> * vecteur);
    ~Gestion_Client();

    void AjouterClient(Client client);
    vector<Client> *getVectorClient(void);

	void ProgRDV(void);
    void StockageRDVsurBD();
};

#endif // !DEF_GESTION_CLIENT_H
