#include "ajouterclientwindow.h"
#include "ui_ajouterclientwindow.h"

AjouterClientWindow::AjouterClientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterClientWindow)
{
    ui->setupUi(this);
}

AjouterClientWindow::~AjouterClientWindow()
{
    delete ui;
}
