#include "connexionwindow.h"
#include "ui_connexionwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>

ConnexionWindow::ConnexionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton_annuler, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->pushButton_connexion, SIGNAL(clicked()), this, SLOT(slotCheck()));

    InitialiseGraphique();
}


ConnexionWindow::~ConnexionWindow()
{
    delete ui;
    Controller_BD::kill();
}

void ConnexionWindow::slotCheck(void) {
    bool res = false;

    res = CheckConnexion::CheckCoUser(ui->lineEdit_Id->text(), ui->lineEdit_Mdp->text());

    if (res)
        accept();

    else QMessageBox::critical(this, "Erreur", "Login ou Mot de passe incorrecte !");
}

void ConnexionWindow::InitialiseGraphique() {
    QFont font;
    font.setCapitalization(QFont::Capitalize);
     ui->lineEdit_Id->setFont(font);

     ui->lineEdit_Mdp->setEchoMode(QLineEdit::Password);
     ui->lineEdit_Mdp->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
}
