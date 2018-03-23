#include "mainwindow.h"
#include "connexionwindow.h"
#include "dbmanager_identification.h"
#include "c_init_bd.h"
#include <QApplication>
#include <iterator>
#include <algorithm>
#include <map>
#include <string>
#include <QFile>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    multimap<int, string> MultiString;
    multimap<int, string>::iterator it;

    MultiString.insert(make_pair(1, "titi"));
    MultiString.insert(make_pair(4, "toto"));
    MultiString.insert(make_pair(3, "tutu"));
    MultiString.insert(make_pair(4, "tata"));

    it = MultiString.find(3);
    MultiString.erase(it);
    it = MultiString.begin();

    MultiString.insert(make_pair(0, "tete"));
    for (it = MultiString.begin(); it != MultiString.end(); ++it) {
        cout << it->second << endl;
    }


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
