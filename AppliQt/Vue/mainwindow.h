#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controleur_client.h"
#include "controleur_personnel.h"
#include <QCloseEvent>

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
        void slotAjouterClient();
        void slotAjouterPersonnel();
        void slotAPropos();
        void slotQuit();
        void slotModifierClient();
        void slotSupprimerClient();
        void slotMiseAJourTableView();

    private:
        Ui::MainWindow *ui;
        QSqlTableModel *model;
        Controleur_Client *controleur_client;
        Controleur_Personnel *controleur_personnel;

        void InitialiseGraphique();
        void InitialiseTableView();
        void closeEvent (QCloseEvent *event);   //Appelé si window fermé avec onglet 'X'

};

#endif // MAINWINDOW_H
