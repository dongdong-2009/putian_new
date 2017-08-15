#ifndef P21_JUDGE_CONTINUE_H
#define P21_JUDGE_CONTINUE_H

#include <QDialog>

namespace Ui {
class p21_judge_continue;
}

class p21_judge_continue : public QDialog
{
    Q_OBJECT

public:
    explicit p21_judge_continue(QWidget *parent = 0);
    ~p21_judge_continue();

private:
    Ui::p21_judge_continue *ui;

private:
    QTimer *timer;
    //QTimer *timer1;

private:
    void update_page_info(void);
    void update_hmi_page_index(void);


private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void call_err_dlg(void);
        void call_back_dlg(void);
    void exit_page_dlg(void);
      void call_checkcard_dlg();
    void call_p20_dlg(void);
    void call_p19_dlg(void);
    void call_p05_dlg(void);

    void on_pbtn_cancel_clicked();
    void on_pbtn_ok_clicked();

signals:
    void signal_enable_p20dlg_timer();
    void signal_enable_checkcard_timer();
    void signal_enable_err_timer();
      void signal_enable_back_timer();
    void signal_timer_p21dlg();
    void signal_exit_p21dlg();

};

#endif // P21_JUDGE_CONTINUE_H
