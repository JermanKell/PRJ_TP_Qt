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

    // Traitement et initialisation du treeView
    QSqlQuery * query = new QSqlQuery(*Controller_BD::getInstance()->getBD());
    treeViewInit(*query);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
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
        RefreshTreePers();
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
                slotMiseAJourTableView();
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

void MainWindow::treeViewInit(QSqlQuery & query) {
    int uiBoucle;

    treeModel = new QStandardItemModel();
    QStandardItem * Noeud = treeModel->invisibleRootItem();

    QList<QStandardItem *> lItem;

    list = controleur_personnel->getListe();

    for(uiBoucle = 0; uiBoucle < list.size(); uiBoucle++)
        lItem.push_back(new QStandardItem(list.at(uiBoucle)));

    Noeud->appendColumn(lItem);

    ui->PersView->setModel(treeModel);
    ui->PersView->expandAll();

    if(!query.exec("SELECT IdType, Nom, Prenom FROM TRessource ")) {
        qDebug() << query.lastError().text();
    }
    while(query.next()) {
        unsigned int id = query.value(0).toInt();
        lItem.at(id-1)->appendRow(new QStandardItem(query.value(2).toString() + " " + query.value(1).toString()));
    }
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
            QMessageBox::warning(this, "Supprimer quel personnel?", "Vous n'avez pas sélectionnez un personnel mais une catégorie de métier");
        }
        else {
            unsigned int idRow = index.row();   // Faire une recherche sur le nb de réponses après requête
            unsigned int idMetier = RechercheMetier(metier);

            if (controleur_personnel->SupprimerPersonnel(idRow, idMetier)) {
                ui->statusBar->showMessage("Suppression d'un personnel effectuée");
                RefreshTreePers();
            }
            // Appel de la méthode du controleur_personnel pour la modification
        }
    }
}

unsigned int MainWindow::RechercheMetier(QString metier) {
    unsigned int var = controleur_personnel->TravailVersInt(metier);
    return var;
}

void MainWindow::RefreshTreePers() {
    unsigned int idBoucle;
    vector<Personnel> *lPers = controleur_personnel->RetourListePersonnel();

    QList<QStandardItem *> lItem;

    QStandardItemModel * model = new QStandardItemModel();
    QStandardItem * Noeud = model->invisibleRootItem();
    ui->PersView->setModel(model);

    delete treeModel;
    treeModel = model;

    ui->PersView->expandAll();

    list.clear();
    list = controleur_personnel->getListe();

    for(idBoucle = 0; idBoucle < list.size(); idBoucle++)
        lItem.push_back(new QStandardItem(list.at(idBoucle)));

    Noeud->appendColumn(lItem);

    for (idBoucle = 0; idBoucle < lPers->size(); idBoucle++) {
        Personnel pers = lPers->at(idBoucle);
        lItem.at(pers.getTypeMetier()-1)->appendRow(new QStandardItem(pers.getPrenom() + " " + pers.getNom()));
    }
    delete lPers;
}

void MainWindow::slotMiseAJourTableView() {
    QSqlTableModel *nouveauModel = controleur_client->RechercheClient(ui->lineEdit_IdRecherche->text().toInt(), ui->lineEdit_NomRecherche->text(), ui->lineEdit_PrenomRecherche->text(), ui->dateEditMini->text(), ui->dateEditMax->text());
    ui->tableViewClient->setModel(nouveauModel);
    delete model;
    model = nouveauModel;
}
