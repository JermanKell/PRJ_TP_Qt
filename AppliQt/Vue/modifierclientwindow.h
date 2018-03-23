#ifndef MODIFIERCLIENTWINDOW_H
#define MODIFIERCLIENTWINDOW_H

#include <QDialog>
#include "dbmanager_client.h"
#include "dbmanager_personnel.h"

namespace Ui {
    class ModifierClientWindow;
}

//Classe Vue modifier client
class ModifierClientWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit ModifierClientWindow(Client *c, DBManager_Client *dbmclient, DBManager_Personnel *dbmpersonnel, QWidget *parent = 0);
        ~ModifierClientWindow();

    private slots:
        /* slot appelé lorsque le bouton validé est acivé. Vérifie les champs et tente de mettre à jour un client à la base */
        void accept();

    private:
        Ui::ModifierClientWindow *ui;
        DBManager_Client *dbm_client;
        DBManager_Personnel *dbm_personnel;
        Client *client;

        /* Initialise les composants graphiques de la vue */
        void InitialiseGraphique();

        /* Méthode chargée de remplir la listWidget des ressources de la base */
        void RemplirListWidgetRessources();

        /* Vérifie les champs lors de la validation */
        bool ControleData();

        /* Met à jour les données de l'attribut client */
        void MajClient();
};

#endif // MODIFIERCLIENTWINDOW_H
