#include "dialog_end.h"
#include "ui_dialog_end.h"
#include "globalhmi.h"

Dialog_end::Dialog_end(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_end)
{
    ui->setupUi(this);
}

Dialog_end::~Dialog_end()
{
    delete ui;
}

void Dialog_end::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_end::init_page_val()
{
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void Dialog_end::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

static int  num_add_end = 0;
void Dialog_end::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void Dialog_end::update_page_info()
{
   // ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
  //  ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));
    if(language_num == 1)
    {
          //ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
          ui->label_end->setText(QString::fromUtf8("感谢您的使用，欢迎下次光临"));
          ui->label_end_2->setText(QString::fromUtf8("如有问题请拨打客服电话"));
  //    ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
    }
    else  if(language_num == 2)
    {
         // ui->label_logo->setText("AC charging pile");
          ui->label_end->setText("Thank your,see you next time");
          ui->label_end_2->setText("If you have questions call Telephone");
          ui->label_stubnum->setText("Telephone :");
    }
    else
    {

    }
}

void Dialog_end::update_hmi_page_index(void)
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
   if(hmi_page_index != PAGEINDEX_END)
   {
       exit_page_dlg();
   }
   else
   {

   }
}

void Dialog_end::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_end();
    //delete end_dlg;
    //end_dlg = NULL;
}
