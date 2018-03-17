#ifndef CONTROLLEUR_PERSONNEL_H
#define CONTROLLEUR_PERSONNEL_H

#include <qstring.h>
#include "Modele/personnel.h"
#include <QSqlQuery>
#include "controleur_BD.h"
#include <QVariant>
#include <vector>
#include <stdio.h>

using namespace std;

class Controleur_Personnel
{

private:
    QSqlQuery query;
    vector<QString> VString;
    vector<QString>::iterator VSIterator;

    int TravailVersInt(QString metier);
    QString IntVersTravail(int id);

    inline bool PersonneExiste(Personnel per) {
        bool var;

        query.prepare("SELECT Nom, Prenom FROM TRessource WHERE Nom LIKE :nom AND Prenom LIKE :prenom");
        query.bindValue(":nom", per.getNom());
        query.bindValue(":prenom", per.getPrenom());
        var = query.exec();

        while (query.next()) {
            if (var)    cout << "Le personnel travaille déjà pour l'entreprise" << endl;
            else    cout << "Le personnel n'a pas été trouvé" << endl;
        }
        return var;
    }

public:
    Controleur_Personnel();
    ~Controleur_Personnel();

    bool AjouterPersonnel(QString nom, QString prenom, QString travail);
    bool ModifierPersonnel();
    bool SupprimerPersonnel();
    vector<Personnel>* GetListePersonnel();
};

#endif // CONTROLLEUR_PERSONNEL_H
