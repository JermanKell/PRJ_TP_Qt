#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajouterclientwindow.h"
#include "ajouterpersonnelwindow.h"
#include "aproposwindow.h"
#include "Controleur/controleur_BD.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Evenements MenuBar
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(slotQuit()));
    QObject::connect(ui->actionClient, SIGNAL(triggered()), this, SLOT(slotAjouterClient()));
    QObject::connect(ui->actionPersonnel, SIGNAL(triggered()), this, SLOT(slotAjouterPersonnel()));
    QObject::connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(slotAPropos()));

    //Evenements ToolBar
    QObject::connect(ui->action_client_Tool, SIGNAL(triggered()), this, SLOT(slotAjouterClient()));
    QObject::connect(ui->action_Personnel_Tool, SIGNAL(triggered()), this, SLOT(slotAjouterPersonnel()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotAjouterClient() {
    AjouterClientWindow ACWindow;
    ACWindow.exec();
}

void MainWindow::slotAjouterPersonnel() {
    AjouterPersonnelWindow APWindow;
    APWindow.exec();
}

void MainWindow::slotAPropos() {
    AProposWindow AWindow;
    AWindow.exec();
}

void MainWindow::slotQuit() {
    Controller_BD::kill();
    qApp->quit();
}
