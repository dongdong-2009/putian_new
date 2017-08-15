#ifndef DIALOG_ERR_CHOOSE_H
#define DIALOG_ERR_CHOOSE_H

#include <QDialog>

namespace Ui {
class dialog_err_choose;
}

class dialog_err_choose : public QDialog
{
    Q_OBJECT
    
public:
    explicit dialog_err_choose(QWidget *parent = 0);
    ~dialog_err_choose();
    
private:
    Ui::dialog_err_choose *ui;

private:
    QTimer *timer;

private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);

    void on_pbtn_cancel_clicked();
    void on_pbtn_local_err_clicked();
    void on_pbtn_remote_err_clicked();

private:
    void update_page_info(void);
    void update_hmi_page_index(void);
    
signals:

    void signal_exit_dlg();
};

#endif // DIALOG_ERR_CHOOSE_H
