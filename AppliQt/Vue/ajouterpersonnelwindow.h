#ifndef AJOUTERPERSONNELWINDOW_H
#define AJOUTERPERSONNELWINDOW_H

#include <QDialog>
#include "controleur_personnel.h"
#include <QMessageBox>

namespace Ui {
    class AjouterPersonnelWindow;
}

class AjouterPersonnelWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit AjouterPersonnelWindow(Controleur_Personnel *controleur, QWidget *parent = 0);
        ~AjouterPersonnelWindow();

    private slots:
        void slotAjouterPersonnel();

    private:
            Ui::AjouterPersonnelWindow *ui;
            Controleur_Personnel *controleur_personnel;
};

#endif // AJOUTERPERSONNELWINDOW_H
