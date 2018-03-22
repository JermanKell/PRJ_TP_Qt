#ifndef MODIFIERPERSONNELWINDOW_H
#define MODIFIERPERSONNELWINDOW_H

#include <QDialog>
#include "dbmanager_personnel.h"
#include <QMessageBox>

namespace Ui {
    class ModifierPersonnelWindow;
}

class ModifierPersonnelWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit ModifierPersonnelWindow(DBManager_Personnel *dbmpersonnel, QString nomMetier, int placeReq, QWidget *parent = 0);
        ~ModifierPersonnelWindow();

    private slots:
        void accept();
        void on_edit_Sit_currentIndexChanged(const QString &arg1);

private:
            Ui::ModifierPersonnelWindow *ui;
            DBManager_Personnel *dbm_personnel;
            bool informaticien;

            QString nmMetier;
            int place;
            int idPersonnel;

            void InitialiseGraphique();
            bool ControleData();
            void MAJAffichage();
};

#endif // MODIFIERPERSONNELWINDOW_H
