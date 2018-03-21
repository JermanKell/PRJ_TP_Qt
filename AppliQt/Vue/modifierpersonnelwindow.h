#ifndef AJOUTERPERSONNELWINDOW_H
#define AJOUTERPERSONNELWINDOW_H

#include <QDialog>
#include "controleur_personnel.h"
#include <QMessageBox>

namespace Ui {
    class ModifierPersonnelWindow;
}

class ModifierPersonnelWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit ModifierPersonnelWindow(Controleur_Personnel *controleur, Personnel * pers, QWidget *parent = 0);
        ~ModifierPersonnelWindow();

    private slots:
        void slotModifierPersonnel();

        void on_edit_Sit_currentIndexChanged(const QString &arg1);

private:
            Ui::ModifierPersonnelWindow *ui;
            Controleur_Personnel *controleur_personnel;
            Personnel * pers;
            bool metier;
};

#endif // AJOUTERPERSONNELWINDOW_H
