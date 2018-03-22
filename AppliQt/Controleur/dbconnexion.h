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

class DBConnexion {
private:
    static DBConnexion * dbConnexion;
    static QSqlDatabase * db;

    DBConnexion();
    ~DBConnexion();

public:
    static DBConnexion * getInstance() {
        if(dbConnexion == nullptr) {
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

    QSqlDatabase * getBD() {
        return db;
    }

    static void kill() {
        if (dbConnexion != nullptr)
        {
            db->close();
            delete db;
            db = nullptr;

            delete dbConnexion;
            dbConnexion = nullptr;
        }
    }
};

#endif // DBCONNEXION_H
