#ifndef AJOUTERDIVERS_H
#define AJOUTERDIVERS_H

#include <QDialog>
#include "dbmanager_personnel.h"

namespace Ui {
class ajouterDivers;
}

class ajouterDivers : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterDivers(DBManager_Personnel * controleur, QWidget *parent = 0);
    ~ajouterDivers();

    void accept();



private:
    Ui::ajouterDivers *ui;
    DBManager_Personnel * control;
};

#endif // AJOUTERDIVERS_H
