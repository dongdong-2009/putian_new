#include "p24_setpara_sub6_dialog.h"
#include "ui_p24_setpara_sub6_dialog.h"
#include "globalhmi.h"
#include <dirent.h>

p24_setpara_sub6_dialog::p24_setpara_sub6_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::p24_setpara_sub6_dialog)
{
    ui->setupUi(this);
}

p24_setpara_sub6_dialog::~p24_setpara_sub6_dialog()
{
    delete ui;
}

void p24_setpara_sub6_dialog::changeEvent(QEvent *e)
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

static int data_copy_count=0;
static int add_num = 0;
static int Timer = 0;
static int time_countdown_flag=0;

void p24_setpara_sub6_dialog::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(SETPAGE_FLUSH_TIMER);
    init_page_val();
    btn_press();
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
}



void p24_setpara_sub6_dialog::init_page_val()
{

    ui->frame_1->move(25,95);
}

void p24_setpara_sub6_dialog::start_timer()
{
    //timer->start(PAGE_FLUSH_TIMER);
    timer->start(5000);
}

void p24_setpara_sub6_dialog::btn_press()
{
    QPushButton* array[14]={0};
    array[0] = ui->pbtn_num0;
    array[1] = ui->pbtn_num1;
    array[2] = ui->pbtn_num2;
    array[3] = ui->pbtn_num3;
    array[4] = ui->pbtn_num4;
    array[5] = ui->pbtn_num5;
    array[6] = ui->pbtn_num6;
    array[7] = ui->pbtn_num7;
    array[8] = ui->pbtn_num8;
    array[9] = ui->pbtn_num9;
    array[10] = ui->pbtn_dot;
    array[11] = ui->pbtn_back;
    array[12] = ui->pbtn_cancel;
    array[13] = ui->pbtn_ok;

    int num = 0;
    for(num = 0; num < 14;num++)
    {
        array[num]->setStyleSheet("QPushButton{border-image: url(:/icon/qrc/keyboard-b/T.png);}\
                                  QPushButton:pressed{border-image: url(:/icon/qrc/keyboard-b/T_press.png);}");
    }

}

void p24_setpara_sub6_dialog::timer_handle()
{
     update_page_info();
     update_hmi_page_index();
}


void p24_setpara_sub6_dialog::update_page_info()
{
    if(time_countdown_flag)
    {
        add_num++;
        if(add_num==20)
        {
            add_num=0;
            Timer--;
            if(Timer<=0)
            {
                Timer = 0;
                time_countdown_flag = 0;
                data_copy_count = 0;
                ui->label_tip->setText(QString::fromUtf8(" "));
            }
        }

    }

}

void p24_setpara_sub6_dialog::update_hmi_page_index()
{

    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
    if(hmi_page_index != PAGEINDEX_SETPAGE_SIX)
    {
        exit_page_dlg();
    }
    else
    {

    }
}

void p24_setpara_sub6_dialog::exit_page_dlg()
{
    DebugMsg(hmilev,8,"exit_page_dlg\n");
    init_page_val();
    timer->stop();
    emit signal_exit_p24dlg();
    //delete p24_dlg;
    //p24_dlg = NULL;

    data_copy_count = 0;
    time_countdown_flag=0;
}

void p24_setpara_sub6_dialog::call_p18_dlg()
{
#if 0
    timer->stop();
    if(p18_dlg){
            delete p18_dlg;
            p18_dlg = NULL;

    }
    p18_dlg = new  p18_setpara_sub5_dialog;
    p18_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p18dlg_timer()),p18_dlg,SLOT(init_page_dlg()));
    connect(p18_dlg,SIGNAL(signal_exit_p18dlg()),this,SLOT(exit_page_dlg()));
    connect(p18_dlg,SIGNAL(signal_timer_p18dlg()),this,SLOT(start_timer()));
    emit signal_enable_p18dlg_timer();
    p18_dlg->exec();
#endif
}


//数据导出
int p24_setpara_sub6_dialog::on_pbtn_dateout_clicked()
{
    system("cp /usr/data/* /media/sda1/");
    system("cp /usr/data/* /media/sda2/");
    system("cp /usr/data/* /media/sda3/");
    system("cp /usr/data/* /media/sda4/");

    DIR *dir1;
    dir1 = opendir("/media/sda1");
    if(!dir1)
    {
        //printf("******************** sda1\n");
    }
    else
    {
        ui->label_tip->setText(QString::fromUtf8("数据拷贝完成!"));
        data_copy_count++;
        //return 0;
    }
    closedir(dir1);

    DIR *dir2;
    dir2 = opendir("/media/sda2");
    if(!dir2)
    {
        //printf("******************** sda2 \n");
    }
    else
    {
        ui->label_tip->setText(QString::fromUtf8("数据拷贝完成!"));
        data_copy_count++;
        //return 0;
    }
    closedir(dir2);

    DIR *dir3;
    dir3 = opendir("/media/sda3");
    if(!dir3)
    {
        //printf("******************** sda3 \n");
    }
    else
    {
        ui->label_tip->setText(QString::fromUtf8("数据拷贝完成!"));
        data_copy_count++;
        //return 0;
    }
    closedir(dir3);

    DIR *dir4;
    dir4 = opendir("/media/sda4/System Volume Information");
    if(!dir4)
    {
        //printf("******************** sda4 \n");
    }
    else
    {
        ui->label_tip->setText(QString::fromUtf8("数据拷贝完成!"));
        data_copy_count++;
        //return 0;
    }
    closedir(dir4);

    if(0 == data_copy_count)
    {
        ui->label_tip->setText(QString::fromUtf8("存储设备未识别!"));

    }
    else
    {
        printf("************* 1 - data_copy_count = %d\n",data_copy_count);
    }

    time_countdown_flag = 1;
    Timer = 3;
}

//上翻
void p24_setpara_sub6_dialog::on_pbtn_up_clicked()
{
    hmi_button_dn_num=PAGEUP_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

    //hmi_page_index=PAGEINDEX_SETPAGE_FIVE;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
    //printf("************%s,%d,Button: pbtn_up**********\n"，__FILE__,__LINE__);

}

//下翻
void p24_setpara_sub6_dialog::on_pbtn_down_clicked()
{
    //hmi_button_dn_num=PAGEDOWN_BUTTON;
    //API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

//设置6: 取消
void p24_setpara_sub6_dialog::on_pbtn_cancel_clicked()
{
    hmi_button_dn_num=CANCEL_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

    //hmi_page_index=PAGEINDEX_MAIN;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

//设置6: 确定
void p24_setpara_sub6_dialog::on_pbtn_ok_clicked()
{
    DebugMsg(hmilev,5,"on_pbtn_enter_clicked\n");

    hmi_button_dn_num=OK_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

    //数组初始化，以及配置文件写入；

    //hmi_page_index=PAGEINDEX_MAIN;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

//故障记录
void p24_setpara_sub6_dialog::on_pbtn_err_clicked()
{
    hmi_button_dn_num=ERRORCHECK_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

    //hmi_page_index=PAGEINDEX_ERR_CHOOSE;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

}

//历史记录
void p24_setpara_sub6_dialog::on_pbtn_history_clicked()
{
    hmi_button_dn_num=HISTORYCHECK_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

    history_setpage = 1;
    //hmi_page_index=PAGEINDEX_HISTORY_CHOOSE;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
}



