#include "checkconnexion.h"

CheckConnexion::CheckConnexion()
{
}

CheckConnexion::~CheckConnexion() {

}

bool CheckConnexion::CheckCoUser(QString Id, QString mdp, QString RefId, QString RefMdP) {
    bool var;
    if ((Id.compare(RefId) == 0) && (mdp.compare(RefMdP) == 0))
        var = true;
    else var = false;
    return var;
}
