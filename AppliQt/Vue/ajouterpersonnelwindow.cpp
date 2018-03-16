#include "ajouterpersonnelwindow.h"
#include "ui_ajouterpersonnelwindow.h"

AjouterPersonnelWindow::AjouterPersonnelWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterPersonnelWindow)
{
    ui->setupUi(this);
    ui->edit_Sit->addItem(tr("Banquier A"));
    ui->edit_Sit->addItem(tr("Banquier B"));
    ui->edit_Sit->addItem(tr("Assureur logement"));
    ui->edit_Sit->addItem(tr("Assureur voiture"));
    ui->edit_Sit->addItem(tr("Assureur vie"));
    ui->edit_Sit->addItem(tr("Divers"));
    ui->edit_Sit->addItem(tr("Informaticien"));

    QObject::connect(ui->boutons_Box, SIGNAL(rejected()), this, SLOT(close()));
    QObject::connect(ui->boutons_Box, SIGNAL(accepted()), this, SLOT(slotAjouterPersonnel()));

    pers = Controleur_Personnel();
}

AjouterPersonnelWindow::~AjouterPersonnelWindow()
{
    delete ui;
}

void AjouterPersonnelWindow::slotAjouterPersonnel() {
    if (pers.AjouterPersonnel(ui->edit_Nom->text(), ui->edit_Prenom->text(), ui->edit_Sit->currentText())) {
        QMessageBox::information(this, "Ajout d'un personnel", "Le personnel a bien été ajouté");
        //this->close();
    }
    else QMessageBox::information(this, "Warning", "Une erreur est survenue lors de l'ajout du personnel !");

}
