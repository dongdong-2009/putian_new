#ifndef DIALOG_NOT_PUTIANCARD_H
#define DIALOG_NOT_PUTIANCARD_H

#include <QDialog>

namespace Ui {
class dialog_not_putiancard;
}

class dialog_not_putiancard : public QDialog
{
    Q_OBJECT
    
public:
    explicit dialog_not_putiancard(QWidget *parent = 0);
    ~dialog_not_putiancard();
    
private:
    Ui::dialog_not_putiancard *ui;

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

#endif // DIALOG_NOT_PUTIANCARD_H
