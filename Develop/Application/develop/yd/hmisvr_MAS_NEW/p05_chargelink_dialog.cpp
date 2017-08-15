#include "p05_chargelink_dialog.h"
#include "ui_p05_chargelink_dialog.h"
#include "globalhmi.h"

p05_chargelink_dialog::p05_chargelink_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::p05_chargelink_dialog)
{
    ui->setupUi(this);
}

p05_chargelink_dialog::~p05_chargelink_dialog()
{
    delete ui;
}

int num_move_5 = 0;
int move_flag_5 = 0;
BOOL connect_state_flag = 0;

static int delay_time_flag = 0;

BOOL chrg_flg;
static int add_num;
static int Timer;

void p05_chargelink_dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void p05_chargelink_dialog::init_page_dlg()
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
   // ui->label_phone->setText(phonenum);
    //ui->label_phone_2->setText(phonenum_2);
}

void p05_chargelink_dialog::init_page_val()
{
    add_num=0;
    Timer=180;//120
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void p05_chargelink_dialog::start_timer()
{
    init_page_val();
    timer->start(PAGE_FLUSH_TIMER);
}


void p05_chargelink_dialog::timer_handle()
{
     update_page_info();
     update_hmi_page_index();
}


void p05_chargelink_dialog::update_page_info()
{

 //   ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
 //   ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));
    if(0 == delay_time_flag)
    {
        add_num++;
        if(add_num==20)
        {
            add_num=0;
            Timer--;
            if(Timer<=0)
            {
                Timer = 60;
                //printf("************* first CANCE send !!!\n");
                hmi_button_dn_num=CANCEL_BUTTON;
                API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),
                                   sizeof(hmi_button_dn_num));
                ui->label_13->setText(QString::fromUtf8("充电枪未连接，请重试!"));
                delay_time_flag = 1;
            }
        }
    }
    else if(1 == delay_time_flag)
    {
        add_num++;
        if(add_num==20)
        {
            add_num=0;
            Timer--;
            if(Timer<=0)
            {
                Timer = 0;
                //printf("************* second CANCE send !!!\n");
                //ui->label_13->setText(QString::fromUtf8("充电枪连接出错，请拔枪重试!"));                
                hmi_button_dn_num=CANCEL_BUTTON;
                API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),
                                   sizeof(hmi_button_dn_num));
            }
        }
    }
    else
    {

    }
    
    ui->lbl_time->setText(QString::number(Timer,'f',0));
    
    if(language_num == 1)
    {
      //   ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
       // ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
       // ui->pushButton_14->setText(QString::fromUtf8("取       消"));
      //  ui->label_11->setText(QString::fromUtf8("请在120秒内将充电枪插入充电插口"));
       // ui->label_2->setText(QString::fromUtf8("秒"));
  #if 0
        API_Read_DB_Nbyte(PL_CHRGUNLINKERR_FLAG,(BOOL *)(&chrg_flg),sizeof(chrg_flg));
        if(chrg_flg)
        {
            ui->label_11->setText(QString::fromUtf8("充电枪连接超时，请重新刷卡!"));
        }
  #endif
    }
    else if(language_num == 2)
    {
       //   ui->label_logo->setText("AC charging pile");
        ui->label_stubnum->setText("Telephone :");
        ui->pushButton_14->setText("Back");
        ui->label_11->setText(QString::fromUtf8("Checking the connection status ..."));
        ui->label_2->setText(QString::fromUtf8("S"));
    }
    num_move_5++;
    if(num_move_5 == 40)
    {
        num_move_5 = 0;
        move_flag_5 ++;
      //  ui->label->move(400,250);
    }

    if(move_flag_5 == 2)
    {
        move_flag_5 = 0;
      //  ui->label->move(450,210);
    }
}

void p05_chargelink_dialog::update_hmi_page_index()
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

    if(hmi_page_index != PAGEINDEX_CHARGELINK)
    {
        exit_page_dlg();
    }
    else
    {

    }

}

void p05_chargelink_dialog::call_link_err_dlg()
{
    timer->stop();
    if(link_err_dlg){
            delete link_err_dlg;
            link_err_dlg = NULL;
    }
    link_err_dlg = new  Dialog_link_err;
    link_err_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_link_err_timer()),link_err_dlg,SLOT(init_page_dlg()));
    connect(link_err_dlg,SIGNAL(signal_exit_dlg_link()),this,SLOT(exit_page_dlg()));

    emit signal_enable_link_err_timer();
    link_err_dlg->exec();
}


void p05_chargelink_dialog::call_err_dlg()
{
    timer->stop();
    if(err_dlg){
            delete err_dlg;
            err_dlg = NULL;
    }
    err_dlg = new  Dialog_error;
    err_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_err_timer()),err_dlg,SLOT(init_page_dlg()));
    connect(err_dlg,SIGNAL(signal_exit_errdlg_link()),this,SLOT(start_timer()));

    emit signal_enable_err_timer();
    err_dlg->exec();
}

void p05_chargelink_dialog::call_p19_dlg()
{
    timer->stop();
    if(p19_dlg){
            delete p19_dlg;
            p19_dlg = NULL;
    }
    p19_dlg = new  p19_charging_dialog;
    p19_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p19dlg_timer()),p19_dlg,SLOT(init_page_dlg()));
    connect(p19_dlg,SIGNAL(signal_exit_p19dlg()),this,SLOT(exit_page_dlg()));
    connect(p19_dlg,SIGNAL(signal_timer_p19dlg()),this,SLOT(start_timer()));
    emit signal_enable_p19dlg_timer();
    p19_dlg->exec();
}
/*
void p05_chargelink_dialog::call_p06_dlg()
{
    timer->stop();
    if(p06_dlg){
            delete p06_dlg;
            p06_dlg = NULL;
            handle_dlg_p06--;
    }
    p06_dlg = new  p06_chargeconfigrm_dialog;
    p06_dlg->setWindowFlags(Qt::FramelessWindowHint);
    handle_dlg_p06++;

    connect(this,SIGNAL(signal_enable_p06dlg_timer()),p06_dlg,SLOT(init_page_dlg()));
    connect(p06_dlg,SIGNAL(signal_exit_p06dlg()),this,SLOT(exit_page_dlg()));
    emit signal_enable_p06dlg_timer();
    p06_dlg->exec();

}

void p05_chargelink_dialog::call_dlg_1()
{
    timer->stop();
    if(dlg_1){
            delete dlg_1;
            dlg_1 = NULL;

    }

    dlg_1 = new dialog_1 ;
    dlg_1->setWindowFlags(Qt::FramelessWindowHint);
    connect(this,SIGNAL(signal_enable_dlg_1_timer()),dlg_1,SLOT(init_page_dlg()));
    connect(dlg_1,SIGNAL(signal_exit_dlg_1()),this,SLOT(exit_page_dlg()));
    emit signal_enable_dlg_1_timer();
    dlg_1->exec();
}
*/
void p05_chargelink_dialog::exit_page_dlg()
{
    DebugMsg(hmilev,8,"exit_page_dlg\n");
    init_page_val();
    timer->stop();
    emit signal_exit_p05dlg();

    delay_time_flag = 0;

    //delete p05_dlg;
    //p05_dlg = NULL;
}

void p05_chargelink_dialog::on_pushButton_14_clicked()
{
    hmi_button_dn_num=OK_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),
                       sizeof(hmi_button_dn_num));
}
