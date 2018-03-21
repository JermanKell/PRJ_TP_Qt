#include "controleur_client.h"

Controleur_Client::Controleur_Client()
{
    query = QSqlQuery(*(Controller_BD::getInstance()->getBD()));
}

bool Controleur_Client::ClientExiste(Client & cl) {
    bool bresult = false;;

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

bool Controleur_Client::ModifierClient(Client & cl) {
    query.prepare("UPDATE TClient SET nom = :nom, "
                   "prenom = :prenom, "
                   "adresse = :adresse, "
                   "ville = :ville, "
                   "cp = :cp, "
                   "commentaire = :commentaires, "
                   "tel = :tel, "
                   "dateRdv = :date, "
                   "dureeRdv = :duree,"
                   "priorite = :priorite "
                   "WHERE id = :id");
    query.bindValue(":nom", cl.getNom());
    query.bindValue(":prenom", cl.getPrenom());
    query.bindValue(":adresse", cl.getAdresse());
    query.bindValue(":ville", cl.getVille());
    query.bindValue(":cp", cl.getCP());
    query.bindValue(":commentaires", cl.getCommentaires());
    query.bindValue(":tel", cl.getTelephone());
    query.bindValue(":date", cl.getDateRDV());
    query.bindValue(":duree", cl.getDureeRDV());
    query.bindValue(":priorite", cl.getPriorite());
    query.bindValue(":id", cl.getId());
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

map<int, Client*>* Controleur_Client::GetListeClient() {
    if(!query.exec("SELECT * FROM TClient")) {
        qDebug() << query.lastError().text();
    }
    map<int, Client*>* mapClient = new map<int, Client*>();
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

       Client *client = new Client(
                     query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(),
                     query.value(5).toInt(),
                     query.value(8).toString(),
                     query.value(9).toInt(),query.value(10).toInt(),
                     query.value(6).toString(),
                     query.value(7).toInt());
       client->setId(query.value(0).toInt());
       client->setIdRessources(vecId);
       mapClient->insert(std::make_pair(client->getId(),client));
    }
    return mapClient;
}

Client* Controleur_Client::GetClient(int idClient) {
    query.prepare("SELECT * FROM TClient WHERE Id = :id");
    query.bindValue(":id", idClient);

    if(!query.exec()) {
        qDebug() << query.lastError();
    }
    if (query.next()) {
        Client *client = new Client(query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(),
                                    query.value(5).toInt(),
                                    query.value(8).toString(),
                                    query.value(9).toInt(),query.value(10).toInt(),
                                    query.value(6).toString(),
                                    query.value(7).toInt());
       client->setId(query.value(0).toInt());
       return client;
    }
    return nullptr;
}

vector<int>* Controleur_Client::GetListeIdRessourcesClient(int idClient) {
    query.prepare("SELECT IdRessource FROM TRdv WHERE IdClient = :idC");
    query.bindValue(":idC", idClient);

    if(!query.exec()) {
        qDebug() << query.lastError();
    }
    vector<int> *vecIdRessources = new vector<int>();
    while (query.next()) {
        vecIdRessources->push_back(query.value(0).toInt());
    }
    return vecIdRessources;
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

QSqlTableModel* Controleur_Client::RechercheClient(int id, QString nom, QString prenom, QString dateDebut, QString dateFin) {
      QSqlTableModel * model = new QSqlTableModel(NULL, *Controller_BD::getInstance()->getBD());
      model->setTable("TClient");
      model->select();
      if(nom.count() != 0) {
          nom = nom.append('%');
      }
      if(prenom.count() != 0) {
          prenom = prenom.append('%');
      }

     model->setFilter(QString("id = "+ QString::number(id) +
                               " OR nom LIKE '"+ nom +
                               "' OR prenom LIKE '"+ prenom +
                               "' OR dateRdv BETWEEN '"+ dateDebut +"' and '"+ dateFin +"'"));
      return model;
}

QString Controleur_Client::DateMinimum() {
    if(!query.exec("SELECT MIN(DateRdv) FROM TClient")) {
        qDebug() << query.lastError().text();
    }
    query.next();
    return query.value(0).toString();
}

QString Controleur_Client::DateMaximum() {
    if(!query.exec("SELECT MAX(DateRdv) FROM TClient")) {
        qDebug() << query.lastError().text();
    }
    query.next();
    return query.value(0).toString();
}

Controleur_Client::~Controleur_Client() {

}

