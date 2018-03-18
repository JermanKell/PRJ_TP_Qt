#ifndef AJOUTERCLIENTWINDOW_H
#define AJOUTERCLIENTWINDOW_H

#include <QDialog>
#include "controleur_client.h"
#include "controleur_personnel.h"

namespace Ui {
    class AjouterClientWindow;
}

class AjouterClientWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit AjouterClientWindow(Controleur_Client *controleur_c, Controleur_Personnel *controleur_p, QWidget *parent = 0);
        ~AjouterClientWindow();

    private slots:
        void accept();

    private:
        Ui::AjouterClientWindow *ui;
        Controleur_Client *controleur_client;
        Controleur_Personnel *controleur_personnel;

        void InitialiseGraphique();
        void RemplirListWidgetRessources();
        bool ControleData();
};

#endif // AJOUTERCLIENTWINDOW_H
