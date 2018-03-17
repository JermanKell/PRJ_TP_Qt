#include "controleur_client.h"

Controleur_Client::Controleur_Client()
{
    query = QSqlQuery(*(Controller_BD::getInstance()->getBD()));
}

vector<Client>* Controleur_Client::GetListeClient() {
    if(!query.exec("SELECT * FROM TClient")) {
        qDebug() << query.lastError().text();
    }
    vector<Client>* vecClient = new vector<Client>();
    while (query.next()) {
        vector<int> vecId;
        int idClient = query.value(0).toInt();

        QSqlQuery queryRessources = QSqlQuery(*(Controller_BD::getInstance()->getBD()));
        queryRessources.prepare("SELECT * FROM TRdv WHERE IdClient = :IdClient");
        queryRessources.bindValue(":IdClient", idClient);
        if(!queryRessources.exec()) {
            qDebug() << query.lastError().text();
        }

        while (queryRessources.next()) {
            vecId.push_back(queryRessources.value(2).toInt());
        }

       Client client(query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(),
                     query.value(5).toInt(),
                     query.value(8).toString(),
                     query.value(9).toInt(),query.value(10).toInt(),
                     vecId,
                     query.value(6).toString(),
                     query.value(7).toInt());
       client.setId(query.value(0).toInt());
        vecClient->push_back(client);
    }
    return vecClient;
}

Controleur_Client::~Controleur_Client() {

}

