#ifndef DBMANAGER_CLIENT_H
#define DBMANAGER_CLIENT_H

#include "Modele/client.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include "dbconnexion.h"
#include <map>

class DBManager_Client
{
private:
    QSqlQuery query;

public:
    DBManager_Client();
    ~DBManager_Client();

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

#endif // DBMANAGER_CLIENT_H
