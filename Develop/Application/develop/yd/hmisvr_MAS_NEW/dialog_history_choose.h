#ifndef DIALOG_HISTORY_CHOOSE_H
#define DIALOG_HISTORY_CHOOSE_H

#include <QDialog>

namespace Ui {
class Dialog_history_choose;
}

class Dialog_history_choose : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_history_choose(QWidget *parent = 0);
    ~Dialog_history_choose();

private:
    Ui::Dialog_history_choose *ui;

private:
    QTimer *timer;

private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);
    void on_pbtn_query_clicked();
    void on_pbtn_query_net_clicked();
    void on_pbtn_cancel_clicked();

private:
    void update_page_info(void);
    void update_hmi_page_index(void);
signals:

    void signal_exit_dlg();
};

#endif // DIALOG_HISTORY_CHOOSE_H
