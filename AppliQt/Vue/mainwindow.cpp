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
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
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

    // Evenement TreeView
    QObject::connect(ui->PersModif, SIGNAL(clicked()), this, SLOT(slotModifierPersonnel()));
    QObject::connect(ui->PersSup, SIGNAL(clicked()), this, SLOT(slotSupprimerPersonnel()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tableModel;
    delete treeModel;
    delete controleur_client;
    delete controleur_personnel;
    Controller_BD::kill();
}

void MainWindow::InitialiseGraphique() {
    ui->lineEdit_IdRecherche->setValidator(new QDoubleValidator(0, 999999999, 9, this));
    ui->dateEditMini->setDate(QDate::fromString(controleur_client->DateMinimum(), "yyyy-MM-dd"));
    ui->dateEditMax->setDate(QDate::fromString(controleur_client->DateMaximum(), "yyyy-MM-dd"));
    InitialiseTableView();
    InitialiseTreeView();

    QFont font;
    font.setCapitalization(QFont::Capitalize);
     ui->lineEdit_NomRecherche->setFont(font);
     ui->lineEdit_PrenomRecherche->setFont(font);
}

void MainWindow::InitialiseTableView() {
    tableModel = nullptr;
    slotMiseAJourTableView();
    ui->tableViewClient->hideColumn(3);
    ui->tableViewClient->hideColumn(4);
    ui->tableViewClient->hideColumn(5);
    ui->tableViewClient->hideColumn(6);
    ui->tableViewClient->hideColumn(7);
    ui->tableViewClient->hideColumn(9);
    ui->tableViewClient->hideColumn(10);
    ui->tableViewClient->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewClient->verticalHeader()->setVisible(false);
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
        MiseAJourTeeView();
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
       Client *client = controleur_client->GetClient(tableModel->index(ui->tableViewClient->currentIndex().row(), 0).data().toInt());
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
            if (!controleur_client->SupprimerRDVClient(tableModel->index(ui->tableViewClient->currentIndex().row(), 0).data().toInt())) {
                bErreurSQL = true;
            }
            else {
                if(!tableModel->removeRow(ui->tableViewClient->currentIndex().row())) {
                    bErreurSQL = true;
                }
            }

            if(bErreurSQL) {
                db->rollback();
                ui->statusBar->showMessage("Supression client annulée du à une erreur");
            }
            else {
                db->commit();
                slotMiseAJourTableView();
                ui->statusBar->showMessage("Supression client faite");
            }
        }
        else
        {
            QMessageBox::information(this, "Information", "La supression du client a été annulée");
            ui->statusBar->showMessage("Supression client annulée");
        }
    }

}

void MainWindow::InitialiseTreeView() {
    treeModel = nullptr;
    MiseAJourTeeView();
    ui->PersView->header()->setVisible(false);
}

void MainWindow::slotModifierPersonnel() {
    const QModelIndex index = ui->PersView->selectionModel()->currentIndex();
    if (!index.isValid()) {
        ui->statusBar->showMessage("Modification personnel échouée");
        QMessageBox::warning(this, "Modifier quel personnel ?", "Aucun personnel n'a été sélectionné dans l'arbre");
    }
    else {
        QVariant var = index.data(Qt::DisplayRole);
        const QModelIndex mod = index.parent();
        QVariant value = mod.data(Qt::DisplayRole);
        qDebug() << var.toString() << "\t" << index.row() << "\t" << value.toString() <<endl;
    }

}

void MainWindow::slotSupprimerPersonnel() {
    const QModelIndex index = ui->PersView->selectionModel()->currentIndex();
    if (!index.isValid()) {
        ui->statusBar->showMessage("Supression personnel échouée");
        QMessageBox::warning(this, "Supprimer quel personnel?", "Aucun personnel n'a été sélectionné dans le tableau");
    }
    else {
        QString metier = index.parent().data(Qt::DisplayRole).toString();
        if (metier == NULL) {
            ui->statusBar->showMessage("Supression personnel échouée");
            QMessageBox::critical(this, "pas un personnel", "Vous n'avez pas sélectionnez un personnel mais une catégorie de métier");
        }
        else {

            int reponse = QMessageBox::question(this, "Confirmation", " Confirmer la suppression définitive de ce client?", QMessageBox ::Yes | QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {
                unsigned int idRow = index.row();   // Faire une recherche sur le nb de réponses après requête
                unsigned int idMetier = controleur_personnel->TravailVersInt(metier);

                if (controleur_personnel->SupprimerPersonnel(idRow, idMetier)) {
                    ui->statusBar->showMessage("Suppression d'un personnel effectuée");
                    MiseAJourTeeView();
                }
                // Appel de la méthode du controleur_personnel pour la modification
            }
            else {
                QMessageBox::information(this, "Information", "La supression du personnel a été annulée");
                ui->statusBar->showMessage("Supression personnel annulée");
            }
        }
    }
}

void MainWindow::MiseAJourTeeView() {
    int uiBoucle;
    QStandardItemModel *nouveauModel = new QStandardItemModel();
    QStandardItem * Noeud = nouveauModel->invisibleRootItem();

    QList<QStandardItem *> listeMetier;

    QList<QString> *list = controleur_personnel->RecupMetier();
    for(uiBoucle = 0; uiBoucle < list->size(); uiBoucle++) {
        listeMetier.push_back(new QStandardItem(list->at(uiBoucle)));
    }
    delete list;

    Noeud->appendColumn(listeMetier);

    ui->PersView->setModel(nouveauModel);
    ui->PersView->expandAll();
    delete treeModel;
    treeModel = nouveauModel;
    vector<Personnel> *vecPersonnel = controleur_personnel->RetourListePersonnel();
    for(unsigned int uiBoucle=0; uiBoucle < vecPersonnel->size(); uiBoucle++) {
        listeMetier.at(vecPersonnel->at(uiBoucle).getTypeMetier()-1)->appendRow(new QStandardItem(vecPersonnel->at(uiBoucle).getNom() + " " + vecPersonnel->at(uiBoucle).getPrenom()));
    }
    delete vecPersonnel;
}

void MainWindow::slotMiseAJourTableView() {
    QSqlTableModel *nouveauModel = controleur_client->RechercheClient(ui->lineEdit_IdRecherche->text().toInt(), ui->lineEdit_NomRecherche->text(), ui->lineEdit_PrenomRecherche->text(), ui->dateEditMini->text(), ui->dateEditMax->text());
    ui->tableViewClient->setModel(nouveauModel);
    delete tableModel;
    tableModel = nouveauModel;
}
