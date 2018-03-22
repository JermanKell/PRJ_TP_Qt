#ifndef DBMANAGER_PERSONNEL_H
#define DBMANAGER_PERSONNEL_H

#include <qstring.h>
#include "Modele/personnel.h"
#include <QSqlQuery>
#include "dbconnexion.h"
#include <QVariant>
#include <QList>
#include <vector>
#include <stdio.h>

using namespace std;

class DBManager_Personnel
{

private:
    QSqlQuery query;

    inline bool PersonneExiste(Personnel per) {
        bool var;

        query.prepare("SELECT Nom, Prenom FROM TRessource WHERE Nom LIKE :nom AND Prenom LIKE :prenom");
        query.bindValue(":nom", per.getNom());
        query.bindValue(":prenom", per.getPrenom());
        var = query.exec();

        if (query.next()) {
            var = true;
        }
        else    {
            var = false;
        }

        return var;
    }

public:
    DBManager_Personnel();
    ~DBManager_Personnel();

    QList<QString>* RecupMetier();
    int TravailVersInt(QString metier);
    QString IntVersTravail(int id);

    bool AjouterPersonnel(QString nom, QString prenom, QString travail, QString identifiant, QString mdp);
    bool ModifierPersonnel(QString nom, QString prenom, QString nvmetier, QString ancienMetier, QString identifiant, QString mdp, int idRessource);
    bool SupprimerPersonnel(unsigned int idRow, QString Metier);

    vector<Personnel>* RetourListePersonnel();
    QList<QString>* RetournerPersonnel(QString nomMetier, int placeReq);
};

#endif // DBMANAGER_PERSONNEL_H
