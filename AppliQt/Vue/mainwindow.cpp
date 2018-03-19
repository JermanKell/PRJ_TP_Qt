#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajouterclientwindow.h"
#include "modifierclientwindow.h"
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
    InitialiseGraphique();

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
    QObject::connect(ui->lineEdit_IdRecherche, SIGNAL(textChanged(const QString &)), this, SLOT(slotMiseAJourTableView()));
    QObject::connect(ui->lineEdit_NomRecherche, SIGNAL(textChanged(const QString &)), this, SLOT(slotMiseAJourTableView()));
    QObject::connect(ui->lineEdit_PrenomRecherche, SIGNAL(textChanged(const QString &)), this, SLOT(slotMiseAJourTableView()));
    QObject::connect(ui->dateEditMini, SIGNAL(dateChanged(const QDate &)), this, SLOT(slotMiseAJourTableView()));
    QObject::connect(ui->dateEditMax, SIGNAL(dateChanged(const QDate &)), this, SLOT(slotMiseAJourTableView()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete controleur_client;
    delete controleur_personnel;
}

void MainWindow::InitialiseGraphique() {
    ui->lineEdit_IdRecherche->setValidator(new QDoubleValidator(0, 999999999, 9, this));
    ui->dateEditMini->setDate(QDate::fromString(controleur_client->DateMinimum(), "yyyy-MM-dd"));
    ui->dateEditMax->setDate(QDate::fromString(controleur_client->DateMaximum(), "yyyy-MM-dd"));
    InitialiseTableView();

    QFont font;
    font.setCapitalization(QFont::Capitalize);
     ui->lineEdit_NomRecherche->setFont(font);
     ui->lineEdit_PrenomRecherche->setFont(font);
}

void MainWindow::InitialiseTableView() {
    model = nullptr;
    slotMiseAJourTableView();
    ui->tableViewClient->hideColumn(3);
    ui->tableViewClient->hideColumn(4);
    ui->tableViewClient->hideColumn(5);
    ui->tableViewClient->hideColumn(6);
    ui->tableViewClient->hideColumn(7);
    ui->tableViewClient->hideColumn(9);
    ui->tableViewClient->hideColumn(10);
}

void MainWindow::slotAjouterClient() {
    AjouterClientWindow ACWindow(controleur_client, controleur_personnel);
    if(ACWindow.exec()==QDialog::Accepted)
    {
        ui->statusBar->showMessage("Ajout client validé");
        slotMiseAJourTableView();
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
       Client *client = controleur_client->GetClient(model->index(ui->tableViewClient->currentIndex().row(), 0).data().toInt());
       ModifierClientWindow MCWindow(client, controleur_client, controleur_personnel);
        if(MCWindow.exec()==QDialog::Accepted)
        {
            ui->statusBar->showMessage("Modification client validé");
            slotMiseAJourTableView();
        }
        else
        {
            ui->statusBar->showMessage("Modif client annulé");
        }
    }
}

void MainWindow::slotSupprimerClient() {
    if(ui->tableViewClient->currentIndex().row() == -1) {
        ui->statusBar->showMessage("Supression client échoué");
        QMessageBox::warning(this, "Supprimer quel client?", "Aucun client n'a été sélectionné dans le tableau");
    }
    else
    {
        int reponse = QMessageBox::question(this, "Confirmation", " Confirmer la suppression définitive de ce client?", QMessageBox ::Yes | QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            bool bErreurSQL = false;
            QSqlDatabase *db = Controller_BD::getInstance()->getBD();
            db->transaction();
            if (!controleur_client->SupprimerRDVClient(model->index(ui->tableViewClient->currentIndex().row(), 0).data().toInt())) {
                bErreurSQL = true;
            }
            else {
                if(!model->removeRow(ui->tableViewClient->currentIndex().row())) {
                    bErreurSQL = true;
                }
            }

            if(bErreurSQL) {
                db->rollback();
                ui->statusBar->showMessage("Supression client annulée du à une erreur");
            }
            else {
                db->commit();
                model->select();
                ui->statusBar->showMessage("Supression client faite");
            }
        }
        else
        {
            QMessageBox::information(this, "Information?", "La supression du client a été annulée");
            ui->statusBar->showMessage("Supression client annulée");
        }
    }

}

void MainWindow::slotMiseAJourTableView() {
    QSqlTableModel *nouveauModel = controleur_client->RechercheClient(ui->lineEdit_IdRecherche->text().toInt(), ui->lineEdit_NomRecherche->text(), ui->lineEdit_PrenomRecherche->text(), ui->dateEditMini->text(), ui->dateEditMax->text());
    ui->tableViewClient->setModel(nouveauModel);
    delete model;
    model = nouveauModel;
}

void MainWindow::slotQuit() {
    Controller_BD::kill();
    qApp->quit();
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    slotQuit();
    event->accept();
}
