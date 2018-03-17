#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include<vector>

class Client
{
    private:

    int int_id;
    QString str_nom;
    QString str_prenom;
    QString str_adresse;
    QString str_ville;
    int int_codepostal;
    QString str_dateRDV;
    int int_dureeRDV;
    int int_priorite;
    std::vector<int> vec_int_idressource;
    QString str_commentaires;
    int int_telephone;

    public:

    Client(QString nom, QString prenom, QString adresse, QString ville, int codepostal, QString jour, int duree, int priorite, std::vector<int> ressources, QString commentaires, int telephone);

    int getId();
    QString getNom();
    QString getPrenom();
    QString getAdresse();
    QString getVille();
    int getCP();
    QString getDateRDV();
    int getDureeRDV();
    int getPriorite();
    std::vector<int> getIdRessources();
    QString getCommentaires();
    int getTelephone();

    void setId(int id);


};

#endif // CLIENT_H
