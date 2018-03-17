#include "checkconnexion.h"

using namespace std;

CheckConnexion::CheckConnexion() {

}

CheckConnexion::~CheckConnexion() {

}

bool CheckConnexion::CheckCoUser(QString Id, QString mdp) {
    bool bresult = false;

    QSqlQuery query = QSqlQuery(*(Controller_BD::getInstance()->getBD()));

    query.prepare("SELECT Login, MdP FROM TCompte WHERE Login LIKE :Id AND MdP LIKE :mdp");
    query.bindValue(":Id", Id);
    query.bindValue(":mdp", mdp);

    if(!query.exec()) {
        qDebug() << query.lastError();
    }

    if (query.next()) {
        bresult = true;
    }
    return bresult;
}
