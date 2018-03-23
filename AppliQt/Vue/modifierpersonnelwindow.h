#ifndef MODIFIERPERSONNELWINDOW_H
#define MODIFIERPERSONNELWINDOW_H

#include <QDialog>
#include "dbmanager_personnel.h"
#include <QMessageBox>

namespace Ui {
    class ModifierPersonnelWindow;
}

//Classe Vue modifier personnel
class ModifierPersonnelWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit ModifierPersonnelWindow(DBManager_Personnel *dbmpersonnel, QString nomMetier, int placeReq, QWidget *parent = 0);
        ~ModifierPersonnelWindow();

    private slots:

        /* slot appelé lorsque le bouton validé est acivé. Vérifie les champs et tente de mettre à jour un personnel à la base */
        void accept();

        /* slot déclanché lorsque l'indice de la combobox change afin d'activer/désactiver les champs login/mdp */
        void on_edit_Sit_currentIndexChanged(const QString &arg1);

private:
            Ui::ModifierPersonnelWindow *ui;
            DBManager_Personnel *dbm_personnel;
            bool informaticien;

            QString nmMetier;
            int place;
            int idPersonnel;

            /* Initialise les composants graphiques de la vue */
            void InitialiseGraphique();

            /* Vérifie les champs lors de la validation */
            bool ControleData();

            /* Méthode utilisée par la méthode InitialiseGraphique() */
            void MAJAffichage();
};

#endif // MODIFIERPERSONNELWINDOW_H
