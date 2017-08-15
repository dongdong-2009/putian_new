#include "dialog_not_putiancard.h"
#include "ui_dialog_not_putiancard.h"
#include "globalhmi.h"

dialog_not_putiancard::dialog_not_putiancard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_not_putiancard)
{
    ui->setupUi(this);

    //printf("*********** %s,Ui:  not_putiancard **********\n",__FILE__);
}

dialog_not_putiancard::~dialog_not_putiancard()
{
    delete ui;
}

static int add_num;
static int Timer;

void dialog_not_putiancard::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void dialog_not_putiancard::init_page_val()
{
    add_num=0;
    Timer=3;//120
    //ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    //ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void dialog_not_putiancard::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

//static int  num_add_end = 0;
void dialog_not_putiancard::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void dialog_not_putiancard::update_page_info()
{
    add_num++;
    if(add_num==20)
    {
        add_num=0;
        Timer--;
        if(Timer<=0)
        {
            Timer = 0;
            //hmi_page_index =  PAGEINDEX_MAIN;
            //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

            hmi_button_dn_num=CANCEL_BUTTON;
            API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),
                               sizeof(hmi_button_dn_num));
        }
    }

    ui->label_time->setText(QString::number(Timer,'f',0));
}

void dialog_not_putiancard::update_hmi_page_index(void)
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
   if(hmi_page_index != PAGEINDEX_NOT_PUTIANCARD)
   {
       exit_page_dlg();
   }
   else
   {

   }
}

void dialog_not_putiancard::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_dlg();
    //delete end_dlg;
    //end_dlg = NULL;
}

