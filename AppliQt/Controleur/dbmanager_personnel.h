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

//Classe interagissant avec la classe Personnel
class DBManager_Personnel
{

private:
    QSqlQuery query;

    /* Retourne vrai si un personnel portant le même nom et prenom existe dans la base */
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

    /* Retourne une liste de tous les types (métiers) de la base */
    QList<QString>* RecupMetier();

    /* Retourne l'id correspondand au label du type (métier) en paramètre */
    int TravailVersInt(QString metier);

    /* Retourne le label du type (métier) depuis son id */
    QString IntVersTravail(int id);

    /* Ajoute un personnel dans la base et ajoute/supprime un login/mdp */
    bool AjouterPersonnel(QString nom, QString prenom, QString travail, QString identifiant, QString mdp);

    /* Modifie les données d'un personnel */
    bool ModifierPersonnel(QString nom, QString prenom, QString nvmetier, QString ancienMetier, QString identifiant, QString mdp, int idRessource);

    /* Supprime tous les RDV depuis un id personnel */
    bool SupprimerRDV(int idPersonnel);

    /* Supprime un personnel et son sompte associé si il est informaticien */
    bool SupprimerPersonnel(unsigned int idRow, QString Metier);

    /* Retourne tous les personnels de la base */
    vector<Personnel>* RetourListePersonnel();

    /* Retourne tous les personnels d'un métier donné */
    QList<QString>* RetournerPersonnel(QString nomMetier, int placeReq);
};

#endif // DBMANAGER_PERSONNEL_H
