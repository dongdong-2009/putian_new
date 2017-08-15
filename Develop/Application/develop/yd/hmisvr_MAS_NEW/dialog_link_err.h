#ifndef DIALOG_LINK_ERR_H
#define DIALOG_LINK_ERR_H

#include <QDialog>

namespace Ui {
class Dialog_link_err;
}

class Dialog_link_err : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_link_err(QWidget *parent = 0);
    ~Dialog_link_err();

private:
    Ui::Dialog_link_err *ui;



private:
    QTimer *timer;

private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg_link(void);
    void exit_page_dlg_charge(void);
private:
    void update_page_info(void);
    void update_hmi_page_index(void);
signals:

    void signal_exit_dlg_link();
        void signal_exit_dlg_charge();
};

#endif // DIALOG_LINK_ERR_H
