#include "client.h"

Client::Client(QString nom, QString prenom, QString adresse, QString ville, int codepostal, QString date, int duree, int priorite, QString commentaires, int telephone)
{
    str_nom = nom;
    str_prenom = prenom;
    str_adresse = adresse;
    str_ville = ville;
    int_codepostal = codepostal;
    str_dateRDV = date;
    int_dureeRDV = duree;
    int_priorite = priorite;
    str_commentaires = commentaires;
    int_telephone = telephone;
}

int Client::getId() {
    return int_id;
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

std::vector<int> & Client::getIdRessources() {
    return vec_int_idressource;
}

std::vector<QString> & Client::getNomRessources() {
    return vec_qstring_idressource;
}

QString Client::getCommentaires() {
    return str_commentaires;
}

int Client::getTelephone() {
    return int_telephone;
}

void Client::setId(int id) {
    int_id = id;
}

void Client::setNom(QString nom) {
    str_nom = nom;
}

void Client::setPrenom(QString prenom) {
    str_prenom = prenom;
}

void Client::setAdresse(QString adresse) {
    str_adresse = adresse;
}

void Client::setVille(QString ville) {
    str_ville = ville;
}

void Client::setCP(int cp) {
    int_codepostal = cp;
}

void Client::setDateRDV(QString dateRDV) {
    str_dateRDV = dateRDV;
}

void Client::setDureeRDV(int dureeRDV) {
    int_dureeRDV = dureeRDV;
}

void Client::setPriorite(int priorite) {
    int_priorite = priorite;
}

void Client::setIdRessources(std::vector<int> idRessources) {
    vec_int_idressource = idRessources;
}

void Client::setNomRessources(std::vector<QString> nomRessources) {
    vec_qstring_idressource = nomRessources;
}

void Client::setCommentaires(QString commentaires) {
    str_commentaires = commentaires;
}

void Client::setTelephone(int telephone) {
    int_telephone = telephone;
}


bool Client::IdRessourcesIsEmpty() {
    if (vec_int_idressource.size() == 0)
        return true;
    else
        return false;
}

bool Client::NomRessourcesIsEmpty() {
    if (vec_qstring_idressource.size() == 0)
        return true;
    else
        return false;
}
