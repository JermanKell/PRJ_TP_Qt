#ifndef DBMANAGER_CLIENT_H
#define DBMANAGER_CLIENT_H

#include "Modele/client.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include "dbconnexion.h"
#include <map>

//Classe interagissant avec les clients de la base
class DBManager_Client
{
private:
    QSqlQuery query;

public:
    DBManager_Client();
    ~DBManager_Client();

    /* Vérifie si un client portant le même nom et prénom existe déja dans la base */
    bool ClientExiste(Client * cl);

    /* Ajoute un client à la base */
    bool AjouterClient(Client * cl);

    /* Ajoute un RDV à la base depuis les ids du client et du personnel */
    bool AjouterRDVClient(int idClient, int idRessource);

    /* Supprime un client de la base depuis son id */
    bool SupprimerRDVClient(int idClient);

    /* Modifie les données d'un client à partir d'un id */
    bool ModifierClient(Client * cl);

    /* Retourne une map de clients avec l'ensemble de leurs ressources associées (id) */
    map<int, Client*>* GetListeClient();

    /* Retourne un client depuis son id */
    Client* GetClient(int idClient);

    /* Retourne un client depuis son nom et prenom */
    Client* GetClientFromName(QString nom, QString prenom);

    /* Retourne toutes les ressources d'un client depuis son id */
    vector<int>* GetListeIdRessourcesClient(int idClient);

    /* Retourne le nombre de client */
    int NbClient();

    /* Retourne l'identifiant client le plus élevé, le dernier ajouté à la base */
    int MaxIdClient();

    /* Retourne un model de la table client contenant l'un des champs en paramètres. Pour les paramètres dates on prend l'intervalle */
    QSqlTableModel* RechercheClient(int id, QString nom, QString prenom, QString dateDebut, QString dateFin);

    /* Retourne la date la plus ancienne d'un RDV parmis tous les clients */
    QString DateMinimum();

    /* Retourne la date la plus avancée d'un RDV parmis tous les clients */
    QString DateMaximum();
};

#endif // DBMANAGER_CLIENT_H
