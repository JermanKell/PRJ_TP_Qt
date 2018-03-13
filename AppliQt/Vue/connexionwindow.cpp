#include "connexionwindow.h"
#include "ui_connexionwindow.h"
#include "Controleur/controleur_BD.h"
#include <QSqlDatabase>
#include <QSqlQuery>

ConnexionWindow::ConnexionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton_annuler, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->pushButton_connexion, SIGNAL(clicked()), this, SLOT(slotCheck()));
}


ConnexionWindow::~ConnexionWindow()
{
    delete ui;
}

void ConnexionWindow::slotCheck(void) {
    bool res = false;
    QSqlDatabase * cont = Controller_BD::getBD();
    QSqlQuery query(*cont);
    res = CheckConnexion::CheckCoUser(ui->lineEdit->text(), ui->lineEdit_2->text(), Identifiant, MdP);

    if (res)
        accept();

    else QMessageBox::information(this, "Warning", "Login ou Mot de passe incorrecte !");
}
