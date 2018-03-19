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
    ui->lineEdit_Telephone->setValidator(new QDoubleValidator(0, 999999999, 9, this));

    QFont font;
    font.setCapitalization(QFont::Capitalize);
    ui->lineEdit_Nom->setFont(font);
    ui->lineEdit_Prenom->setFont(font);
    ui->lineEdit_Ville->setFont(font);

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
    if(ui->lineEdit_CodePostal->text().count() != 5 || ui->lineEdit_CodePostal->text().toInt() == 0) {
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

void ModifierClientWindow::accept() //SURCHARGE POUR EMPECHER LA FENETRE DE SE FERMER
{
    if (!ControleData()) {
        QMessageBox::warning(this, "Champs invalides", "Certains champs ne sont pas valides !");
    }
    else {
        bool bErreurSQL = false;
        vector<QString> vecRessources;
        for(int iBoucle = 0; iBoucle < ui->listWidget_Ressources->count(); iBoucle++) {
            if(ui->listWidget_Ressources->item(iBoucle)->checkState() == Qt::Checked) {
                vecRessources.push_back(ui->listWidget_Ressources->item(iBoucle)->text());
            }
        }
        MajClient();
        QSqlDatabase *db = Controller_BD::getInstance()->getBD();
        db->transaction();
        if(!controleur_client->ModifierClient(*client)) {
            bErreurSQL = true;
        }
        if(!controleur_client->SupprimerRDVClient(client->getId())) {
            bErreurSQL = true;
        }
        vector<Personnel>* vecPersonnel = controleur_personnel->GetListePersonnel();
        for(unsigned int uiBoucleR=0; uiBoucleR < vecRessources.size(); uiBoucleR++) {
            for(unsigned int uiBoucleP=0; uiBoucleP < vecPersonnel->size(); uiBoucleP++){
                if(QString::compare(vecPersonnel->at(uiBoucleP).getNom(), vecRessources.at(uiBoucleR), Qt::CaseSensitive) == 0) {
                    if(!controleur_client->AjouterRDVClient(client->getId(), vecPersonnel->at(uiBoucleP).getId())) {
                        bErreurSQL = true;
                    }
                }
            }
        }
        delete vecPersonnel;

        if (!bErreurSQL) {
            db->commit();
            QMessageBox::information(this, "Confirmation", "La modification du client a bien été prise en compte !");
            done(Accepted);
        }
        else {
            db->rollback();
            QMessageBox::critical(this, "Erreur", "Un problème est survenu lors de la modification du client.\n Veuillez re-essayer !");
        }
    }
}

void ModifierClientWindow::MajClient() {
    client->setNom(ui->lineEdit_Nom->text());
    client->setPrenom(ui->lineEdit_Prenom->text());
    client->setAdresse(ui->lineEdit_Adresse->text());
    client->setCP(ui->lineEdit_CodePostal->text().toInt());
    client->setVille(ui->lineEdit_Ville->text());
    client->setPriorite(ui->lineEdit_Priorite->text().toInt());
    client->setDateRDV(ui->dateEdit_dateRDV->text());
    client->setDureeRDV(ui->lineEdit_Duree->text().toInt());
    client->setTelephone(ui->lineEdit_Telephone->text().toInt());
    client->setCommentaires(ui->textEdit_Commentaires->toPlainText());
}

ModifierClientWindow::~ModifierClientWindow()
{
    delete ui;
    delete client;
}
