#ifndef CONNEXIONWINDOW_H
#define CONNEXIONWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "dbmanager_identification.h"

namespace Ui {
    class ConnexionWindow;
}

//Classe Vue connexion
class ConnexionWindow : public QDialog
{
    Q_OBJECT

private:

public:
    explicit ConnexionWindow(QWidget *parent = 0);
    ~ConnexionWindow();

public slots:
        //slot appelé lors de la validation qui vérifie si l'id et mdp existent dans la base */
        void slotCheck(void);

    private:
        Ui::ConnexionWindow *ui;
        DBManager_Identification *db_identification;

        /* Initialise les composants graphiques */
        void InitialiseGraphique();
};

#endif // CONNEXIONWINDOW_H
