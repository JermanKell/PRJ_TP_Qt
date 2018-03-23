#ifndef DEF_RENDEZ_VOUS_H
#define DEF_RENDEZ_VOUS_H

#include <QString>

class RendezVous {
private:
    /*
        Identifiant de la ressource pour le RDV
	*/
    unsigned int idRessource;

	/*
        Identifiant du client ayant pris RDV
	*/
    unsigned int idClient;

    QString heureRDV;

public:
	RendezVous();
    RendezVous(unsigned int idRes, unsigned int idClient);
    ~RendezVous();

    unsigned int getIdRessource();
    unsigned int getIdClient();
    QString getHeureRDV();
    void setHeureRDV(QString str);
    void setIdRessource(unsigned int idRes);
    void setIdClient(unsigned int idClient);
};


#endif // !DEF_RENDEZ_VOUS_H
