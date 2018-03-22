#ifndef DBMANAGER_IDENTIFICATION_H
#define DBMANAGER_IDENTIFICATION_H

#include<qstring.h>
#include <stdio.h>
#include "QSqlQuery"
#include "QVariant"
#include <QSqlDatabase>
#include "dbconnexion.h"

class DBManager_Identification
{
private:

public:
    DBManager_Identification();
    ~DBManager_Identification();
    bool VerifierConnexion(QString Id, QString MDP);
};

#endif // DBMANAGER_IDENTIFICATION_H
