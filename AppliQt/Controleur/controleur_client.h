#ifndef CONTROLEUR_CLIENT_H
#define CONTROLEUR_CLIENT_H

#include "Modele/client.h"
#include <qstring.h>
#include <QVariant>
#include <QSqlQuery>
#include "controleur_BD.h"

class Controleur_Client
{
private:
    QSqlQuery query;

public:
    Controleur_Client();
    ~Controleur_Client();

    bool ClientExiste(Client & cl);
    bool AjouterClient(Client & cl);
    bool AjouterRDVClient(int idClient, int idRessource);
    bool SupprimerRDVClient(int idClient);
    bool ModifierClient();
    bool SupprimerClient();
    vector<Client>* GetListeClient();
    Client* GetClient(int idClient);
    vector<int>* GetListeIdRessourcesClient(int idClient);
    int NbClient();
    int MaxIdClient();
};

#endif // CONTROLEUR_CLIENT_H
