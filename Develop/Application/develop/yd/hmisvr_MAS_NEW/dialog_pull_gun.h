#ifndef DIALOG_PULL_GUN_H
#define DIALOG_PULL_GUN_H

#include <QDialog>

namespace Ui {
class Dialog_pull_gun;
}

class Dialog_pull_gun : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_pull_gun(QWidget *parent = 0);
    ~Dialog_pull_gun();

private:
    Ui::Dialog_pull_gun *ui;

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

    void signal_exit_pulldlg();
};

#endif // DIALOG_PULL_GUN_H
