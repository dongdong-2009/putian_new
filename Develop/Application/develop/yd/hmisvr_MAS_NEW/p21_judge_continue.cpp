#include "p21_judge_continue.h"
#include "ui_p21_judge_continue.h"
#include "globalhmi.h"

p21_judge_continue::p21_judge_continue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::p21_judge_continue)
{
    ui->setupUi(this);
}

p21_judge_continue::~p21_judge_continue()
{
    delete ui;
}


void p21_judge_continue::on_pbtn_cancel_clicked()
{
    hmi_button_dn_num=CANCEL_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

int ok_flag = 0;
void p21_judge_continue::on_pbtn_ok_clicked()
{
    ok_flag = 1;
    if(language_num == 1)
    {
        ui->label_speaker->setText(QString::fromUtf8("请拔出车端充电枪进行结算"));
    }
    else if(language_num == 2)
    {
         ui->label_speaker->setText("Payoff only when the charge line out !");
    }
    else
    {

    }
}

void p21_judge_continue::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
      ui->label_piccode->setPixmap(QPixmap("/usr/APP/1.png"));

}

void p21_judge_continue::init_page_val()
{
        UINT8 data = NO_BUTTON;
        API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void p21_judge_continue::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
}


int gun_flg = 0;
void p21_judge_continue::timer_handle()
{
     update_page_info();
     update_hmi_page_index();
}

void p21_judge_continue::update_page_info()
{
  //  ui->label_phone->setText(phonenum);
  //   ui->label_code->setText(code);
  //   UINT16 u16_data = 0;
  //  ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
 //   ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));

    if(language_num == 1)
    {
       //   ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
   //ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
         // ui->label_title->setText(QString::fromUtf8("功  能  选  择"));
       //   ui->label_speaker_2->setText(QString::fromUtf8("充 电 暂 停"));
   //       ui->pbtn_cancel->setText(QString::fromUtf8("继 续 充 电"));
    //      ui->pbtn_ok->setText(QString::fromUtf8("拔 枪 结 算"));

    }
    else  if(language_num == 2)
    {
        //  ui->label_logo->setText("AC charging pile");
    //      ui->label_title->setText("Function Selection");
          ui->label_stubnum->setText("Telephone :");
          ui->label_speaker_2->setText("Charging pause");
          ui->pbtn_cancel->setText("Charging");
          ui->pbtn_ok->setText("Payoff");
    }

}

void p21_judge_continue::update_hmi_page_index()
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
    if(hmi_page_index != PAGEINDEX_JUDGE_CONTINUE)
    {
        exit_page_dlg();
    }
    else
    {

    }

}

void p21_judge_continue::call_back_dlg()
{
    timer->stop();
    if(back_dlg){
            delete back_dlg;
            back_dlg = NULL;
    }
    back_dlg = new  Dialog_back;
    back_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_back_timer()),back_dlg,SLOT(init_page_dlg()));
    connect(back_dlg,SIGNAL(signal_exit_backdlg_judge()),this,SLOT(call_p20_dlg()));

    emit signal_enable_back_timer();
    back_dlg->exec();
}

void p21_judge_continue::call_err_dlg()
{
    timer->stop();
    if(err_dlg){
            delete err_dlg;
            err_dlg = NULL;
    }
    err_dlg = new  Dialog_error;
    err_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_err_timer()),err_dlg,SLOT(init_page_dlg()));
    connect(err_dlg,SIGNAL(signal_exit_errdlg_judge()),this,SLOT(start_timer()));

    emit signal_enable_err_timer();
    err_dlg->exec();
}

void p21_judge_continue::call_p05_dlg()
{
    timer->stop();
    emit signal_timer_p21dlg();
    delete p21_dlg;
    p21_dlg = NULL;
}

void p21_judge_continue::call_p19_dlg()
{

    timer->stop();
    emit signal_timer_p21dlg();
    delete p21_dlg;
    p21_dlg = NULL;
}

void p21_judge_continue::call_p20_dlg()
{
    timer->stop();
    if(p20_dlg){
            delete p20_dlg;
            p20_dlg = NULL;
    }
    p20_dlg = new  p20_payoff_dialog;
    p20_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p20dlg_timer()),p20_dlg,SLOT(init_page_dlg()));
    connect(p20_dlg,SIGNAL(signal_exit_p20dlg()),this,SLOT(exit_page_dlg()));
    emit signal_enable_p20dlg_timer();
    p20_dlg->exec();
}

void p21_judge_continue::exit_page_dlg()
{
    DebugMsg(hmilev,8,"exit_page_dlg\n");
    init_page_val();
    timer->stop();
    emit signal_exit_p21dlg();
    //delete p21_dlg;
    //p21_dlg = NULL;
}
void p21_judge_continue::call_checkcard_dlg()
{
    timer->stop();
    if(checkcard_dlg){
            delete checkcard_dlg;
            checkcard_dlg = NULL;
    }
    checkcard_dlg = new  Dialog_checkcaed;
    checkcard_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_checkcard_timer()),checkcard_dlg,SLOT(init_page_dlg()));
   // connect(checkcard_dlg,SIGNAL(signal_exit_checkcarddlg_err()),this,SLOT(start_timer()));
    connect(checkcard_dlg,SIGNAL(signal_exit_checkcarddlg()),this,SLOT(start_timer()));
    emit signal_enable_checkcard_timer();
    checkcard_dlg->exec();
}
