#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controleur_client.h"
#include "controleur_personnel.h"
#include <QTreeView>
#include <QSqlQuery>
#include <QStandardItemModel>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void slotAPropos();
        void slotAjouterClient();
        void slotModifierClient();
        void slotSupprimerClient();
        void slotMiseAJourTableView();
        void slotAjouterPersonnel();
        void slotModifierPersonnel();
        void slotSupprimerPersonnel();

    private:
        Ui::MainWindow *ui;
        QSqlTableModel *model;
        Controleur_Client *controleur_client;
        Controleur_Personnel *controleur_personnel;

        void InitialiseGraphique();
        void InitialiseTableView();

        void treeViewInit(QSqlQuery & query);
        unsigned int RechercheMetier(QString metier);
        void RefreshTreePers();
        QList<QString> list;
        QStandardItemModel * treeModel;


};

#endif // MAINWINDOW_H
