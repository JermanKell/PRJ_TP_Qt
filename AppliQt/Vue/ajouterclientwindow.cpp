#include "ajouterclientwindow.h"
#include "ui_ajouterclientwindow.h"
#include <QList>

AjouterClientWindow::AjouterClientWindow(Controleur_Client *controleur_c, Controleur_Personnel *controleur_p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterClientWindow)
{
    ui->setupUi(this);
    controleur_client = controleur_c;
    controleur_personnel = controleur_p;

    RemplirListWidgetRessources();

    ui->lineEdit_CodePostal->setValidator(new QDoubleValidator(0, 99999, 5, this));
    ui->lineEdit_Duree->setValidator(new QIntValidator(0, 600, this));
    ui->lineEdit_Priorite->setValidator(new QIntValidator(1, 5, this));
    ui->lineEdit_Telephone->setValidator(new QDoubleValidator(0, 9999999999, 10, this));
    ui->dateEdit_dateRDV->setMinimumDate(QDate::currentDate());

    QObject::connect(ui->QDialog_btn_ValiderAjoutClient, SIGNAL(rejected()), this, SLOT(close()));
    QObject::connect(ui->QDialog_btn_ValiderAjoutClient, SIGNAL(accepted()), this, SLOT(slotAjouterClient()));
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
    if(ui->lineEdit_Priorite->text().isEmpty()) {
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
        bValide = false;
    }
    return bValide;
}

void AjouterClientWindow::slotAjouterClient() {

    /*vector<int> vec_ressources;
    for(unsigned int uiBoucle=0; uiBoucle < ui->listWidget_Ressources->count(); uiBoucle++) {
        vec_ressources.push_back(ui->listWidget_Ressources->);
    }

    Client client(ui->lineEdit_Nom->text(), ui->lineEdit_Prenom->text(), ui->lineEdit_Adresse->text(), ui->lineEdit_Ville->text(), ui->lineEdit_CodePostal->text().toInt(),
                  ui->lineEdit_JourRDV->text(), ui->lineEdit_Duree->text(), ui->lineEdit_Priorite->text(), ui->listWidget_Ressources->......, )
    if (controleur_personnel->AjouterPersonnel(ui->edit_Nom->text(), ui->edit_Prenom->text(), ui->edit_Sit->currentText())) {
        QMessageBox::information(this, "Ajout d'un personnel", "Le personnel a bien été ajouté");
        //this->close();
    }
    else QMessageBox::information(this, "Warning", "Une erreur est survenue lors de l'ajout du personnel !");*/

}

void AjouterClientWindow::reject()
{
    qDebug() << Q_FUNC_INFO << "QDialog::reject()";
    done(Rejected);
}

void AjouterClientWindow::accept()
{
    qDebug() << Q_FUNC_INFO << "QDialog::reject()";
    //done(Accepted);
}

AjouterClientWindow::~AjouterClientWindow()
{
    delete ui;
}
