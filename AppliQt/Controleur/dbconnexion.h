#ifndef DBCONNEXION_H
#define DBCONNEXION_H

#include "c_init_bd.h"
#include <stdio.h>
#include <iostream>
#include <QSqlDatabase>
#include <QFile>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

using namespace std;

//Classe singleton connexion
class DBConnexion {
private:
    static DBConnexion * dbConnexion;
    static QSqlDatabase * db;

    DBConnexion();
    ~DBConnexion();

public:
    /* retourne l'instance de la classe */
    static DBConnexion * getInstance() {
        if(dbConnexion == NULL) {
            dbConnexion = new DBConnexion();

            if (!QFile::exists("base_tmp.sqli"))
                qDebug() << "Fichier non trouvé !";

            db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
            db->setDatabaseName("base_tmp.sqli");

            if(!db->open()) {
                qDebug() << db->lastError().text();
            }
        }
        return dbConnexion;
    }

    /* retourne la bdd */
    QSqlDatabase * getBD() {
        return db;
    }

    /* détruit l'objet singleton */
    static void kill() {
        if (dbConnexion != NULL)
        {
            db->close();
            delete db;
            db = NULL;

            delete dbConnexion;
            dbConnexion = NULL;
        }
    }
};

#endif // DBCONNEXION_H
