#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include<vector>

class Client
{
    private:

    QString str_nom;
    QString str_prenom;
    QString str_adresse;
    QString str_ville;
    int int_codepostal;
    QString str_jour;
    int int_duree;
    int int_priorite;
    std::vector<int> vec_int_idressource;
    QString str_commentaires;
    int int_telephone;

    public:

    Client();
    Client(QString nom, QString prenom, QString adresse, QString ville, int codepostal, QString jour, int duree, int priorite, std::vector<int> ressources);
    Client(QString nom, QString prenom, QString adresse, QString ville, int codepostal, QString jour, int duree, int priorite, std::vector<int> ressources, QString commentaires, int telephone);
};

#endif // CLIENT_H
