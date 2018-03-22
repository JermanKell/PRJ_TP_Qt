#include "modifierpersonnelwindow.h"
#include "ui_modifierpersonnelwindow.h"

ModifierPersonnelWindow::ModifierPersonnelWindow(DBManager_Personnel *dbmpersonnel, QString nomMetier, int placeReq, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierPersonnelWindow)
{
    ui->setupUi(this);
    dbm_personnel = dbmpersonnel;
    informaticien = false;
    nmMetier = nomMetier;
    place = placeReq;

    InitialiseGraphique();
    ui->edit_Sit->setCurrentText(nomMetier);

    QObject::connect(ui->edit_Sit, SIGNAL(currentIndexChanged(QString)), this , SLOT(on_edit_Sit_currentIndexChanged(QString)));
}

ModifierPersonnelWindow::~ModifierPersonnelWindow()
{
    delete ui;
}

void ModifierPersonnelWindow::InitialiseGraphique() {
    QList<QString> * listeMetier = dbm_personnel->RecupMetier();
    for(int i=0; i < listeMetier->size(); i++) {
        ui->edit_Sit->addItem(listeMetier->at(i));
    }
    delete listeMetier;

    QFont font;
    font.setCapitalization(QFont::Capitalize);
    ui->edit_Nom->setFont(font);
    ui->edit_Prenom->setFont(font);
    ui->edit_Id->setFont(font);

    ui->lab_Id->setDisabled(true);
    ui->lab_MdP->setDisabled(true);
    ui->edit_Id->setDisabled(true);
    ui->edit_MdP->setDisabled(true);
    MAJAffichage();
}

bool ModifierPersonnelWindow::ControleData() {
    bool bValide = true;
    if(ui->edit_Nom->text().isEmpty()) {
        bValide = false;
        ui->edit_Nom->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->edit_Nom->setStyleSheet(styleSheet());
    }
    if(ui->edit_Prenom->text().isEmpty()) {
        bValide = false;
        ui->edit_Prenom->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->edit_Prenom->setStyleSheet(styleSheet());
    }
    if (informaticien && ui->edit_Id->text().isEmpty()) {
        bValide = false;
        ui->edit_Id->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->edit_Id->setStyleSheet(styleSheet());
    }
    if (informaticien && ui->edit_MdP->text().isEmpty()) {
        bValide = false;
        ui->edit_MdP->setStyleSheet("border: 2px solid red");
    }
    else {
        ui->edit_MdP->setStyleSheet(styleSheet());
    }
    return bValide;
}

void ModifierPersonnelWindow::accept() {
    QString identifiant = NULL;
    QString mdp = NULL;

    if (!ControleData()) {
        QMessageBox::critical(this, "champs obligatoires", "Tous les champs disponibles ne sont pas remplis !");
    }
    else
    {
        if (informaticien && QString::compare(ui->edit_Id->text(), "Admin", Qt::CaseInsensitive)) {
            QMessageBox::critical(this, "Erreur", "Le login Admin est réservé !");
        }
        else
        {
            if (informaticien) {
                identifiant = ui->edit_Id->text();
                mdp = ui->edit_MdP->text();
            }

            if (dbm_personnel->ModifierPersonnel(ui->edit_Nom->text(), ui->edit_Prenom->text(), ui->edit_Sit->currentText(), nmMetier, identifiant, mdp, idPersonnel)) {
                QMessageBox::information(this, "Modification d'un personnel", "Le personnel a bien ete modifie");
                done(Accepted);
            }
            else QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la modification du personnel !");
        }
    }
}

void ModifierPersonnelWindow::on_edit_Sit_currentIndexChanged(const QString &arg1)
{
    if ((arg1.compare("Informaticien")) == 0) {
        ui->lab_Id->setDisabled(false);
        ui->lab_MdP->setDisabled(false);
        ui->edit_Id->setDisabled(false);
        ui->edit_MdP->setDisabled(false);

        informaticien = true;
    }
    else {
        ui->lab_Id->setDisabled(true);
        ui->lab_MdP->setDisabled(true);
        ui->edit_Id->setDisabled(true);
        ui->edit_MdP->setDisabled(true);

        informaticien = false;
    }
}

void ModifierPersonnelWindow::MAJAffichage() {
    QList<QString> *lStr = dbm_personnel->RetournerPersonnel(nmMetier, place);
    ui->edit_Nom->setText(lStr->at(0));
    ui->edit_Prenom->setText(lStr->at(1));
    idPersonnel = lStr->at(2).toInt();
    delete lStr;
}
