#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <qstring.h>

class Personnel {
  private:
QString Nom;
QString Prenom;
QString Type;

  public:
Personnel(QString nom, QString prenom, QString metier);
~Personnel();
};

#endif // PERSONNEL_H
