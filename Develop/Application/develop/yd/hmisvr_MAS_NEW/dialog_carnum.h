#ifndef DIALOG_CARNUM_H
#define DIALOG_CARNUM_H

#include <QDialog>

namespace Ui {
class Dialog_carnum;
}

class Dialog_carnum : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_carnum(QWidget *parent = 0);
    ~Dialog_carnum();

private:
    Ui::Dialog_carnum *ui;
private:
    QTimer *timer;

private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);

private slots:
     void btn_press(void);
    void on_pbtn_down_clicked();
    void on_pbtn_up_clicked();
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

    void on_pbtn_change1_clicked();
    void on_pbtn_change2_clicked();
    void on_pbtn_change3_clicked();
private:
    char gb_buf[50];
    int carnum_len;
    int change_carnum;
    void update_page_info(void);
    void update_hmi_page_index(void);
signals:

    void signal_exit_dlg();
};

#endif // DIALOG_CARNUM_H
