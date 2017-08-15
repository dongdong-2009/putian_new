#include "dialog_err_carconfirm.h"
#include "ui_dialog_err_carconfirm.h"
#include "globalhmi.h"

dialog_err_carconfirm::dialog_err_carconfirm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_err_carconfirm)
{
    ui->setupUi(this);
}

dialog_err_carconfirm::~dialog_err_carconfirm()
{
    delete ui;
}

static int add_num;
static int Timer;

void dialog_err_carconfirm ::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void dialog_err_carconfirm ::init_page_val()
{
    add_num=0;
    Timer=5;//120
}

void dialog_err_carconfirm ::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
}

void dialog_err_carconfirm ::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void dialog_err_carconfirm ::update_page_info()
{
    //printf("***********************************************\n");
    //printf("***************** carnum_back = %s,%s***************\n",carnum_back,__FILE__);
    ui->label_carnumber->setText(QString::fromUtf8(carnum_back));

    add_num++;
    if(add_num==20)
    {
        add_num=0;
        Timer--;
        if(Timer<=0)
        {
            Timer = 0;
            hmi_page_index =  PAGEINDEX_CARNUM;
            API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
        }
    }
    ui->lbl_time->setText(QString::number(Timer,'f',0));
}

void dialog_err_carconfirm ::update_hmi_page_index(void)
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
   if(hmi_page_index != PAGEINDEX_ERR_CARCONFIRM)
   {
       exit_page_dlg();
   }
   else
   {

   }
}

void dialog_err_carconfirm ::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_dlg();
    //delete end_dlg;
    //end_dlg = NULL;
}

