#ifndef MODIFIERCLIENTWINDOW_H
#define MODIFIERCLIENTWINDOW_H

#include <QDialog>
#include "controleur_client.h"
#include "controleur_personnel.h"

namespace Ui {
    class ModifierClientWindow;
}

class ModifierClientWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit ModifierClientWindow(Client *c, Controleur_Client *controleur_c, Controleur_Personnel *controleur_p, QWidget *parent = 0);
        ~ModifierClientWindow();

    private slots:
        void accept();

    private:
        Ui::ModifierClientWindow *ui;
        Controleur_Client *controleur_client;
        Controleur_Personnel *controleur_personnel;
        Client *client;


        void InitialiseGraphique();
        void RemplirListWidgetRessources();
        bool ControleData();
        void MajClient();
};

#endif // MODIFIERCLIENTWINDOW_H
