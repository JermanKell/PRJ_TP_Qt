#ifndef CONNEXIONWINDOW_H
#define CONNEXIONWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "checkconnexion.h"

namespace Ui {
    class ConnexionWindow;
}

class ConnexionWindow : public QDialog
{
    Q_OBJECT

private:

public:
    explicit ConnexionWindow(QWidget *parent = 0);
    ~ConnexionWindow();

public slots:
        void slotCheck(void);

    private:
        Ui::ConnexionWindow *ui;

        void InitialiseGraphique();
};

#endif // CONNEXIONWINDOW_H
