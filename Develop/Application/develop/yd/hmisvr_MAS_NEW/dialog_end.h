#ifndef DIALOG_END_H
#define DIALOG_END_H

#include <QDialog>

namespace Ui {
class Dialog_end;
}

class Dialog_end : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_end(QWidget *parent = 0);
    ~Dialog_end();

private:
    Ui::Dialog_end *ui;

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

    void signal_exit_end();
};

#endif // DIALOG_END_H
