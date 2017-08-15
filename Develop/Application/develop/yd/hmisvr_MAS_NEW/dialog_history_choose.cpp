#include "dialog_history_choose.h"
#include "ui_dialog_history_choose.h"
#include "globalhmi.h"


Dialog_history_choose::Dialog_history_choose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_history_choose)
{
    ui->setupUi(this);
}

Dialog_history_choose::~Dialog_history_choose()
{
    delete ui;
}

void Dialog_history_choose::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_history_choose::init_page_val()
{
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void Dialog_history_choose::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_history_choose::on_pbtn_cancel_clicked()
{
    hmi_button_dn_num=CANCEL_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),
                       sizeof(hmi_button_dn_num));

    //hmi_page_index=PAGEINDEX_SETPAGE_SIX;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

}

void Dialog_history_choose::on_pbtn_query_clicked()
{   

    hmi_button_dn_num=HISTORYCHECK_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),
                       sizeof(hmi_button_dn_num));

    //hmi_page_index=PAGEINDEX_HISTORYCHECK;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

}

void Dialog_history_choose::on_pbtn_query_net_clicked()
{

    hmi_button_dn_num=HISTORYNET_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),
                       sizeof(hmi_button_dn_num));

    //hmi_page_index=PAGEINDEX_HISTORY_NET;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

}
static int  num_add_end = 0;
void Dialog_history_choose::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void Dialog_history_choose::update_page_info()
{

}

void Dialog_history_choose::update_hmi_page_index(void)
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
   if(hmi_page_index != PAGEINDEX_HISTORY_CHOOSE)
   {
       exit_page_dlg();
   }
   else
   {

   }
}

void Dialog_history_choose::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_dlg();
    //delete end_dlg;
    //end_dlg = NULL;
}
