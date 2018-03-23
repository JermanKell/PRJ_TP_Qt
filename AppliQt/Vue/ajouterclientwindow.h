#ifndef AJOUTERCLIENTWINDOW_H
#define AJOUTERCLIENTWINDOW_H

#include <QDialog>
#include "dbmanager_client.h"
#include "dbmanager_personnel.h"

namespace Ui {
    class AjouterClientWindow;
}

//Classe Vue ajouter client
class AjouterClientWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit AjouterClientWindow(DBManager_Client *dbmclient, DBManager_Personnel *dbmpersonnel, QWidget *parent = 0);
        ~AjouterClientWindow();

    private slots:
        /* slot appelé lorsque le bouton validé est acivé. Vérifie les champs et tente d'ajouter un client à la base */
        void accept();

    private:
        Ui::AjouterClientWindow *ui;
        DBManager_Client *dbm_client;
        DBManager_Personnel *dbm_personnel;

        /* Initialise les composants graphiques de la vue */
        void InitialiseGraphique();

        /* Méthode chargée de remplir la listWidget des ressources de la base */
        void RemplirListWidgetRessources();

        /* Vérifie les champs lors de la validation */
        bool ControleData();
};

#endif // AJOUTERCLIENTWINDOW_H
