#include "dbmanager_identification.h"

using namespace std;

DBManager_Identification::DBManager_Identification() {

}

DBManager_Identification::~DBManager_Identification() {

}

bool DBManager_Identification::VerifierConnexion(QString Id, QString mdp) {
    bool bresult = false;

    QSqlQuery query = QSqlQuery(*(DBConnexion::getInstance()->getBD()));

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
