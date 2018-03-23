#ifndef AJOUTERPERSONNELWINDOW_H
#define AJOUTERPERSONNELWINDOW_H

#include <QDialog>
#include "dbmanager_personnel.h"
#include "mainwindow.h"
#include <QMessageBox>

namespace Ui {
    class AjouterPersonnelWindow;
}

//Classe Vue ajouter personnel
class AjouterPersonnelWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit AjouterPersonnelWindow(DBManager_Personnel *dbmpersonnel, QWidget *parent = 0);
        ~AjouterPersonnelWindow();

    private slots:
        /* slot appelé lorsque le bouton validé est acivé. Vérifie les champs et tente d'ajouter un personnel à la base */
        void accept();

        /* slot déclanché lorsque l'indice de la combobox change afin d'activer/désactiver les champs login/mdp */
        void on_edit_Sit_currentTextChanged(const QString &arg1);

private:
            Ui::AjouterPersonnelWindow *ui;
            DBManager_Personnel *dbm_personnel;
            bool informaticien;

            /* Initialise les composants graphiques de la vue */
            void InitialiseGraphique();

            /* Vérifie les champs lors de la validation */
            bool ControleData();
};

#endif // AJOUTERPERSONNELWINDOW_H
