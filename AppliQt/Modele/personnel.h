#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <qstring.h>

//Classe modèle d'un personnel
class Personnel {
  private:
    int Id;
    QString Nom;
    QString Prenom;
    int Type;

  public:
    Personnel(QString nom, QString prenom, int metierType);
    ~Personnel();

    //getter
    int getId();
    QString getPrenom();
    QString getNom();
    int getTypeMetier();

    //setter
    void setId(int id);
};

#endif // PERSONNEL_H
