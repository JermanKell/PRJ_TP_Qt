#include "controleur_personnel.h"

Controleur_Personnel::Controleur_Personnel()
{

}

Controleur_Personnel::~Controleur_Personnel() {

}


bool Controleur_Personnel::AjouterPersonnel(QString nom, QString prenom, QString travail) {
    bool var = false;
    Personnel pers = Personnel(nom, prenom, travail);
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
