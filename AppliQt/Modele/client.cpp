#include "client.h"

Client::Client()
{

}

Client::Client(QString nom, QString prenom, QString adresse, QString ville, int codepostal, QString jour, int duree, int priorite, std::vector<int> ressources)
{
    str_nom = nom;
    str_prenom = prenom;
    str_adresse = adresse;
    str_ville = ville;
    int_codepostal = codepostal;
    str_jour = jour;
    int_duree = duree;
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
    str_jour = jour;
    int_duree = duree;
    int_priorite = priorite;
    vec_int_idressource = ressources;
    str_commentaires = commentaires;
    int_telephone = telephone;
}
