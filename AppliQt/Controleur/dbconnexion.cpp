#include "dbconnexion.h"

DBConnexion * DBConnexion::dbConnexion = nullptr;
QSqlDatabase * DBConnexion::db = nullptr;

DBConnexion::DBConnexion() {

}

DBConnexion::~DBConnexion() {

}
