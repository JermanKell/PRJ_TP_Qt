#include "ajouterpersonnelwindow.h"
#include "ui_ajouterpersonnelwindow.h"

AjouterPersonnelWindow::AjouterPersonnelWindow(DBManager_Personnel *dbmpersonnel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterPersonnelWindow)
{
    ui->setupUi(this);
    dbm_personnel = dbmpersonnel;

    InitialiseGraphique();

    QObject::connect(ui->edit_Sit, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_edit_Sit_currentTextChanged(QString)));
}

AjouterPersonnelWindow::~AjouterPersonnelWindow()
{
    delete ui;
}

void AjouterPersonnelWindow::InitialiseGraphique() {
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
    informaticien = false;
}

bool AjouterPersonnelWindow::ControleData() {
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

void AjouterPersonnelWindow::accept() {
    QString idSession;
    QString mdpSession;

    if (!ControleData()) {
        QMessageBox::critical(this, "champs obligatoires", "Tous les champs disponibles ne sont pas remplis !");
    }
    else
    {
        if (informaticien && QString::compare(ui->edit_Id->text(), "Admin",  Qt::CaseInsensitive)) {
            QMessageBox::critical(this, "Erreur", "Le login Admin est réservé !");
        }
        else
        {
            if (informaticien) {
                idSession = ui->edit_Id->text();
                mdpSession = ui->edit_MdP->text();
            }
            if (dbm_personnel->AjouterPersonnel(ui->edit_Nom->text(), ui->edit_Prenom->text(), ui->edit_Sit->currentText(), idSession, mdpSession)) {
                QMessageBox::information(this, "Ajout d'un personnel", "Le personnel a bien ete ajouté");
                done(Accepted);
            }
            else QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de l'ajout du personnel !");
        }
    }
}

void AjouterPersonnelWindow::on_edit_Sit_currentTextChanged(const QString &arg1)
{
    if (arg1.compare("Informaticien") == 0) {
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
