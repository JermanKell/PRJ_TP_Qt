#ifndef CHECKCONNEXION_H
#define CHECKCONNEXION_H

#include<qstring.h>
#include <stdio.h>
#include "QSqlQuery"
#include "QVariant"
#include <QSqlDatabase>
#include "controleur_BD.h"

class CheckConnexion
{
private:

public:
    CheckConnexion();
    ~CheckConnexion();
    static bool CheckCoUser(QString Id, QString MDP);
};

#endif // CHECKCONNEXION_H
