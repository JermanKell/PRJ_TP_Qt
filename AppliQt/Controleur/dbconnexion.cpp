#include "dbconnexion.h"

DBConnexion * DBConnexion::dbConnexion = NULL;
QSqlDatabase * DBConnexion::db = NULL;

DBConnexion::DBConnexion() {

}

DBConnexion::~DBConnexion() {

}
