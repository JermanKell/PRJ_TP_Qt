#include "modifierpersonnelwindow.h"
#include "ui_modifierpersonnelwindow.h"

ModifierPersonnelWindow::ModifierPersonnelWindow(Controleur_Personnel *controleur, Personnel * personne, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierPersonnelWindow)
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

    QObject::connect(ui->QDialog_btn_ValiderModifPersonnel, SIGNAL(rejected()), this, SLOT(close()));
    QObject::connect(ui->QDialog_btn_ValiderModifPersonnel, SIGNAL(accepted()), this, SLOT(slotModifierPersonnel()));
    QObject::connect(ui->edit_Sit, SIGNAL(currentIndexChanged(QString)), this , SLOT(on_edit_Sit_currentIndexChanged(QString)));

    pers = personne;

    ui->lab_Id->setDisabled(true);
    ui->lab_MdP->setDisabled(true);
    ui->edit_Id->setDisabled(true);
    ui->edit_MdP->setDisabled(true);

    metier = false;

    //ui->edit_Nom->setText();
}

ModifierPersonnelWindow::~ModifierPersonnelWindow()
{
    delete ui;
}

void ModifierPersonnelWindow::slotModifierPersonnel() {
    if (controleur_personnel->ModifierPersonnel()) {
        QMessageBox::information(this, "Ajout d'un personnel", "Le personnel a bien ete ajoute");
        //this->close();
    }
    //else
        QMessageBox::information(this, "Warning", "Une erreur est survenue lors de l'ajout du personnel !");

}

void ModifierPersonnelWindow::on_edit_Sit_currentIndexChanged(const QString &arg1)
{
    if ((arg1.compare("Informaticien")) == 0) {
        ui->lab_Id->setDisabled(false);
        ui->lab_MdP->setDisabled(false);
        ui->edit_Id->setDisabled(false);
        ui->edit_MdP->setDisabled(false);

        metier = true;
    }
}
