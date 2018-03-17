#include "ajouterclientwindow.h"
#include "ui_ajouterclientwindow.h"

AjouterClientWindow::AjouterClientWindow(Controleur_Client *controleur, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterClientWindow)
{
    ui->setupUi(this);
    controleur_client = controleur;

    QObject::connect(ui->QDialog_btn_ValiderAjoutClient, SIGNAL(rejected()), this, SLOT(close()));
    QObject::connect(ui->QDialog_btn_ValiderAjoutClient, SIGNAL(accepted()), this, SLOT(slotAjouterClient()));
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

AjouterClientWindow::~AjouterClientWindow()
{
    delete ui;
}
