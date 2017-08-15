#ifndef DIALOG_BOOK_H
#define DIALOG_BOOK_H

#include <QDialog>

namespace Ui {
class Dialog_book;
}

class Dialog_book : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_book(QWidget *parent = 0);
    ~Dialog_book();

private:
    Ui::Dialog_book *ui;

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

    void signal_exit_bookdlg();
};

#endif // DIALOG_BOOK_H
