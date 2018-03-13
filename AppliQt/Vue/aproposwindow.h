#ifndef APROPOSWINDOW_H
#define APROPOSWINDOW_H

#include <QDialog>

namespace Ui {
    class AProposWindow;
}

class AProposWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit AProposWindow(QWidget *parent = 0);
        ~AProposWindow();

    private:
        Ui::AProposWindow *ui;
};

#endif // APROPOSWINDOW_H
