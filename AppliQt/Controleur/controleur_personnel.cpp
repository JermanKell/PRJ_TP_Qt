#include "controleur_personnel.h"

Controleur_Personnel::Controleur_Personnel()
{
    query = QSqlQuery(*(Controller_BD::getInstance()->getBD()));

    RecupMetier();

}

Controleur_Personnel::~Controleur_Personnel() {

}

QList<QString>* Controleur_Personnel::RecupMetier() {
    QList<QString>* listMetier = new QList<QString>;
    bool var = query.exec("SELECT Label FROM TType ");
    if(!var)    qDebug() << query.lastError();
    while (query.next()) {
        listMetier->push_back(query.value(0).toString());
    }
    return listMetier;
}

int Controleur_Personnel::TravailVersInt(QString metier) {
    query.prepare("SELECT Id FROM TType WHERE Label = :metier");
    query.bindValue(":metier", metier);
    if(!query.exec())    qDebug() << query.lastError();
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QString Controleur_Personnel::IntVersTravail(int id) {
    query.prepare("SELECT Label FROM TType WHERE Id = :id");
    query.bindValue(":id", id);
    if(!query.exec())    qDebug() << query.lastError();
    if (query.next()) {
        return query.value(0).toString();
    }
    return 0;
}

bool Controleur_Personnel::AjouterPersonnel(QString nom, QString prenom, QString travail) {
    bool var;

    int id = TravailVersInt(travail);
    Personnel pers = Personnel(nom, prenom, id);

    var = PersonneExiste(pers);

    if(!var) {
        qDebug() << "Ajout du personnel en cours..." << endl;

        query.prepare("INSERT INTO TRessource (Id, Nom, Prenom, IdType) " "VALUES (NULL, :nom, :prenom, :id)");
        query.bindValue(":nom", pers.getNom());
        query.bindValue(":prenom", pers.getPrenom());
        query.bindValue(":id", pers.getTypeMetier());
        var = query.exec();
    }

    return var;
}

bool Controleur_Personnel::ModifierPersonnel() {
    bool var = false;



    return var;
}

bool Controleur_Personnel::SupprimerPersonnel(unsigned int idRow, unsigned int idMetier) {
    bool var;
    bool value;
    unsigned int nbLigne = 0;
    int id;

    query.prepare("SELECT Id, Nom, Prenom, IdType FROM TRessource WHERE IdType = :idMet");
    query.bindValue(":idMet", idMetier);

    if ((var = query.exec())) {
        while ((query.next()) && (nbLigne != idRow)) {
            nbLigne++;
        }
        id = query.value(0).toInt();

        query.prepare("DELETE FROM TRessource WHERE Id = :id ");
        query.bindValue(":id", id);
        value = query.exec();
    }
    return var&value;
}

vector<Personnel>* Controleur_Personnel::RetourListePersonnel() {
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
