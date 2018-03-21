#include "ajouterpersonnelwindow.h"
#include "ui_ajouterpersonnelwindow.h"

AjouterPersonnelWindow::AjouterPersonnelWindow(Controleur_Personnel *controleur, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterPersonnelWindow)
{
    ui->setupUi(this);
    controleur_personnel = controleur;

    ui->edit_Sit->addItem(tr("Banquier A"));
    ui->edit_Sit->addItem(tr("Banquier B"));
    ui->edit_Sit->addItem(tr("Assureur logement"));
    ui->edit_Sit->addItem(tr("Assureur voiture"));
    ui->edit_Sit->addItem(tr("Assureur vie"));
    ui->edit_Sit->addItem(tr("Divers"));
    ui->edit_Sit->addItem(tr("Informaticien"));

    QObject::connect(ui->QDialog_btn_ValiderAjoutPersonnel, SIGNAL(rejected()), this, SLOT(close()));
    QObject::connect(ui->QDialog_btn_ValiderAjoutPersonnel, SIGNAL(accepted()), this, SLOT(slotAjouterPersonnel()));
}

AjouterPersonnelWindow::~AjouterPersonnelWindow()
{
    delete ui;
}

void AjouterPersonnelWindow::slotAjouterPersonnel() {
    if (controleur_personnel->AjouterPersonnel(ui->edit_Nom->text(), ui->edit_Prenom->text(), ui->edit_Sit->currentText())) {
        QMessageBox::information(this, "Ajout d'un personnel", "Le personnel a bien ete ajoute");
        //this->close();
    }
    else QMessageBox::information(this, "Warning", "Une erreur est survenue lors de l'ajout du personnel !");

}
