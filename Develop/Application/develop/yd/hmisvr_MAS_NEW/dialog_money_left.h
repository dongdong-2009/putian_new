#ifndef DIALOG_MONEY_LEFT_H
#define DIALOG_MONEY_LEFT_H

#include <QDialog>

namespace Ui {
class Dialog_money_left;
}

class Dialog_money_left : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_money_left(QWidget *parent = 0);
    ~Dialog_money_left();

private:
    Ui::Dialog_money_left *ui;

private:
    QTimer *timer;

private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);

private:
    void update_page_info(void);
    void update_hmi_page_index(void);
signals:

    void signal_exit_money_left();
};

#endif // DIALOG_MONEY_LEFT_H
