#include "dialog_err_choose.h"
#include "ui_dialog_err_choose.h"
#include "globalhmi.h"

dialog_err_choose::dialog_err_choose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_err_choose)
{
    ui->setupUi(this);
}

dialog_err_choose::~dialog_err_choose()
{
    delete ui;
}

void dialog_err_choose::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void dialog_err_choose::init_page_val()
{
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void dialog_err_choose::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void dialog_err_choose::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void dialog_err_choose::update_page_info()
{
     
}

void dialog_err_choose::update_hmi_page_index(void)
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
   if(hmi_page_index != PAGEINDEX_ERR_CHOOSE)
   {
       exit_page_dlg();
   }
   else
   {

   }
}

void dialog_err_choose::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_dlg();
    //delete end_dlg;
    //end_dlg = NULL;
}

void dialog_err_choose::on_pbtn_local_err_clicked()
{
    
    hmi_button_dn_num=LOCAL_ERR_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));  

    //hmi_page_index=PAGEINDEX_LOCAL_ERR;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

}

void dialog_err_choose::on_pbtn_remote_err_clicked()
{
    
    hmi_button_dn_num=REMOTE_ERR_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));  

    //hmi_page_index=PAGEINDEX_REMOTE_ERR;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

}

void dialog_err_choose::on_pbtn_cancel_clicked()
{
    hmi_button_dn_num=CANCEL_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));  

    //hmi_page_index=PAGEINDEX_SETPAGE_SIX;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

}
