#include "modifierclientwindow.h"
#include "ui_modifierclientwindow.h"
#include <QMessageBox>

ModifierClientWindow::ModifierClientWindow(Client *c, Controleur_Client *controleur_c, Controleur_Personnel *controleur_p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierClientWindow)
{
    ui->setupUi(this);
    controleur_client = controleur_c;
    controleur_personnel = controleur_p;
    client = c;

    InitialiseGraphique();
}

void ModifierClientWindow::InitialiseGraphique() {
    ui->lineEdit_CodePostal->setValidator(new QDoubleValidator(0, 99999, 5, this));
    ui->lineEdit_Duree->setValidator(new QIntValidator(0, 600, this));
    ui->lineEdit_Priorite->setValidator(new QIntValidator(1, 5, this));
    ui->lineEdit_Telephone->setValidator(new QDoubleValidator(0, 9999999999, 10, this));
    //ui->dateEdit_dateRDV->setMinimumDate(QDate::currentDate());

    RemplirListWidgetRessources();

    ui->lineEdit_Nom->setText(client->getNom());
    ui->lineEdit_Prenom->setText(client->getPrenom());
    ui->lineEdit_Adresse->setText(client->getAdresse());
    ui->lineEdit_CodePostal->setText(QString::number(client->getCP()));
    ui->lineEdit_Ville->setText(client->getVille());
    ui->lineEdit_Priorite->setText(QString::number(client->getPriorite()));
    ui->lineEdit_Duree->setText(QString::number(client->getDureeRDV()));
    if(client->getTelephone() != 0) {
        ui->lineEdit_Telephone->setText(QString::number(client->getTelephone()));
    }
    ui->textEdit_Commentaires->setText(client->getCommentaires());
    ui->dateEdit_dateRDV->setDate(QDate::fromString(client->getDateRDV(), "yyyy-MM-dd"));

}

void ModifierClientWindow::RemplirListWidgetRessources(){
    vector<Personnel> *vecPersonnel = controleur_personnel->GetListePersonnel();
    vector<int> *vecIdRessources = controleur_client->GetListeIdRessourcesClient(client->getId());

     for(unsigned int uiBoucle = 0; uiBoucle < vecPersonnel->size(); uiBoucle++) {
        ui->listWidget_Ressources->addItem(vecPersonnel->at(uiBoucle).getNom());
        QListWidgetItem* item = ui->listWidget_Ressources->item(uiBoucle);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);

        bool bTrouve = false;
        unsigned int uiBoucleId=0;

        while(!bTrouve && uiBoucleId < vecIdRessources->size()) {
            if(vecPersonnel->at(uiBoucle).getId() == vecIdRessources->at(uiBoucleId)) {
                item->setCheckState(Qt::Checked);
                vecIdRessources->erase(vecIdRessources->begin() + uiBoucleId);
                bTrouve = true;
           }
            uiBoucleId++;
        }
        if(!bTrouve) {
            item->setCheckState(Qt::Unchecked);
        }
     }
     delete vecPersonnel;
     delete vecIdRessources;
 }

bool ModifierClientWindow::ControleData() {
    bool bValide = true;
    unsigned int uiCountChecked = 0;
    if(ui->lineEdit_Nom->text().isEmpty()) {
        bValide = false;
        ui->lineEdit_Nom->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->lineEdit_Nom->setStyleSheet(styleSheet());
    }
    if(ui->lineEdit_Prenom->text().isEmpty()) {
        bValide = false;
        ui->lineEdit_Prenom->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->lineEdit_Prenom->setStyleSheet(styleSheet());
    }
    if(ui->lineEdit_Adresse->text().isEmpty()) {
        bValide = false;
        ui->lineEdit_Adresse->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->lineEdit_Adresse->setStyleSheet(styleSheet());
    }
    if(ui->lineEdit_CodePostal->text().count() != 5) {
        bValide = false;
        ui->lineEdit_CodePostal->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->lineEdit_CodePostal->setStyleSheet(styleSheet());
    }
    if(ui->lineEdit_Duree->text().isEmpty()) {
        bValide = false;
        ui->lineEdit_Duree->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->lineEdit_Duree->setStyleSheet(styleSheet());
    }
    if(ui->lineEdit_Priorite->text().isEmpty() || ui->lineEdit_Priorite->text().toInt() < 1) {
        bValide = false;
        ui->lineEdit_Priorite->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->lineEdit_Priorite->setStyleSheet(styleSheet());
    }
    if(ui->lineEdit_Ville->text().isEmpty()) {
        bValide = false;
        ui->lineEdit_Ville->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->lineEdit_Ville->setStyleSheet(styleSheet());
    }
    if(!ui->lineEdit_Telephone->text().isEmpty() && ui->lineEdit_Telephone->text().size() != 10) {
        bValide = false;
        ui->lineEdit_Telephone->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->lineEdit_Telephone->setStyleSheet(styleSheet());
    }
    for(int iBoucle = 0; iBoucle < ui->listWidget_Ressources->count(); iBoucle++) {
        if(ui->listWidget_Ressources->item(iBoucle)->checkState() == Qt::Checked) {
            uiCountChecked++;
        }
    }
    if(uiCountChecked == 0) {
        bValide = false;
        ui->listWidget_Ressources->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->listWidget_Ressources->setStyleSheet(styleSheet());
    }
    return bValide;
}

void ModifierClientWindow::accept() //SURCHARGE POUR EMPECHER LA FENETRE DE SE FERMER
{
    if (!ControleData())
    {
        QMessageBox::warning(this, "Champs invalides", "Certains champs ne sont pas valides !");
    }
    else
    {
        Client client(ui->lineEdit_Nom->text(), ui->lineEdit_Prenom->text(), ui->lineEdit_Adresse->text(),
                      ui->lineEdit_Ville->text(), ui->lineEdit_CodePostal->text().toInt(),
                      ui->dateEdit_dateRDV->text(), ui->lineEdit_Duree->text().toInt(), ui->lineEdit_Priorite->text().toInt(),
                      ui->textEdit_Commentaires->toPlainText(), ui->lineEdit_Telephone->text().toInt());
        if(controleur_client->ClientExiste(client))
        {
            QMessageBox::critical(this, "Erreur", "Un client avec le même nom et prénom existe déja !");
        }
        else
        {
            bool bErreurSQL = false;
            vector<QString> vecRessources;
            for(int iBoucle = 0; iBoucle < ui->listWidget_Ressources->count(); iBoucle++)
            {
                if(ui->listWidget_Ressources->item(iBoucle)->checkState() == Qt::Checked)
                {
                    vecRessources.push_back(ui->listWidget_Ressources->item(iBoucle)->text());
                }
            }
            QSqlDatabase *db = Controller_BD::getInstance()->getBD();
            if(!db->transaction())
            {
                qDebug() << db->lastError();
                bErreurSQL = true;
            }
            else
            {
                if(!controleur_client->AjouterClient(client))
                {
                    bErreurSQL = true;
                }
                int idNouveauClient = controleur_client->MaxIdClient();

                vector<Personnel>* vecPersonnel = controleur_personnel->GetListePersonnel();
                for(unsigned int uiBoucleR=0; uiBoucleR < vecRessources.size(); uiBoucleR++)
                {
                    for(unsigned int uiBoucleP=0; uiBoucleP < vecPersonnel->size(); uiBoucleP++)
                    {
                        if(QString::compare(vecPersonnel->at(uiBoucleP).getNom(), vecRessources.at(uiBoucleR), Qt::CaseSensitive) == 0)
                        {
                            if(!controleur_client->AjouterRDVClient(idNouveauClient, vecPersonnel->at(uiBoucleP).getId()))
                            {
                                bErreurSQL = true;
                            }
                        }
                    }
                }
                delete vecPersonnel;

                if (!bErreurSQL)
                {
                    db->commit();
                    QMessageBox::information(this, "Confirmation", "L'ajout du client a bien été pris en compte !");
                    done(Accepted);
                }
                else {
                    db->rollback();
                    QMessageBox::critical(this, "Erreur", "Un problème est survenu lors de l'ajout du nouveau client.\n Veuillez re-essayer !");
                }
            }
        }
    }
}

ModifierClientWindow::~ModifierClientWindow()
{
    delete ui;
    delete client;
}
