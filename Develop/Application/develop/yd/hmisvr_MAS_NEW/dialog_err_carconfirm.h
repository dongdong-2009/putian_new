#ifndef DIALOG_ERR_CARCONFIRM_H
#define DIALOG_ERR_CARCONFIRM_H

#include <QDialog>

namespace Ui {
class dialog_err_carconfirm;
}

class dialog_err_carconfirm : public QDialog
{
    Q_OBJECT
    
public:
    explicit dialog_err_carconfirm(QWidget *parent = 0);
    ~dialog_err_carconfirm();
    
private:
    Ui::dialog_err_carconfirm *ui;

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

    void signal_exit_dlg();
};

#endif // DIALOG_ERR_CARCONFIRM_H
