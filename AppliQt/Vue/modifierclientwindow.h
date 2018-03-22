#ifndef MODIFIERCLIENTWINDOW_H
#define MODIFIERCLIENTWINDOW_H

#include <QDialog>
#include "dbmanager_client.h"
#include "dbmanager_personnel.h"

namespace Ui {
    class ModifierClientWindow;
}

class ModifierClientWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit ModifierClientWindow(Client *c, DBManager_Client *dbmclient, DBManager_Personnel *dbmpersonnel, QWidget *parent = 0);
        ~ModifierClientWindow();

    private slots:
        void accept();

    private:
        Ui::ModifierClientWindow *ui;
        DBManager_Client *dbm_client;
        DBManager_Personnel *dbm_personnel;
        Client *client;


        void InitialiseGraphique();
        void RemplirListWidgetRessources();
        bool ControleData();
        void MajClient();
};

#endif // MODIFIERCLIENTWINDOW_H
