#ifndef AJOUTERPERSONNELWINDOW_H
#define AJOUTERPERSONNELWINDOW_H

#include <QDialog>
#include "dbmanager_personnel.h"
#include <QMessageBox>

namespace Ui {
    class AjouterPersonnelWindow;
}

class AjouterPersonnelWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit AjouterPersonnelWindow(DBManager_Personnel *dbmpersonnel, QWidget *parent = 0);
        ~AjouterPersonnelWindow();

    private slots:
        void accept();
        void on_edit_Sit_currentTextChanged(const QString &arg1);

private:
            Ui::AjouterPersonnelWindow *ui;
            DBManager_Personnel *dbm_personnel;
            bool informaticien;

            void InitialiseGraphique();
            bool ControleData();
};

#endif // AJOUTERPERSONNELWINDOW_H
