#ifndef DBMANAGER_IDENTIFICATION_H
#define DBMANAGER_IDENTIFICATION_H

#include<qstring.h>
#include <stdio.h>
#include "QSqlQuery"
#include <QSqlDatabase>
#include "dbconnexion.h"

//Classe interagissant avec la table TCompte
class DBManager_Identification
{
private:

public:
    DBManager_Identification();
    ~DBManager_Identification();

    /* Retourne vrai si une ligne contient le même login et mot de passe que les paramètres */
    bool VerifierConnexion(QString Id, QString MDP);
};

#endif // DBMANAGER_IDENTIFICATION_H
