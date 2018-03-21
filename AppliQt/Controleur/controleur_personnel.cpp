#include "controleur_personnel.h"

Controleur_Personnel::Controleur_Personnel()
{
    query = QSqlQuery(*(Controller_BD::getInstance()->getBD()));

    RecupMetier();

}

Controleur_Personnel::~Controleur_Personnel() {

}

void Controleur_Personnel::RecupMetier() {
    VString.clear();

    bool var = query.exec("SELECT Label FROM TType ");
    if(!var)    qDebug() << query.lastError();
    while (query.next()) {
        VString.push_back(query.value(0).toString());
    }
}

int Controleur_Personnel::TravailVersInt(QString metier) {
    VSIterator = VString.begin();
    int variable = 1;

    while(VSIterator != VString.end()) {
        if (VSIterator->compare(metier) != 0) {
                VSIterator++;
                variable++;
        }
        else VSIterator = VString.end();
    }

    return variable;
}

QString Controleur_Personnel::IntVersTravail(int id) {
    VSIterator = VString.begin();
    int var = 0;

    while (var < id) {
        VSIterator++;
        var++;
    }

    return *VSIterator;
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

QList<QString> Controleur_Personnel::getListe() {
    return VString;
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
