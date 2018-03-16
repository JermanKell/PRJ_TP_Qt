#ifndef CONTROLEUR_CLIENT_H
#define CONTROLEUR_CLIENT_H

#include "Modele/client.h"
#include <qstring.h>
#include <QVariant>
#include <QSqlQuery>
#include "controleur_BD.h"

class Controleur_Client
{
private:
    QSqlQuery query;

    inline bool ClientExiste(Client cl) {
        bool var;
/*
        query.prepare("SELECT Nom, Prenom FROM TClient WHERE Nom LIKE :nom AND Prenom LIKE :prenom");
        query.bindValue(":nom", cl.);*/

        return var;
    }

public:
    Controleur_Client();
    ~Controleur_Client();

    bool AjouterClient();
    bool ModifierClient();
    bool SupprimerClient();
};

#endif // CONTROLEUR_CLIENT_H
