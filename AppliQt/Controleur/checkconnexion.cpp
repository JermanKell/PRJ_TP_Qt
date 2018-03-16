#include "checkconnexion.h"

using namespace std;

CheckConnexion::CheckConnexion() {

}

CheckConnexion::~CheckConnexion() {

}

bool CheckConnexion::CheckCoUser(QString Id, QString mdp) {
    bool var = false;

    QSqlQuery query = QSqlQuery(*(Controller_BD::getInstance()->getBD()));

    query.prepare("SELECT Login, MdP FROM TCompte WHERE Login LIKE :Id AND MdP LIKE :mdp");
    query.bindValue(":Id", Id);
    query.bindValue(":mdp", mdp);
    var = query.exec();

    while (query.next())
        cout << "Connexion réussie, connexion à l'application principale en cours ..." << endl;

    return var;
}
