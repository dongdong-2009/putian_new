#ifndef P19_CHARGING_DIALOG_H
#define P19_CHARGING_DIALOG_H

#include <QDialog>


namespace Ui {
    class p19_charging_dialog;
}

class p19_charging_dialog : public QDialog {
    Q_OBJECT
public:
    p19_charging_dialog(QWidget *parent = 0);
    ~p19_charging_dialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::p19_charging_dialog *ui;

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
    // void timer1_handle(void);
    //int caculate_pic_count(int soc);
    void exit_page_dlg(void);
    void call_dlg_2(void);
   // void call_dlg_1(void);
    void call_p20_dlg(void);
    void call_p21_dlg(void);
    void call_err_dlg(void);
    void call_link_err_dlg(void);
        void call_diff_card_dlg(void);
        void call_checkcard_dlg();
    void call_p05_dlg(void);
    void on_pbtn_app_clicked();


signals:
    void signal_enable_checkcard_timer();
     void signal_enable_err_timer();
      void signal_enable_diff_card_timer();
     void signal_enable_link_err_timer();
    void signal_enable_p20dlg_timer();
    void signal_enable_p21dlg_timer();
    void signal_enable_dlg_2_timer();
   // void signal_enable_dlg_1_timer();
    void signal_timer_p19dlg();
    void signal_exit_p19dlg();
};

#endif // P19_CHARGING_DIALOG_H
