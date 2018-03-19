#include "ajouterclientwindow.h"
#include "ui_ajouterclientwindow.h"
#include <QMessageBox>

AjouterClientWindow::AjouterClientWindow(Controleur_Client *controleur_c, Controleur_Personnel *controleur_p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterClientWindow)
{
    ui->setupUi(this);
    controleur_client = controleur_c;
    controleur_personnel = controleur_p;

    InitialiseGraphique();
}

void AjouterClientWindow::InitialiseGraphique() {
    ui->lineEdit_CodePostal->setValidator(new QDoubleValidator(0, 99999, 5, this));
    ui->lineEdit_Duree->setValidator(new QIntValidator(0, 600, this));
    ui->lineEdit_Priorite->setValidator(new QIntValidator(1, 5, this));
    ui->lineEdit_Telephone->setValidator(new QDoubleValidator(0, 999999999, 9, this));
    ui->dateEdit_dateRDV->setMinimumDate(QDate::currentDate());
    RemplirListWidgetRessources();
}

void AjouterClientWindow::RemplirListWidgetRessources(){
    vector<Personnel> *vecPersonnel = controleur_personnel->GetListePersonnel();
     for(unsigned int uiBoucle = 0; uiBoucle < vecPersonnel->size(); uiBoucle++) {
        ui->listWidget_Ressources->addItem(vecPersonnel->at(uiBoucle).getNom());
        QListWidgetItem* item = ui->listWidget_Ressources->item(uiBoucle);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
     }
     delete vecPersonnel;
 }

bool AjouterClientWindow::ControleData() {
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
    if(!ui->lineEdit_Telephone->text().isEmpty() && ui->lineEdit_Telephone->text().size() < 9) {
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

void AjouterClientWindow::accept() //SURCHARGE POUR EMPECHER LA FENETRE DE SE FERMER
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
            db->transaction();
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

AjouterClientWindow::~AjouterClientWindow()
{
    delete ui;
}
