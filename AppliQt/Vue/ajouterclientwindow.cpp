#include "ajouterclientwindow.h"
#include "ui_ajouterclientwindow.h"

AjouterClientWindow::AjouterClientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterClientWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->QDialog_btn_ValiderAjoutClient, SIGNAL(rejected()), this, SLOT(close()));
    QObject::connect(ui->QDialog_btn_ValiderAjoutClient, SIGNAL(accepted()), this, SLOT(slotAjouterPersonnel()));
}

AjouterClientWindow::~AjouterClientWindow()
{
    delete ui;
}
