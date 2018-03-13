#ifndef AJOUTERCLIENTWINDOW_H
#define AJOUTERCLIENTWINDOW_H

#include <QDialog>

namespace Ui {
    class AjouterClientWindow;
}

class AjouterClientWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit AjouterClientWindow(QWidget *parent = 0);
        ~AjouterClientWindow();

    private:
        Ui::AjouterClientWindow *ui;
};

#endif // AJOUTERCLIENTWINDOW_H
