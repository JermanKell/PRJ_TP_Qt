#include "client.h"

Client::Client(QString nom, QString prenom, QString adresse, QString ville, int codepostal, QString jour, int duree, int priorite, std::vector<int> ressources)
{
    str_nom = nom;
    str_prenom = prenom;
    str_adresse = adresse;
    str_ville = ville;
    int_codepostal = codepostal;
    str_dateRDV = jour;
    int_dureeRDV = duree;
    int_priorite = priorite;
    vec_int_idressource = ressources;
}

Client::Client(QString nom, QString prenom, QString adresse, QString ville, int codepostal, QString jour, int duree, int priorite, std::vector<int> ressources, QString commentaires, int telephone)
{
    str_nom = nom;
    str_prenom = prenom;
    str_adresse = adresse;
    str_ville = ville;
    int_codepostal = codepostal;
    str_dateRDV = jour;
    int_dureeRDV = duree;
    int_priorite = priorite;
    vec_int_idressource = ressources;
    str_commentaires = commentaires;
    int_telephone = telephone;
}

QString Client::getNom() {
    return str_nom;
}

QString Client::getPrenom() {
    return str_prenom;
}

QString Client::getAdresse() {
    return str_adresse;
}

QString Client::getVille() {
    return str_ville;
}

int Client::getCP() {
    return int_codepostal;
}

QString Client::getDateRDV() {
    return str_dateRDV;
}

int Client::getDureeRDV() {
    return int_dureeRDV;
}

int Client::getPriorite() {
    return int_priorite;
}

std::vector<int> Client::getIdRessources() {
    return vec_int_idressource;
}

QString Client::getCommentaires() {
    return str_commentaires;
}

int Client::getTelephone() {
    return int_telephone;
}
