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
    ui->statusBar->showMessage("Connecté");
    controleur_mainwindow = new Controleur_mainwindow();

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

    //TableView
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

    //Données du TableView
    QSqlQuery * query = new QSqlQuery(*Controller_BD::getInstance()->getBD());
    if(!query->exec("SELECT * FROM TClient")) {
        qDebug() << query->lastError().text();
    }
    while (query->next()) {
        QList<QStandardItem*> newRow;
        QStandardItem *item_Id = new QStandardItem(query->value(0).toString());
        QStandardItem *item_Nom = new QStandardItem(query->value(1).toString());
        QStandardItem *item_Prenom = new QStandardItem(query->value(2).toString());
        QStandardItem *item_Adresse = new QStandardItem(query->value(3).toString());
        QStandardItem *item_Ville = new QStandardItem(query->value(4).toString());
        QStandardItem *item_CP = new QStandardItem(query->value(5).toString());
        QStandardItem *item_Tel = new QStandardItem(query->value(7).toString());
        QStandardItem *item_DateRDV = new QStandardItem(query->value(8).toString());
        QStandardItem *item_DureeRDV = new QStandardItem(query->value(9).toString());
        QStandardItem *item_Priorite = new QStandardItem(query->value(10).toString());
        newRow.append(item_Id);
        newRow.append(item_Nom);
        newRow.append(item_Prenom);
        newRow.append(item_Adresse);
        newRow.append(item_Ville);
        newRow.append(item_CP);
        newRow.append(item_Tel);
        newRow.append(item_DateRDV);
        newRow.append(item_DureeRDV);
        newRow.append(item_Priorite);
        model->appendRow(newRow);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotAjouterClient() {
    AjouterClientWindow ACWindow;
    if(ACWindow.exec()==QDialog::Accepted)
    {
        ui->statusBar->showMessage("Ajout client validé");
    }
    else
    {
        ui->statusBar->showMessage("Ajout client annulé");
    }
}

void MainWindow::slotAjouterPersonnel() {
    AjouterPersonnelWindow APWindow;
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
