#ifndef AJOUTERCLIENTWINDOW_H
#define AJOUTERCLIENTWINDOW_H

#include <QDialog>
#include "dbmanager_client.h"
#include "dbmanager_personnel.h"

namespace Ui {
    class AjouterClientWindow;
}

class AjouterClientWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit AjouterClientWindow(DBManager_Client *dbmclient, DBManager_Personnel *dbmpersonnel, QWidget *parent = 0);
        ~AjouterClientWindow();

    private slots:
        void accept();

    private:
        Ui::AjouterClientWindow *ui;
        DBManager_Client *dbm_client;
        DBManager_Personnel *dbm_personnel;

        void InitialiseGraphique();
        void RemplirListWidgetRessources();
        bool ControleData();
};

#endif // AJOUTERCLIENTWINDOW_H
