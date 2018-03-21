#ifndef CONTROLLEUR_PERSONNEL_H
#define CONTROLLEUR_PERSONNEL_H

#include <qstring.h>
#include "Modele/personnel.h"
#include <QSqlQuery>
#include "controleur_BD.h"
#include <QVariant>
#include <QList>
#include <vector>
#include <stdio.h>

using namespace std;

class Controleur_Personnel
{

private:
    QSqlQuery query;
    QList<QString> VString;
    QList<QString>::iterator VSIterator;

    void RecupMetier();

    inline bool PersonneExiste(Personnel per) {
        bool var;

        query.prepare("SELECT Nom, Prenom FROM TRessource WHERE Nom LIKE :nom AND Prenom LIKE :prenom");
        query.bindValue(":nom", per.getNom());
        query.bindValue(":prenom", per.getPrenom());
        var = query.exec();

        if (query.next()) {
            cout << "Le personnel travaille déjà pour l'entreprise" << endl;
            var = true;

        }
        else    {
            cout << "Le personnel n'a pas ete trouve" << endl;
            var = false;
        }

        return var;
    }

public:
    Controleur_Personnel();
    ~Controleur_Personnel();

    QList<QString> getListe();


    int TravailVersInt(QString metier);
    QString IntVersTravail(int id);

    bool AjouterPersonnel(QString nom, QString prenom, QString travail);
    bool ModifierPersonnel();
    bool SupprimerPersonnel(unsigned int idRow, unsigned int idMetier);

    vector<Personnel>* RetourListePersonnel();
};

#endif // CONTROLLEUR_PERSONNEL_H
