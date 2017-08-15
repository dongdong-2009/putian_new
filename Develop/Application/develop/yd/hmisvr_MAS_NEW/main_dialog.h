#ifndef MAIN_DIALOG_H
#define MAIN_DIALOG_H

#include <QDialog>

namespace Ui {
    class main_dialog;
}

class main_dialog : public QDialog {
    Q_OBJECT
public:
    main_dialog(QWidget *parent = 0);
    ~main_dialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::main_dialog *ui;
    QTimer *timer;
    void init_main_dlg(void);
    void init_database(void);
    void check_hmi_page_index(void);

private slots:
    void call_p01_dlg(void);
    void call_p02_dlg(void);
    void call_p03_dlg(void);
    void call_p05_dlg(void);
    void call_p07_dlg(void);
    void call_p08_dlg(void);
    void call_p09_dlg(void);
    void call_p13_dlg(void);
    void call_p14_dlg(void);
    void call_p15_dlg(void);
    void call_p16_dlg(void);
    void call_p17_dlg(void);
    void call_p18_dlg(void);
    void call_p19_dlg(void);
    void call_p20_dlg(void);
    void call_p21_dlg(void);
    void call_p24_dlg(void);
    void call_dlg_2(void);
    void call_dlg_1(void);
    void call_err_dlg(void);
    void call_book_dlg(void);
    void call_money_left_dlg(void);
    void call_link_err_dlg();
    void call_end_dlg();
    void call_firsterr_dlg();
    void call_diff_card_dlg();
    void call_pull_gun();
    void call_back(void);
    void call_history_dlg();
    void call_checkcard_dlg(void);
    void call_his_choose_dlg();
    void call_passwd_app_dlg();
    void call_carnum_dlg();
    void call_err_carconfirm();
    void call_not_putiancard();

    void call_err_choose();
    void call_local_err();
    void call_remote_err();

    void on_pbtn_language_clicked();
    void on_pbtn_setpara_clicked();
    void timer_handle(void);
    void start_timer(void);

    void on_pbtn_test_1_clicked();
    void on_pbtn_test_2_clicked();

signals:
    void signal_enable_money_left_timer();
    void signal_enable_p01dlg_timer();
    void signal_enable_p02dlg_timer();
    void signal_enable_p03dlg_timer();
    void signal_enable_p05dlg_timer();
    void signal_enable_p07dlg_timer();
    void signal_enable_p08dlg_timer();
    void signal_enable_p09dlg_timer();
    void signal_enable_p13dlg_timer();
    void signal_enable_p14dlg_timer();
    void signal_enable_p15dlg_timer();
    void signal_enable_p16dlg_timer();
    void signal_enable_p17dlg_timer();
    void signal_enable_p18dlg_timer();
    void signal_enable_p19dlg_timer();
    void signal_enable_p20dlg_timer();
    void signal_enable_p21dlg_timer();
    void signal_enable_p24dlg_timer();
    void signal_enable_dlg_2_timer();
    void signal_enable_dlg_1_timer();
    void signal_enable_err_timer();
    void signal_enable_book_timer();
    void signal_enable_link_err_timer();
    void signal_enable_end_timer();
    void signal_enable_firsterr_timer();
    void signal_enable_diff_card_timer();
    void signal_enable_checkcard_timer();
    void signal_enable_pull_gun_timer();
    void signal_enable_back_timer();
    void signal_enable_historydlg_timer();
    void signal_enable_his_choose_timer();
    void signal_enable_passwd_app_timer();
    void signal_enable_carnum_timer();
    void signal_enable_errconfirm_timer();
    void signal_enable_notputiancard_timer();

    void signal_enable_errchoose_timer();
    void signal_enable_localerr_timer();
    void signal_enable_remoterr_timer();
};

#endif // MAIN_DIALOG_H
