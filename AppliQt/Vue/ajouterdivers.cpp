#include "ajouterdivers.h"
#include "ui_ajouterdivers.h"

ajouterDivers::ajouterDivers(DBManager_Personnel * controleur, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterDivers)
{
    ui->setupUi(this);
    control = controleur;

}

ajouterDivers::~ajouterDivers()
{
    delete ui;
}

void ajouterDivers::accept() {
    if (control->AjouterPersonnel(ui->edit_nom->text(), ui->edit_prenom->text(), "Divers", "", "")) {
            done(Accepted);
    }
    else qDebug() << "Erreur à l'insertion de la ressource dans la catégorie Divers" << endl;
}
