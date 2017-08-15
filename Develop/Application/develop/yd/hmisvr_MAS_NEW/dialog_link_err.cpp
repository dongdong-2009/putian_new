#include "dialog_link_err.h"
#include "ui_dialog_link_err.h"
#include "globalhmi.h"

Dialog_link_err::Dialog_link_err(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_link_err)
{
    ui->setupUi(this);
}

Dialog_link_err::~Dialog_link_err()
{
    delete ui;
}

void Dialog_link_err::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_link_err::init_page_val()
{
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void Dialog_link_err::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

static int  num_add_link = 0;
void Dialog_link_err::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void Dialog_link_err::update_page_info()
{
//    ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
 //   ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));

    

    //ui->label_time->setText(QString::number(Timer,'f',0));
    


    if(language_num == 1)
    {
          //ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
          ui->label_check->setText(QString::fromUtf8("充电枪连接超时，请重新刷卡"));
          ui->label_check_2->setText(QString::fromUtf8("3秒后返回交易界面"));
          ui->label_stubnum->setText(QString::fromUtf8(" 客  服  电  话  :"));
    }
    else  if(language_num == 2)
    {
         // ui->label_logo->setText("AC charging pile");
          ui->label_check->setText("Time out, please try again");
          ui->label_check_2->setText("3 seconds after the return");
          ui->label_stubnum->setText("Telephone :");
    }
    else
    {

    }

}

void Dialog_link_err::update_hmi_page_index(void)
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
    if(hmi_page_index != PAGEINDEX_CHARGELINK_ERR)
    {
        exit_page_dlg_link();
    }
    else
    {

    }
}

void Dialog_link_err::exit_page_dlg_link()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_dlg_link();
    //delete link_err_dlg;
    //link_err_dlg = NULL;
}

void Dialog_link_err::exit_page_dlg_charge()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_dlg_charge();
    //delete link_err_dlg;
   // link_err_dlg = NULL;
}
