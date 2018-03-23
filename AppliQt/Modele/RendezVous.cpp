#include"RendezVous.h"

RendezVous::RendezVous() {

}

RendezVous::RendezVous(unsigned int idRes, unsigned int idClient) {
    idRessource = idRes;
    this->idClient = idClient;
}
RendezVous::~RendezVous() {

}

unsigned int RendezVous::getIdRessource() {
    return idRessource;
}

unsigned int RendezVous::getIdClient() {
    return idClient;
}

QString RendezVous::getHeureRDV() {
    return heureRDV;
}

void RendezVous::setHeureRDV(QString str) {
    heureRDV = str;
}

void RendezVous::setIdClient(unsigned int idClient) {
    this->idClient = idClient;
}

void RendezVous::setIdRessource(unsigned int idRes) {
    idRessource = idRes;
}

