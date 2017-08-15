#ifndef DIALOG_PASSWD_APP_H
#define DIALOG_PASSWD_APP_H

#include <QDialog>

namespace Ui {
class Dialog_passwd_app;
}

class Dialog_passwd_app : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_passwd_app(QWidget *parent = 0);
    ~Dialog_passwd_app();

private:
    Ui::Dialog_passwd_app *ui;

protected:
    void changeEvent(QEvent *e);

private:
        QTimer *timer;

private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);
    void btn_press(void);

private:
    unsigned char btn_passwd_pos;
    char btn_passwd[17];
    char btn_passwd_disp[17];
private:
    void update_page_info(void);
    void update_hmi_page_index(void);
    void call_p02_dlg(void);
    void call_p05_dlg(void);
    void call_p07_dlg(void);
 //   void call_dlg_1(void);

private slots:
    void on_pbtn_ok_clicked();
    void on_pbtn_go_clicked();

    void on_pbtn_back_clicked();
    void on_pbtn_dot_clicked();
    void on_pbtn_num0_clicked();
    void on_pbtn_num9_clicked();
    void on_pbtn_num8_clicked();
    void on_pbtn_num7_clicked();
    void on_pbtn_num6_clicked();
    void on_pbtn_num5_clicked();
    void on_pbtn_num4_clicked();
    void on_pbtn_num3_clicked();
    void on_pbtn_num2_clicked();
    void on_pbtn_num1_clicked();

signals:
    void signal_enable_maindlg_timer();
    void signal_enable_p02dlg_timer();
    void signal_enable_p05dlg_timer();
    void signal_enable_p07dlg_timer();
 //   void signal_enable_dlg_1_timer();
    void signal_exit_dlg();
};

#endif // DIALOG_PASSWD_APP_H
