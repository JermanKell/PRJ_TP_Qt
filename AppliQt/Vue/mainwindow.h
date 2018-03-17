#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controleur_mainwindow.h"

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

    private:
        Ui::MainWindow *ui;
        Controleur_mainwindow * controleur_mainwindow;

};

#endif // MAINWINDOW_H
