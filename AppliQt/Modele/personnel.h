#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <qstring.h>

class Personnel {
  private:
    int Id;
    QString Nom;
    QString Prenom;
    int Type;

  public:
    Personnel(QString nom, QString prenom, int metierType);
    ~Personnel();

    int getId();
    QString getPrenom();
    QString getNom();

    int getTypeMetier();

    void setId(int id);
};

#endif // PERSONNEL_H
