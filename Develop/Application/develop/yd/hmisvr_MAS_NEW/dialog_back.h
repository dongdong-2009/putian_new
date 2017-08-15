#ifndef DIALOG_BACK_H
#define DIALOG_BACK_H

#include <QDialog>

namespace Ui {
class Dialog_back;
}

class Dialog_back : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_back(QWidget *parent = 0);
    ~Dialog_back();

private:
    Ui::Dialog_back *ui;


private:
    QTimer *timer;

private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);
private:
    void update_page_info(void);
    void update_hmi_page_index(void);
signals:

    void signal_exit_backdlg_judge();
};

#endif // DIALOG_BACK_H
