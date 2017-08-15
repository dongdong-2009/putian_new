#include "dialog_first_err.h"
#include "ui_dialog_first_err.h"
#include "globalhmi.h"

Dialog_first_err::Dialog_first_err(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_first_err)
{
    ui->setupUi(this);
}

Dialog_first_err::~Dialog_first_err()
{
    delete ui;
}

static char web_real[50]={};

void Dialog_first_err::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_first_err::init_page_val()
{
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
    ui->label_phone_2->setText(phonenum);
    ui->label_phone_3->setText(phonenum_2);
    ui->label_piccode->setPixmap(QPixmap("/usr/APP/1.png"));
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void Dialog_first_err::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

static int  num_add_end = 0;
void Dialog_first_err::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void Dialog_first_err::update_page_info()
{
    ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));

    if(language_num == 1)
    {
          //ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
      //ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
    }
    else  if(language_num == 2)
    {
         // ui->label_logo->setText("AC charging pile");
          ui->label_stubnum->setText("Telephone :");
    }
    else
    {

    }

    memset(web_real,0,sizeof(web_real));
    memset(Tempor_name,0,sizeof(Tempor_name));
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"real_websize");
    if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
    {
        memcpy(web_real,Tempor_name,sizeof(web_real));
    }
    else
    {
        memset(web_real,0,sizeof(web_real));
    }
    ui->label_stubnum_3->setText(web_real);
    
}

void Dialog_first_err::update_hmi_page_index(void)
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
   if(hmi_page_index != PAGEINDEX_FIRST_ERR)
   {
       exit_page_dlg();
   }
   else
   {

   }
}

void Dialog_first_err::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_firsterr();
    //delete end_dlg;
    //end_dlg = NULL;
}

void Dialog_first_err::on_pbtn_setpara_clicked()
{
   hmi_button_dn_num=SET_PARA_BUTTON;
   API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}
