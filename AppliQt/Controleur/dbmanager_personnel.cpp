#include "dbmanager_personnel.h"

DBManager_Personnel::DBManager_Personnel()
{
    query = QSqlQuery(*(DBConnexion::getInstance()->getBD()));
}

DBManager_Personnel::~DBManager_Personnel() {

}

QList<QString>* DBManager_Personnel::RecupMetier() {
    QList<QString>* listMetier = new QList<QString>;
    bool var = query.exec("SELECT Label FROM TType ");
    if(!var)    qDebug() << query.lastError();
    while (query.next()) {
        listMetier->push_back(query.value(0).toString());
    }
    return listMetier;
}

int DBManager_Personnel::TravailVersInt(QString metier) {
    query.prepare("SELECT Id FROM TType WHERE Label = :metier");
    query.bindValue(":metier", metier);
    if(!query.exec())    qDebug() << query.lastError();
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QString DBManager_Personnel::IntVersTravail(int id) {
    query.prepare("SELECT Label FROM TType WHERE Id = :id");
    query.bindValue(":id", id);
    if(!query.exec())    qDebug() << query.lastError();
    if (query.next()) {
        return query.value(0).toString();
    }
    return QString("");
}

bool DBManager_Personnel::AjouterPersonnel(QString nom, QString prenom, QString travail, QString identifiant, QString mdp) {
    bool varRecherche;
    bool varIns = false;
    bool varInserCompte = false;

    int idRessource;

    int id = TravailVersInt(travail);
    Personnel pers = Personnel(nom, prenom, id);

    varRecherche = PersonneExiste(pers);

    if(!varRecherche) {
        query.prepare("INSERT INTO TRessource (Id, Nom, Prenom, IdType) " "VALUES (NULL, :nom, :prenom, :id)");
        query.bindValue(":nom", pers.getNom());
        query.bindValue(":prenom", pers.getPrenom());
        query.bindValue(":id", pers.getTypeMetier());
        varIns = query.exec();

        if (!varIns)
            qDebug() << query.lastError();

        if (QString::compare("Informaticien", travail, Qt::CaseInsensitive) == 0) {
            query.prepare("SELECT Id FROM TRessource WHERE Nom LIKE :nom AND Prenom LIKE :prenom AND IdType = :idtype");
            query.bindValue(":nom", pers.getNom());
            query.bindValue(":prenom", pers.getPrenom());
            query.bindValue(":idtype", pers.getTypeMetier());

            if (query.exec()) {
                query.next();
                idRessource = query.value(0).toInt();
            }

            query.prepare("INSERT INTO TCompte (Id, IdRessource, Login, MdP) VALUES(NULL, :idRes, :identifiant, :mdp)");
            query.bindValue(":idRes", idRessource);
            query.bindValue(":identifiant", identifiant);
            query.bindValue(":mdp", mdp);
            varInserCompte = query.exec();

            if (!varInserCompte)
                qDebug() << query.lastError();

            else {
                query.prepare("SELECT Login, MdP FROM TCompte WHERE IdRessource = :id");
                query.bindValue(":id", idRessource);
                if (query.exec()) {
                      query.next();
                      qDebug() << query.value(0) << query.value(1);
                 }
                 else qDebug() << query.lastError() << endl;
             }
         }
      }
    return varIns|varInserCompte;
}


bool DBManager_Personnel::ModifierPersonnel(QString nom, QString prenom, QString nvmetier, QString ancienMetier, QString identifiant, QString mdp, int idRessource) {
    bool varMAJ;
    bool varIns;    // Insertion
    bool varDelC; // Suppresion du compte si c'etait un administrateur
    int idNvmetier = TravailVersInt(nvmetier);

    query.prepare("UPDATE TRessource SET Nom = :nom, Prenom = :prenom, IdType = :idmet WHERE Id = :id");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":idmet", idNvmetier);
    query.bindValue(":id", idRessource);
    varMAJ = query.exec();

    if (!varMAJ)
        qDebug() << query.lastError() << endl;

    if (QString::compare("Informaticien", nvmetier, Qt::CaseInsensitive) == 0) {
        query.prepare("INSERT INTO TCompte (Id, IdRessource, Login, MdP) VALUES(NULL, :idRes, :identifiant, :mdp)");
        query.bindValue(":idRes", idRessource);
        query.bindValue(":identifiant", identifiant);
        query.bindValue(":mdp", mdp);
        varIns = query.exec();

        if (!varIns)
            qDebug() << query.lastError() << endl;
    }
    if (QString::compare("Informaticien", ancienMetier, Qt::CaseInsensitive) == 0)
    {
        query.prepare("DELETE FROM TCompte WHERE IdRessource = :idRes");
        query.bindValue(":idRes", idRessource);
        varDelC = query.exec();

        if (!varDelC)
            qDebug() << query.lastError() << endl;
    }
    return varMAJ&(varIns|varDelC);
}


bool DBManager_Personnel::SupprimerPersonnel(unsigned int idRow, QString Metier) {
    bool varReq;
    bool varDel;
    bool varDelInf = false;
    unsigned int nbLigne = 0;
    int idMetier = TravailVersInt(Metier);
    int id;

    query.prepare("SELECT Id, Nom, Prenom, IdType FROM TRessource WHERE IdType = :idMet");
    query.bindValue(":idMet", idMetier);

    if ((varReq = query.exec())) {
        while ((query.next()) && (nbLigne != idRow)) {
            nbLigne++;
        }
        id = query.value(0).toInt();

        query.prepare("DELETE FROM TRessource WHERE Id = :id ");
        query.bindValue(":id", id);
        varDel = query.exec();
        if (!varDel)
            qDebug() << query.lastError() << endl;

        if (QString::compare("Informaticien", Metier, Qt::CaseInsensitive) == 0) {
            query.prepare("DELETE FROM TCompte WHERE Id = :id");
            query.bindValue(":id", id);
            varDelInf = query.exec();
            if (!varDelInf)
                qDebug() << query.lastError() << endl;
        }
    }
    return (varReq&varDel)|varDelInf;
}

vector<Personnel>* DBManager_Personnel::RetourListePersonnel() {
    vector<Personnel> *pers = new vector<Personnel>;

    query.prepare("SELECT * FROM TRessource");
    if (query.exec()) {
        while (query.next()) {
            Personnel personnel = Personnel(query.value(1).toString(), query.value(2).toString(), query.value(3).toInt());
            personnel.setId(query.value(0).toInt());
            pers->push_back(personnel);
        }
    }
    return pers;
}

QList<QString>* DBManager_Personnel::RetournerPersonnel(QString nomMetier, int placeReq) {
    int idMetier = TravailVersInt(nomMetier);
    QList<QString> *list = new QList<QString>;
    int i = 0;

    query.prepare("SELECT Nom, Prenom, Id FROM TRessource WHERE IdType = :idMetier");
    query.bindValue(":idMetier", idMetier);

    if ((query.exec())) {
        query.next();
        while(i != placeReq) {
            i++;
            query.next();
        }
        list->push_back(query.value(0).toString());
        list->push_back(query.value(1).toString());
        list->push_back(query.value(2).toString());

    }
    return list;
}

