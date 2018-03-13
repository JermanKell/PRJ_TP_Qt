#ifndef CONTOLLER_H
#define CONTOLLER_H

#include "c_init_bd.h"
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <QSqlDatabase>
#include <QFile>
#include <QSqlQuery>

using namespace std;

class Controller_BD {
private:
    Controller_BD();
    ~Controller_BD();
    static QSqlDatabase * db;

public:
    Controller_BD();
    ~Controller_BD();

    static QSqlDatabase * getBD() {
        if (db == nullptr) {
           // db = new QSqlDatabase();
            db->addDatabase("SQLITE");

            if (!QFile::exists("base_tmp.sqli"))
                cout << "Fichier non trouvé !" << endl;

            db->setDatabaseName("base_tmp.sqli");
            db->open();
         }

        return db;
    }

    static void kill() {
        if (db != nullptr) {
            db->close();
            delete db;
            db = nullptr;
        }

    }


};

#endif // CONTOLLER_H
