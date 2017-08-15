#include "dialog_money_left.h"
#include "ui_dialog_money_left.h"
#include "globalhmi.h"
Dialog_money_left::Dialog_money_left(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_money_left)
{
    ui->setupUi(this);
}

Dialog_money_left::~Dialog_money_left()
{
    delete ui;
}

void Dialog_money_left::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_money_left::init_page_val()
{
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void Dialog_money_left::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
}

void Dialog_money_left::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}
INT8 buf2_0x69[65]={0 };//gb3212
void Dialog_money_left::update_page_info()
{
   // ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
 //   ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));

    API_Read_DB_Nbyte(PL_0x69_NAME,(INT8 *)(&buf2_0x69),64);
    if(buf2_0x69[0]!=0)
    {
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    ui->label_end->setText(QString::fromLocal8Bit(buf2_0x69));
    }
    char tempvalue=0;
   // API_Read_DB_Nbyte(PL_Account_Money_use_FLAG,(char*)&tempvalue,sizeof(tempvalue));
    if(tempvalue==1)
    {
         ui->label_end->setText(QString::fromUtf8("用户密码不正确"));
    }
    else if(tempvalue==2)
    {
         ui->label_end->setText(QString::fromUtf8("用户不合法"));
    }
    else if(tempvalue==3)
    {
         ui->label_end->setText(QString::fromUtf8("用户不可用"));
    }
    else if(tempvalue==4)
    {
         ui->label_end->setText(QString::fromUtf8("用户充电账户无法使用"));
    }
    else if(tempvalue==5)
    {
         ui->label_end->setText(QString::fromUtf8("账户余额不足"));
    }
    else if(tempvalue==6)
    {
         ui->label_end->setText(QString::fromUtf8("用户支付账户停止使用"));
    }
    else if(tempvalue==7)
    {
         ui->label_end->setText(QString::fromUtf8("用户支付账户余额不明"));
    }
    else if(tempvalue==9)
    {
         ui->label_end->setText(QString::fromUtf8("用户支付账户无法查询"));
    }
    else if(tempvalue==10)
    {
         ui->label_end->setText(QString::fromUtf8("用户支付账户无法使用"));
    }
    if(language_num == 1)
    {
          //ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
         // ui->label_end->setText(QString::fromUtf8("卡内余额不足,请充值"));
          ui->label_end_2->setText(QString::fromUtf8("3秒后返回交易界面"));
    //      ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
    }
    else  if(language_num == 2)
    {
         // ui->label_logo->setText("AC charging pile");
          ui->label_end->setText("Sorry, your credit is running low");
          ui->label_end_2->setText("3 seconds after the return");
          ui->label_stubnum->setText("Telephone :");
    }
    else
    {

    }
}

void Dialog_money_left::update_hmi_page_index(void)
{
        API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
        if(hmi_page_index != PAGEINDEX_LEFTMONEY)
        {
            exit_page_dlg();
        }
        else
        {

        }
}

void Dialog_money_left::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_money_left();
    //delete money_left_dlg;
    //money_left_dlg = NULL;
}
