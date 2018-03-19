#include "mainwindow.h"
#include "connexionwindow.h"
#include "checkconnexion.h"
#include "c_init_bd.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    if (!QFile::exists("base_tmp.sqli"))
        C_INIT_BD::Creation_BD();

    QApplication a(argc, argv);

    ConnexionWindow co_w;
    if(co_w.exec()==QDialog::Accepted)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }

   return 0;
}
