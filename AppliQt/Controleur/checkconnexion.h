#ifndef CHECKCONNEXION_H
#define CHECKCONNEXION_H

#include<qstring.h>

class CheckConnexion
{
private:

public:
    CheckConnexion();
    ~CheckConnexion();
    static bool CheckCoUser(QString Id, QString MDP, QString RefId, QString RefMdP);
};

#endif // CHECKCONNEXION_H
