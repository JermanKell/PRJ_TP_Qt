#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajouterclientwindow.h"
#include "ajouterpersonnelwindow.h"
#include "aproposwindow.h"
#include "Controleur/controleur_BD.h"
#include <QSqlQuery>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controleur_client = new Controleur_Client();
    controleur_personnel = new Controleur_Personnel();

    ui->statusBar->showMessage("Connecté");

    //Evenements MenuBar
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(slotQuit()));
    QObject::connect(ui->actionClient, SIGNAL(triggered()), this, SLOT(slotAjouterClient()));
    QObject::connect(ui->actionPersonnel, SIGNAL(triggered()), this, SLOT(slotAjouterPersonnel()));
    QObject::connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(slotAPropos()));

    //Evenements ToolBar
    QObject::connect(ui->action_client_Tool, SIGNAL(triggered()), this, SLOT(slotAjouterClient()));
    QObject::connect(ui->action_Personnel_Tool, SIGNAL(triggered()), this, SLOT(slotAjouterPersonnel()));

    //Evenements TableViewClient
    QObject::connect(ui->btn_ModifierClient, SIGNAL(clicked()), this, SLOT(slotModifierClient()));
    QObject::connect(ui->btn_SupprimerClient, SIGNAL(clicked()), this, SLOT(slotSupprimerClient()));

    model = new QSqlTableModel(this, *Controller_BD::getInstance()->getBD());
    model->setTable("TClient");
    model->select();
    ui->tableViewClient->setModel(model);
    ui->tableViewClient->hideColumn(3);
    ui->tableViewClient->hideColumn(4);
    ui->tableViewClient->hideColumn(5);
    ui->tableViewClient->hideColumn(6);
    ui->tableViewClient->hideColumn(7);
    ui->tableViewClient->hideColumn(9);
    ui->tableViewClient->hideColumn(10);


    //TableView
   /* QStandardItemModel * model = new QStandardItemModel(0, 4, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Nom")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Prenom")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Date RDV")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Id")));
    ui->tableViewClient->setModel(model);

    vector<Client> *vecClient = controleur_client->GetListeClient();

    for(unsigned int uiBoucle=0; uiBoucle < vecClient->size(); uiBoucle++) {
        QList<QStandardItem*> newRow;
        QStandardItem *item_Id = new QStandardItem(vecClient->at(uiBoucle).getId());
        QStandardItem *item_Nom = new QStandardItem(vecClient->at(uiBoucle).getNom());
        QStandardItem *item_Prenom = new QStandardItem(vecClient->at(uiBoucle).getPrenom());
        QStandardItem *item_DateRDV = new QStandardItem(vecClient->at(uiBoucle).getDateRDV());
        newRow.append(item_Id);
        newRow.append(item_Nom);
        newRow.append(item_Prenom);
        newRow.append(item_DateRDV);
        model->appendRow(newRow);
    }*/
}

MainWindow::~MainWindow()
{
    delete ui;
    delete controleur_client;
    delete controleur_personnel;
}

void MainWindow::slotAjouterClient() {
    AjouterClientWindow ACWindow(controleur_client, controleur_personnel);
    if(ACWindow.exec()==QDialog::Accepted)
    {
        ui->statusBar->showMessage("Ajout client validé");
        model->select();
    }
    else
    {
        ui->statusBar->showMessage("Ajout client annulé");
    }
}

void MainWindow::slotAjouterPersonnel() {
    AjouterPersonnelWindow APWindow(controleur_personnel);
    if(APWindow.exec()==QDialog::Accepted)
    {
        ui->statusBar->showMessage("Ajout personnel validé");
    }
    else
    {
        ui->statusBar->showMessage("Ajout personnel annulé");
    }
}

void MainWindow::slotAPropos() {
    AProposWindow AWindow;
    AWindow.exec();
}

void MainWindow::slotModifierClient() {
    if(ui->tableViewClient->currentIndex().row() == -1) {
        ui->statusBar->showMessage("Modification client échoué");
        QMessageBox::warning(this, "Modifier quel client?", "Aucun client n'a été sélectionné dans le tableau");
    }
    else
    {

    }
}

void MainWindow::slotSupprimerClient() {
    if(ui->tableViewClient->currentIndex().row() == -1) {
        ui->statusBar->showMessage("Supression client échoué");
        QMessageBox::warning(this, "Supprimer quel client?", "Aucun client n'a été sélectionné dans le tableau");
    }
    else
    {
        //model->removeRow(currentIndex.row());
    }
}

void MainWindow::slotQuit() {
    Controller_BD::kill();
    qApp->quit();
}
