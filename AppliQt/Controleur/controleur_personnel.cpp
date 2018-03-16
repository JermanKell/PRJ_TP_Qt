#include "controleur_personnel.h"

Controleur_Personnel::Controleur_Personnel()
{
    query = QSqlQuery(*(Controller_BD::getInstance()->getBD()));

    VString.push_back(QString("Banquier A"));
    VString.push_back(QString("Banquier B"));
    VString.push_back(QString("Assureur logement"));
    VString.push_back(QString("Assureur voiture"));
    VString.push_back(QString("Assureur vie"));
    VString.push_back(QString("Divers"));
    VString.push_back(QString("Informaticien"));
}

Controleur_Personnel::~Controleur_Personnel() {

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
        cout << "Ajout du personnel en cours..." << endl;

        query.prepare("INSERT INTO TRessource (Id, Nom, Prenom, IdType) " "VALUES (NULL, :nom, :prenom, :id)");
        query.bindValue(":nom", pers.getNom());
        query.bindValue(":prenom", pers.getPrenom());
        query.bindValue(":id", pers.getTypeMetier());
        var = query.exec();

        if (var)    cout << "Le personnel a bien été ajouté !" << endl;
    }

    return var;
}

bool Controleur_Personnel::ModifierPersonnel() {
    bool var = false;


    return var;
}

bool Controleur_Personnel::SupprimerPersonnel() {
    bool var = false;

    return var;
}
