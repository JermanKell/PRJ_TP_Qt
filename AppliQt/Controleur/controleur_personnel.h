#ifndef CONTROLLEUR_PERSONNEL_H
#define CONTROLLEUR_PERSONNEL_H

#include <qstring.h>
#include "Modele/personnel.h"

class Controleur_Personnel
{

private:
    // Attribut qui va faire le lien à la BDD

public:
    Controleur_Personnel();
    ~Controleur_Personnel();

    bool AjouterPersonnel(QString nom, QString prenom, QString travail);
    bool ModifierPersonnel();
    bool SupprimerPersonnel();
};

#endif // CONTROLLEUR_PERSONNEL_H
