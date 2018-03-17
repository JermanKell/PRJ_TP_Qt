#include "personnel.h"

Personnel::Personnel(QString nom, QString prenom, int metierType) {
    Nom = nom;
    Prenom = prenom;
    Type = metierType;
}

Personnel::~Personnel()
{

}

int Personnel::getId() {
    return Id;
}

QString Personnel::getPrenom() {
    return Prenom;
}
QString Personnel::getNom() {
    return Nom;
}

int Personnel::getTypeMetier() {
    return Type;
}

void Personnel::setId(int id) {
    Id = id;
}
