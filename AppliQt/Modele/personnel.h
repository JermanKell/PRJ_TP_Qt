#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <qstring.h>

class Personnel {
  private:
    QString Nom;
    QString Prenom;
    int Type;

  public:
    Personnel(QString nom, QString prenom, int metierType);
    ~Personnel();

    QString getPrenom();
    QString getNom();

    int getTypeMetier();
};

#endif // PERSONNEL_H
