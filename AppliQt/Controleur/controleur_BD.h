#ifndef CONTOLLER_H
#define CONTOLLER_H

#include "c_init_bd.h"
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <QSqlDatabase>
#include <QFile>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

using namespace std;

class Controller_BD {
private:
    static Controller_BD * controllerDB;
    static QSqlDatabase * db;

    Controller_BD();
    ~Controller_BD();

public:
    static Controller_BD * getInstance() {
        if(controllerDB == nullptr) {
            controllerDB = new Controller_BD();

            if (!QFile::exists("base_tmp.sqli"))
                qDebug() << "Fichier non trouvé !";



            db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
            db->setDatabaseName("base_tmp.sqli");

            if(!db->open()) {
                qDebug() << db->lastError().text();
            }
        }
        return controllerDB;
    }

    static QSqlDatabase * getBD() {
        return db;
    }

    static void kill() {
        if (controllerDB != nullptr)
        {
            db->close();
            delete db;
            db = nullptr;

            delete controllerDB;
            controllerDB = nullptr;
        }
    }
};

#endif // CONTOLLER_H
