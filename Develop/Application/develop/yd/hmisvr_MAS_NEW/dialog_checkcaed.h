#ifndef DIALOG_CHECKCAED_H
#define DIALOG_CHECKCAED_H

#include <QDialog>

namespace Ui {
class Dialog_checkcaed;
}

class Dialog_checkcaed : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_checkcaed(QWidget *parent = 0);
    ~Dialog_checkcaed();

private:
    Ui::Dialog_checkcaed *ui;

private:
    QTimer *timer;

private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
     void exit_page_dlg(void);
   // void exit_page_dlg_err(void);
  //  void exit_page_dlg_right(void);
private:
    void update_page_info(void);
    void update_hmi_page_index(void);
signals:
       void signal_exit_checkcarddlg();
  //  void signal_exit_checkcarddlg_right();
 //   void signal_exit_checkcarddlg_err();
};

#endif // DIALOG_CHECKCAED_H
