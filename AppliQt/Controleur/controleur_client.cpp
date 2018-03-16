#include "controleur_client.h"

Controleur_Client::Controleur_Client()
{
    query = QSqlQuery(*(Controller_BD::getInstance()->getBD()));
}

Controleur_Client::~Controleur_Client() {

}

