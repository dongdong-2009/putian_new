#ifndef DIALOG_ORDER_H
#define DIALOG_ORDER_H

#include <QDialog>

namespace Ui {
class Dialog_order;
}

class Dialog_order : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_order(QWidget *parent = 0);
    ~Dialog_order();

private:
    Ui::Dialog_order *ui;
};

#endif // DIALOG_ORDER_H
