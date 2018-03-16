#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajouterclientwindow.h"
#include "ajouterpersonnelwindow.h"
#include "aproposwindow.h"
#include "Controleur/controleur_BD.h"
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controleur_mainwindow = new Controleur_mainwindow();

    //Evenements MenuBar
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(slotQuit()));
    QObject::connect(ui->actionClient, SIGNAL(triggered()), this, SLOT(slotAjouterClient()));
    QObject::connect(ui->actionPersonnel, SIGNAL(triggered()), this, SLOT(slotAjouterPersonnel()));
    QObject::connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(slotAPropos()));

    //Evenements ToolBar
    QObject::connect(ui->action_client_Tool, SIGNAL(triggered()), this, SLOT(slotAjouterClient()));
    QObject::connect(ui->action_Personnel_Tool, SIGNAL(triggered()), this, SLOT(slotAjouterPersonnel()));

    QStandardItemModel * model = new QStandardItemModel(0, 10, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Id")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Nom")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Prenom")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Adresse")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Ville")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Code postal")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("Telephone")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString("Date RDV")));
    model->setHorizontalHeaderItem(8, new QStandardItem(QString("Duree RDV")));
    model->setHorizontalHeaderItem(9, new QStandardItem(QString("Priorite")));
    ui->tableViewClient->setModel(model);
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
