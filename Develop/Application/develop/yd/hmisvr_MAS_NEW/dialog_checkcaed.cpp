#include "dialog_checkcaed.h"
#include "ui_dialog_checkcaed.h"
#include "globalhmi.h"

Dialog_checkcaed::Dialog_checkcaed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_checkcaed)
{
    ui->setupUi(this);
}

Dialog_checkcaed::~Dialog_checkcaed()
{
    delete ui;
}

void Dialog_checkcaed::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_checkcaed::init_page_val()
{
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void Dialog_checkcaed::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

static int  num_add_end = 0;
void Dialog_checkcaed::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void Dialog_checkcaed::update_page_info()
{
 //   ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
//    ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));

    if(language_num == 1)
    {
          //ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
         ui->label_check->setText(QString::fromUtf8("正在验证,请稍候"));
         ui->label_stubnum->setText(QString::fromUtf8("桩编号:"));
    }
    else  if(language_num == 2)
    {
         // ui->label_logo->setText("AC charging pile");
          ui->label_check->setText("Please waiting for checking the card");
          ui->label_stubnum->setText("Telephone  :");
    }
    else
    {

    }
}

void Dialog_checkcaed::update_hmi_page_index(void)
{
        API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
       if(hmi_page_index != PAGEINDEX_CHECKCARD)
       {
           exit_page_dlg();
       }
       else
       {

       }
}

void Dialog_checkcaed::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_checkcarddlg();
  //  delete checkcard_dlg;
  //  checkcard_dlg = NULL;
}
