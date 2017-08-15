#ifndef P18_SETPARA_SUB5_DIALOG_H
#define P18_SETPARA_SUB5_DIALOG_H

#include <QDialog>

namespace Ui {
    class p18_setpara_sub5_dialog;
}

class p18_setpara_sub5_dialog : public QDialog {
    Q_OBJECT
public:
    p18_setpara_sub5_dialog(QWidget *parent = 0);
    ~p18_setpara_sub5_dialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::p18_setpara_sub5_dialog *ui;

private:
    QTimer *timer;

    unsigned char manufactor_time_len;
    char manufactor_time[25];

    unsigned char upload_length;    
    char upload_soft[25];

    int first_val;
    int shape_val;



private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void btn_press();
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);

private:
    void update_page_info(void);
    void update_hmi_page_index(void);

private slots:

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
    
    void on_pbtn_ok_clicked();
    void on_pbtn_up_clicked();
    void on_pbtn_down_clicked();
    void on_pbtn_cancel_clicked();

    void on_char_first_clicked();
    void on_net_first_clicked();
    void on_gun_line_clicked();
    void on_gun_socket_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();

    void on_pbtn_dot_clicked();
    void on_pbtn_back_clicked();

signals:

    void signal_timer_p18dlg();
    void signal_exit_p18dlg();
    void signal_enable_p24dlg_timer();
    void signal_exit_p24dlg();
};

#endif
