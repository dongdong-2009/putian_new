#ifndef DIALOG_LOCAL_ERR_H
#define DIALOG_LOCAL_ERR_H

#include <QDialog>

namespace Ui {
class dialog_local_err;
}

class dialog_local_err : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_local_err(QWidget *parent = 0);
    ~dialog_local_err();

    struct SYNCHRO_TIME
    {
        unsigned short uwYear;
        unsigned char ucMonth;
        unsigned char ucDay;
        unsigned char ucHour;
        unsigned char ucMinute;
        unsigned char ucSecond;
        unsigned char ucReserve;
    };
    char *itos(struct SYNCHRO_TIME  time);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::dialog_local_err *ui;

private:
    QTimer *timer;

    int lbl_num;
    int lbl_num_2;
    int lbl_num_3;
    int lbl_num_4;
    int lbl_num_5;

    struct SYNCHRO_TIME time;
    struct SYNCHRO_TIME time_2;
    struct SYNCHRO_TIME time_3;
    struct SYNCHRO_TIME time_4;
    struct SYNCHRO_TIME time_5;

    unsigned int err_code;
    unsigned int err_code_2;
    unsigned int err_code_3;
    unsigned int err_code_4;
    unsigned int err_code_5;

    unsigned int errtype_num_1;
    unsigned int errtype_num_2;
    unsigned int errtype_num_3;
    unsigned int errtype_num_4;
    unsigned int errtype_num_5;

    int llbl_num;
    int llbl_num_2;
    int llbl_num_3;
    int llbl_num_4;
    int llbl_num_5;

    char lbl_txt[50];
    char lbl_txt_2[50];
    char lbl_txt_3[50];
    char lbl_txt_4[50];
    char lbl_txt_5[50];

    char lbl_txt_11[50];
    char lbl_txt_12[50];
    char lbl_txt_13[50];
    char lbl_txt_14[50];
    char lbl_txt_15[50];





private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);

    void on_pbtn_first_page_clicked();
    void on_pbtn_down_clicked();
    void on_pbtn_up_clicked();
    void on_pbtn_back_clicked();

    void on_pbtn_more_1_clicked();
    void on_pbtn_more_2_clicked();
    void on_pbtn_more_3_clicked();
    void on_pbtn_back_2_clicked();

private:
    void update_page_info(void);
    void update_hmi_page_index(void);

signals:

    void signal_exit_dlg();
};

#endif // DIALOG_LOCAL_ERR_H
