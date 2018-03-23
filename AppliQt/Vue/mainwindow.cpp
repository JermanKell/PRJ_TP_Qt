#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajouterclientwindow.h"
#include "modifierclientwindow.h"
#include "ajouterpersonnelwindow.h"
#include "modifierpersonnelwindow.h"
#include "aproposwindow.h"
#include "Controleur/dbconnexion.h"
#include "Controleur/Gestion_Client.h"
#include "Vue/ajouterdivers.h"
#include <QDebug>
#include <qdom.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbm_client = new DBManager_Client();
    dbm_personnel = new DBManager_Personnel();

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

    // Slot Ajouter Personnel dans Divers

    QObject::connect(ui->actionDivers, SIGNAL(triggered()), this, SLOT(slotAjouterDivers()));

    //Evenements TableViewClient
    QObject::connect(ui->btn_ModifierClient, SIGNAL(clicked()), this, SLOT(slotModifierClient()));
    QObject::connect(ui->btn_SupprimerClient, SIGNAL(clicked()), this, SLOT(slotSupprimerClient()));

    //Evenements RechercheTableView
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
    qDebug() << "Nombre de requête INSERT total executé: " << dbm_client->getCompteurINSERT() + dbm_personnel->getCompteurINSERT();

    delete ui;
    delete tableModel;
    delete treeModel;
    delete dbm_client;
    delete dbm_personnel;
    DBConnexion::kill();
}

void MainWindow::InitialiseGraphique() {
    this->setWindowTitle("Gestion de RDV");
    ui->lineEdit_IdRecherche->setValidator(new QDoubleValidator(0, 999999999, 9, this));
    ui->dateEditMini->setDate(QDate::fromString(dbm_client->DateMinimum(), "yyyy-MM-dd"));
    ui->dateEditMax->setDate(QDate::fromString(dbm_client->DateMaximum(), "yyyy-MM-dd"));
    InitialiseTableView();
    InitialiseTreeView();

    QFont font;
    font.setCapitalization(QFont::Capitalize);
     ui->lineEdit_NomRecherche->setFont(font);
     ui->lineEdit_PrenomRecherche->setFont(font);
}

void MainWindow::InitialiseTableView() {
    tableModel = NULL;

    ui->lineEdit_PrenomRecherche->setText("son prénom");

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


// Slot Ajouter Personnel Divers
void MainWindow::slotAjouterDivers() {
    ajouterDivers divers(dbm_personnel);
    if (divers.exec()==QDialog::Accepted) {
        ui->statusBar->showMessage("Ajout personnel dans la categorie divers validé");
        MiseAJourTeeView();
    }
    else {
        ui->statusBar->showMessage("Ajout personnel dans la categorie divers annulé");
    }
}






void MainWindow::slotAjouterClient() {
    AjouterClientWindow ACWindow(dbm_client, dbm_personnel);
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
    AjouterPersonnelWindow APWindow(dbm_personnel, this);
    if(APWindow.exec()==QDialog::Accepted)
    {
        MiseAJourTeeView();
        ui->statusBar->showMessage("Ajout de personne terminé");
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
       Client *client = dbm_client->GetClient(tableModel->index(ui->tableViewClient->currentIndex().row(), 0).data().toInt());
       ModifierClientWindow MCWindow(client, dbm_client, dbm_personnel);
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
            QSqlDatabase *db = DBConnexion::getInstance()->getBD();
            db->transaction();
            if (!dbm_client->SupprimerRDVClient(tableModel->index(ui->tableViewClient->currentIndex().row(), 0).data().toInt())) {
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
    treeModel = NULL;
    MiseAJourTeeView();
    ui->PersView->header()->setVisible(false);
}

void MainWindow::slotModifierPersonnel() {
    const QModelIndex index = ui->PersView->selectionModel()->currentIndex();
    if (!index.isValid()) {
        ui->statusBar->showMessage("Modification personnel échouée");
        QMessageBox::warning(this, "Modifier quel personnel ?", "Aucun personnel n'a été selectionné dans l'arbre");
    }
    else {
        if (QString::compare(index.data(Qt::DisplayRole).toString(), "Admin Admin") == 0) {
            ui->statusBar->showMessage("Modification personnel échouée");
            QMessageBox::critical(this, "Erreur", "Impossible de modifier le compte Administrateur !");
        }
        else {
            QString nomMetier = index.parent().data(Qt::DisplayRole).toString();

            ModifierPersonnelWindow modif(dbm_personnel, nomMetier, index.row());
            if (modif.exec() == QDialog::Accepted) {
                ui->statusBar->showMessage("Modification du personnel validé");
                MiseAJourTeeView();
            }
        }
    }
}

void MainWindow::slotSupprimerPersonnel() {
    const QModelIndex index = ui->PersView->selectionModel()->currentIndex();
    if (!index.isValid()) {
        ui->statusBar->showMessage("Suppression personnel échouée");
        QMessageBox::warning(this, "Supprimer quel personnel?", "Aucun personnel n'a été selectionné dans le tableau");
    }
    else {     
        int reponse = QMessageBox::question(this, "Confirmation", " Confirmer la suppression définitive de ce personnel?", QMessageBox ::Yes | QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QString metier = index.parent().data(Qt::DisplayRole).toString();
            if (metier == NULL) {
                ui->statusBar->showMessage("Suppression personnel échouée");
                QMessageBox::warning(this, "Supprimer quel personnel?", "Vous n'avez pas selectionne un personnel mais une categorie de metier");
            }
            else {
                if (QString::compare(index.data(Qt::DisplayRole).toString(), "Admin Admin") == 0) {
                    ui->statusBar->showMessage("Suppression personnel échouée");
                    QMessageBox::critical(this, "Erreur", "Impossible de supprimer le compte Administrateur !");
                }
                else {
                    unsigned int idRow = index.row();   // Faire une recherche sur le nb de réponses après requète

                    if (dbm_personnel->SupprimerPersonnel(idRow, metier)) {
                        QMessageBox::information(this, "Etat de suppression", "Suppression de ce personnel effectué");
                        ui->statusBar->showMessage("Suppression d'un personnel effectuée");
                        MiseAJourTeeView();
                    }
                }
            }
        }
        else
        {
            QMessageBox::information(this, "Information", "La supression de ce personnel a été annulée");
            ui->statusBar->showMessage("Supression personnel annulée");
        }
    }
}

void MainWindow::MiseAJourTeeView() {
    int uiBoucle;
    QStandardItemModel *nouveauModel = new QStandardItemModel();
    QStandardItem * Noeud = nouveauModel->invisibleRootItem();

    QList<QStandardItem *> listeMetier;

    QList<QString> *list = dbm_personnel->RecupMetier();
    for(uiBoucle = 0; uiBoucle < list->size(); uiBoucle++) {
        listeMetier.push_back(new QStandardItem(list->at(uiBoucle)));
    }
    delete list;

    Noeud->appendColumn(listeMetier);

    ui->PersView->setModel(nouveauModel);
    ui->PersView->expandAll();
    delete treeModel;
    treeModel = nouveauModel;
    vector<Personnel> *vecPersonnel = dbm_personnel->RetourListePersonnel();
    for(unsigned int uiBoucle=0; uiBoucle < vecPersonnel->size(); uiBoucle++) {
        listeMetier.at(vecPersonnel->at(uiBoucle).getTypeMetier()-1)->appendRow(new QStandardItem(vecPersonnel->at(uiBoucle).getNom() + " " + vecPersonnel->at(uiBoucle).getPrenom()));
    }
    delete vecPersonnel;
}

void MainWindow::slotMiseAJourTableView() {
    QSqlTableModel *nouveauModel = dbm_client->RechercheClient(ui->lineEdit_IdRecherche->text().toInt(), ui->lineEdit_NomRecherche->text(), ui->lineEdit_PrenomRecherche->text(), ui->dateEditMini->text(), ui->dateEditMax->text());
    ui->tableViewClient->setModel(nouveauModel);
    delete tableModel;
    tableModel = nouveauModel;
}

void MainWindow::on_button_Plan_clicked()
{
    Gestion_Client gClient = Gestion_Client(dbm_client->GetListeClient(ui->edit_date->text()));
    gClient.ProgRDV();
}

void MainWindow::on_button_xml_clicked()
{
    vector<Personnel>  * PerVec =  dbm_personnel->RetourListePersonnel();

  QDomImplementation impl = QDomDocument().implementation();
  // document with document type
  QString name = "Ressources";
  QString publicId = "-//XADECK//DTD Stone 1.0 //EN";
  QString systemId = "http://www-imagis.imag.fr/DTD/stone1.dtd";
  QDomDocument doc(impl.createDocumentType(name,publicId,systemId));
  // add some XML comment at the beginning
  doc.appendChild(doc.createComment("This file describe a jewel"));
  doc.appendChild(doc.createTextNode("\n")); // for nicer output
  // root node
  QDomElement stoneNode = doc.createElement("Ressources");
  stoneNode.setAttribute("name","diamond");
  doc.appendChild(stoneNode);
  // appearance
  QDomElement appearanceNode = doc.createElement("TRessource");
  QDomElement colorNode = doc.createElement("Nom");
 /* colorNode.appendChild(doc.createTextNode("255 255 255"));
  appearanceNode.appendChild(colorNode);
  stoneNode.appendChild(appearanceNode);
  // geometry
  QDomElement geometryNode = doc.createElement("geometry");
  QDomElement triangleNode = doc.createElement("triangle");
  triangleNode.appendChild(doc.createTextNode("0 0 0 1 0 0 1 1 0"));
  geometryNode.appendChild(triangleNode);
  QDomElement quadNode = doc.createElement("quad");
  quadNode.appendChild(doc.createTextNode("0 0 1 1 0 1 1 1 1 0 1 1"));
  geometryNode.appendChild(quadNode);
  stoneNode.appendChild(geometryNode);
  cout<<doc.toString();*/

  delete PerVec;
}
