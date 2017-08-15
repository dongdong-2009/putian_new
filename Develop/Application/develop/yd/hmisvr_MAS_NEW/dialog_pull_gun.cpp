#include "dialog_pull_gun.h"
#include "ui_dialog_pull_gun.h"
#include "globalhmi.h"
Dialog_pull_gun::Dialog_pull_gun(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_pull_gun)
{
    ui->setupUi(this);
}

Dialog_pull_gun::~Dialog_pull_gun()
{
    delete ui;
}

void Dialog_pull_gun::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_pull_gun::init_page_val()
{
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
  //  UINT8 data = NO_BUTTON;
//    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void Dialog_pull_gun::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_pull_gun::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void Dialog_pull_gun::update_page_info()
{
    //ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
  //  ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));
    if(language_num == 1)
    {
          //ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
         // ui->label_title->setText(QString::fromUtf8("故 障 信 息"));
      //    ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
          ui->label_state->setText(QString::fromUtf8("请拔出充电桩侧的充电枪"));
          //ui->label_state->setText(QString::fromUtf8("设备故障编码 :"));
    }
    else  if(language_num == 2)
    {
         // ui->label_logo->setText("AC charging pile");
         // ui->label_title->setText("Err Information");
          ui->label_stubnum->setText("Telephone :");
          ui->label_state->setText("Please remove CHG Line");
         // ui->label_state->setText("Error State Num :");
    }
    else
    {

    }

}

void Dialog_pull_gun::update_hmi_page_index(void)
{
        API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
        if(hmi_page_index != PAGEINDEX_PULLGUN)
        {
            exit_page_dlg();
        }
        else
        {

        }
}

void Dialog_pull_gun::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_pulldlg();
   // delete pull_gun_dlg;
   // pull_gun_dlg = NULL;
}
