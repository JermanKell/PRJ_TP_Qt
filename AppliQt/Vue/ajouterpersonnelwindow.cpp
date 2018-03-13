#include "ajouterpersonnelwindow.h"
#include "ui_ajouterpersonnelwindow.h"

AjouterPersonnelWindow::AjouterPersonnelWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterPersonnelWindow)
{
    ui->setupUi(this);
    ui->edit_Sit->addItem(tr("Banquier type A"));
    ui->edit_Sit->addItem(tr("Banquier type B"));
    ui->edit_Sit->addItem(tr("Assureur logement"));
    ui->edit_Sit->addItem(tr("Assureur voiture"));
    ui->edit_Sit->addItem(tr("Assureur vie"));
    ui->edit_Sit->addItem(tr("Informaticien"));
    ui->edit_Sit->addItem(tr("divers"));

    QObject::connect(ui->boutons_Box, SIGNAL(rejected()), this, SLOT(close()));
    QObject::connect(ui->boutons_Box, SIGNAL(accepted()), this, SLOT(slotAjouterPersonnel()));

    // Récupérer le lien ouvert par le controlleur lie a la BDD
}

AjouterPersonnelWindow::~AjouterPersonnelWindow()
{
    delete ui;
}

void AjouterPersonnelWindow::slotAjouterPersonnel() {
    if (pers.AjouterPersonnel(ui->edit_Nom->text(), ui->edit_Prenom->text(), ui->edit_Sit->currentText()))
        QMessageBox::information(this, "Ajout d'un personnel", "Le personnel a bien été ajouté");
}
