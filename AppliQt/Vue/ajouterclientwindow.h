#ifndef AJOUTERCLIENTWINDOW_H
#define AJOUTERCLIENTWINDOW_H

#include <QDialog>
#include "controleur_client.h"

namespace Ui {
    class AjouterClientWindow;
}

class AjouterClientWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit AjouterClientWindow(Controleur_Client *controleur, QWidget *parent = 0);
        ~AjouterClientWindow();

    private slots:
        void slotAjouterClient();

    private:
        Ui::AjouterClientWindow *ui;
        Controleur_Client *controleur_client;
};

#endif // AJOUTERCLIENTWINDOW_H
