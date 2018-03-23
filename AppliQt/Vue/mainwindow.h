#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager_client.h"
#include "dbmanager_personnel.h"
#include <QTreeView>
#include <QStandardItemModel>


namespace Ui {
    class MainWindow;
}

//Classe Vue principal suite à une autentification
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:

        /* Ouvre la vue A propos */
        void slotAPropos();

        /* Ouvre la vue ajouter client et met à jour la vue */
        void slotAjouterClient();

        /* Ouvre la vue modifier client et met à jours la vue */
        void slotModifierClient();

        /* Supprime un client et met à jours la vue */
        void slotSupprimerClient();

        /* Méthode chargée de mettre à jour le TableView */
        void slotMiseAJourTableView();

        /* Ouvre la vue ajouter personnel et met à jour la vue */
        void slotAjouterPersonnel();

        /* Ouvre la vue modifier personnel et met  jour la vue */
        void slotModifierPersonnel();

        /* Supprime un personnel et met à jour la vue */
        void slotSupprimerPersonnel();

    private:
        Ui::MainWindow *ui;
        QSqlTableModel *tableModel;
        QStandardItemModel *treeModel;
        DBManager_Client *dbm_client;
        DBManager_Personnel *dbm_personnel;

        /* Initialise les composants graphiques de la vue */
        void InitialiseGraphique();

        /* Initialise le TableView */
        void InitialiseTableView();

        /* Initialise le TreeView */
        void InitialiseTreeView();

        /* Méthode chargée de mettre à jour le TreeView */
        void MiseAJourTeeView();
};

#endif // MAINWINDOW_H
