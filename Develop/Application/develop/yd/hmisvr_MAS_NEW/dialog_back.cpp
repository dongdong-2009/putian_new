#include "dialog_back.h"
#include "ui_dialog_back.h"
#include "globalhmi.h"

Dialog_back::Dialog_back(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_back)
{
    ui->setupUi(this);
}

Dialog_back::~Dialog_back()
{
    delete ui;
}

void Dialog_back::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_back::init_page_val()
{
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void Dialog_back::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

static int  num_add_end = 0;
void Dialog_back::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void Dialog_back::update_page_info()
{
    if(language_num == 1)
    {
          //ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
          ui->label_check->setText(QString::fromUtf8("等待信息返回"));
          ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
    }
    else  if(language_num == 2)
    {
         // ui->label_logo->setText("AC charging pile");
          ui->label_check->setText("Waiting for the payoff information");
          ui->label_stubnum->setText("Telephone :");
    }
    else
    {

    }
}

void Dialog_back::update_hmi_page_index(void)
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
   if(hmi_page_index != PAGEINDEX_ERRORCHECK)
   {
       exit_page_dlg();
   }
   else
   {

   }
}

void Dialog_back::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_backdlg_judge();
    //delete back_dlg;
    //back_dlg = NULL;
}
