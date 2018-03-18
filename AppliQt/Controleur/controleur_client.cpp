#include "controleur_client.h"

Controleur_Client::Controleur_Client()
{
    query = QSqlQuery(*(Controller_BD::getInstance()->getBD()));
}

bool Controleur_Client::ClientExiste(Client & cl) {
    bool bresult;

    query.prepare("SELECT Nom, Prenom FROM TClient WHERE Nom LIKE :nom AND Prenom LIKE :prenom");
    query.bindValue(":nom", cl.getNom());
    query.bindValue(":prenom", cl.getPrenom());

    if(!query.exec()) {
        qDebug() << query.lastError();
    }

    if (query.next()) {
        bresult = true;
    }
    return bresult;
}

bool Controleur_Client::AjouterClient(Client & cl) {
    query.prepare("INSERT INTO TClient (Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateRdv, DureeRdv, Priorite) "
                  "VALUES (:nom, :prenom, :adresse, :ville, :cp, :comm, :tel, :date, :duree, :prio)");
    query.bindValue(":nom", cl.getNom());
    query.bindValue(":prenom", cl.getPrenom());
    query.bindValue(":adresse", cl.getAdresse());
    query.bindValue(":ville", cl.getVille());
    query.bindValue(":cp", cl.getCP());
    query.bindValue(":comm", cl.getCommentaires());
    query.bindValue(":tel", cl.getTelephone());
    query.bindValue(":date", cl.getDateRDV());
    query.bindValue(":duree", cl.getDureeRDV());
    query.bindValue(":prio", cl.getPriorite());
    if(!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool Controleur_Client::AjouterRDVClient(int idClient, int idRessource) {
    query.prepare("INSERT INTO TRdv (IdClient, IdRessource) "
                  "VALUES (:idC, :idR)");
    query.bindValue(":idC", idClient);
    query.bindValue(":idR", idRessource);

    if(!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool Controleur_Client::SupprimerRDVClient(int idClient) {
    query.prepare("DELETE FROM TRdv WHERE IdClient = :idC");
    query.bindValue(":idC", idClient);

    if(!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
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
                     query.value(6).toString(),
                     query.value(7).toInt());
       client.setId(query.value(0).toInt());
       client.setIdRessources(vecId);
        vecClient->push_back(client);
    }
    return vecClient;
}

int Controleur_Client::NbClient() {
    if(!query.exec("SELECT COUNT(*) FROM TClient")) {
        qDebug() << query.lastError().text();
    }
    if(query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int Controleur_Client::MaxIdClient() {
    if(!query.exec("SELECT MAX(Id) FROM TClient")) {
        qDebug() << query.lastError().text();
    }
    if(query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}
Controleur_Client::~Controleur_Client() {

}

