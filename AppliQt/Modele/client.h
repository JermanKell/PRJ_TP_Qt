#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include<vector>

//Classe modèle d'un client
class Client
{
    private:

    QString str_remarque;

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
    std::vector<QString> vec_qstring_idressource;
    QString str_commentaires;
    int int_telephone;

    public:

    Client(QString nom, QString prenom, QString adresse, QString ville, int codepostal, QString jour, int duree, int priorite, QString commentaires, int telephone);



    QString getRemarque();
    void setRemarque(QString rem);

    //getter
    int getId();
    QString getNom();
    QString getPrenom();
    QString getAdresse();
    QString getVille();
    int getCP();
    QString getDateRDV();
    int getDureeRDV();
    int getPriorite();
    std::vector<int> & getIdRessources();
    std::vector<QString> & getNomRessources();
    QString getCommentaires();
    int getTelephone();

    //setter
    void setId(int id);
    void setNom(QString nom);
    void setPrenom(QString prenom);
    void setAdresse(QString adresse);
    void setVille(QString ville);
    void setCP(int cp);
    void setDateRDV(QString dateRDV);
    void setDureeRDV(int dureeRDV);
    void setPriorite(int priorite);
    void setIdRessources(std::vector<int> idRessources);
    void setNomRessources(std::vector<QString> nomRessources);
    void setCommentaires(QString commentaires);
    void setTelephone(int telephone);

    /* Retourne vrai si la liste id ressources est vide sinon faux */
    bool IdRessourcesIsEmpty();

    /* Retourne vrai si la liste des noms ressources est vide sinon faux */
    bool NomRessourcesIsEmpty();
};

#endif // CLIENT_H
