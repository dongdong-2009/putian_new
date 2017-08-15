#ifndef DIALOG_FIRST_ERR_H
#define DIALOG_FIRST_ERR_H

#include <QDialog>

namespace Ui {
class Dialog_first_err;
}

class Dialog_first_err : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_first_err(QWidget *parent = 0);
    ~Dialog_first_err();

private:
    Ui::Dialog_first_err *ui;
private:
    QTimer *timer;

private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);
    void on_pbtn_setpara_clicked();

private:
    void update_page_info(void);
    void update_hmi_page_index(void);
signals:

    void signal_exit_firsterr();
};

#endif // DIALOG_FIRST_ERR_H
