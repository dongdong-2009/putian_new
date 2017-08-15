#ifndef P24_SETPARA_SUB6_DIALOG_H
#define P24_SETPARA_SUB6_DIALOG_H

#include <QDialog>

namespace Ui {
class p24_setpara_sub6_dialog;
}

class p24_setpara_sub6_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit p24_setpara_sub6_dialog(QWidget *parent = 0);
    ~p24_setpara_sub6_dialog();


private:
    Ui::p24_setpara_sub6_dialog *ui;

protected:
    void changeEvent(QEvent *e);

private:
    QTimer *timer;

private:
    void update_page_info(void);
    void update_hmi_page_index(void);


private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);
    void btn_press(void);

    
    void on_pbtn_down_clicked();
    void on_pbtn_up_clicked();
    void on_pbtn_ok_clicked();
    void on_pbtn_cancel_clicked();
    /*
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
    
    void on_pbtn_1_clicked();
    void on_pbtn_2_clicked();
    void on_pbtn_3_clicked();
    */
    void call_p18_dlg(void);

    //
    int on_pbtn_dateout_clicked();
    void on_pbtn_err_clicked();
    void on_pbtn_history_clicked();

    //
  

signals:
    void signal_enable_p18dlg_timer();
    void signal_exit_p24dlg();
    void signal_timer_p24dlg();

};

#endif // P24_SETPARA_SUB6_DIALOG_H
