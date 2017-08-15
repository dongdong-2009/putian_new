#include "p19_charging_dialog.h"
#include "ui_p19_charging_dialog.h"
#include "globalhmi.h"

#define DEF_SUPPORT_FLUSH_PIC

p19_charging_dialog::p19_charging_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::p19_charging_dialog)
{
    ui->setupUi(this);
}

p19_charging_dialog::~p19_charging_dialog()
{
    delete ui;
}

void p19_charging_dialog::changeEvent(QEvent *e)
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

void p19_charging_dialog::init_page_dlg()
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
}

void p19_charging_dialog::init_page_val()
{
        UINT8 data = NO_BUTTON;
        API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));

        ui->label_speaker->setText(QString::fromUtf8("如需结束充电,请刷卡!"));

        FLOAT32 f32_data = 0;
        UINT16 u16_data=0;
        UINT8 APP_flag = 0;
     //   UINT8 tempvalue=0;


        API_Read_DB_Nbyte(PL_CHRTOTALUSE_TIME,(INT8 *)(&u16_data),sizeof(u16_data));
        ui->lbl_time_hour->setText(QString::number(u16_data/60,'f',0));
        ui->lbl_time_min->setText(QString::number(u16_data%60,'f',0));

        API_Read_DB_Nbyte(PL_CHROUTPT_VOLT,(INT8 *)(&f32_data),sizeof(f32_data));
        ui->lbl_output_voltage->setText(QString::number(f32_data,'f',1));

        API_Read_DB_Nbyte(PL_CHROUTPT_CURRENT,(INT8 *)(&f32_data),sizeof(f32_data));
        ui->lbl_ouput_current->setText(QString::number(f32_data,'f',1));

        API_Read_DB_Nbyte(PL_CHRUSED_KWH,(INT8 *)(&f32_data),sizeof(f32_data));
        ui->lbl_caculate_energy->setText(QString::number(f32_data,'f',2));
     //   s_pic_count=PIC_MIN_COUNT;

         API_Read_DB_Nbyte(PL_APP_FLAG,(char*)&APP_flag,sizeof(APP_flag));
         if(APP_flag)
         {
             ui->pbtn_app->move(450,274);
         }
         else
        {
            ui->pbtn_app->move(450,700);
         }

        update_page_info();

}


void p19_charging_dialog::on_pbtn_app_clicked()
{
    hmi_button_dn_num=OK_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),
                       sizeof(hmi_button_dn_num));
}

void p19_charging_dialog::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
}

void p19_charging_dialog::timer_handle()
{
     update_page_info();
     update_hmi_page_index();
}
static int add_num=0;
int add_number=0;
BOOL connect_err_flag = 0;
void p19_charging_dialog::update_page_info()
{
    FLOAT32 f32_data = 0;
    UINT16 u16_data=0;
    UINT8 tempvalue=0;
    UINT32 error_state_flag = 0;
    BOOL net_flg=0;

    //ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
   // ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));

    ui->pbtn_setnet->setStyleSheet("border-image: url(:/icon/qrc/icon/0.png);");

    API_Read_DB_Nbyte(PL_NETWORKLINKSTATE_FLAG,(BOOL *)(&net_flg),sizeof(net_flg));
    if(net_flg)
    {
      add_num=0;
      ui->pbtn_setnet->setStyleSheet("border-image: url(:/icon/qrc/icon/1.png);");
    }
    else
    {
      add_num++;
      if(add_num>=750)
      {
          ui->pbtn_setnet->setStyleSheet("border-image: url(:/icon/qrc/icon/0.png);");
          add_num=0;
      }
    }

    if(language_num == 1)
    {
       //   ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));

        //  ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
         // ui->label_char_time->setText(QString::fromUtf8("充 电 时 间 :"));
      //    ui->label_energy->setText(QString::fromUtf8("充 电 电 量 :"));
   //       ui->label_volt->setText(QString::fromUtf8("输 出 电 压 :"));
   //       ui->label_cur->setText(QString::fromUtf8("输 出 电 流 :"));

     //     ui->lbl_time_hour_2->setText(QString::fromUtf8("时"));
    //      ui->lbl_time_hour_3->setText(QString::fromUtf8("分"));

          API_Read_DB_Nbyte(PL_STUBERRSTATE_FLAG,(int *)(&error_state_flag),sizeof(error_state_flag));

          //printf("****************error_state_flag = %d,%s**************\n",error_state_flag,__FILE__);

          if((error_state_flag > 0) && (error_state_flag != 0x800000))
          {
              if( (error_state_flag & (1<<30)) )
              {
                  ui->label_speaker_2->setText(QString::fromUtf8("输入过压"));
              }
              if( (error_state_flag & (1<<31)) )
              {
                  ui->label_speaker_2->setText(QString::fromUtf8("输入欠压"));
              }
              ui->label_speaker_2->setText(QString::fromUtf8("设备故障，暂停使用,请刷卡拔枪结算!"));
              ui->label_title->setText(QString::fromUtf8("充 电 故 障"));
          }
          else if(0x800000 == error_state_flag )
          {
              ui->label_title->setText(QString::fromUtf8("充 电 中 "));
              ui->label_speaker_2->setText(QString::fromUtf8("网络故障"));
          }else{
              ui->label_title->setText(QString::fromUtf8("充 电 中 "));
              ui->label_speaker_2->setText(QString::fromUtf8("良好"));
          }

          API_Read_DB_Nbyte(PL_TitleWaring_FLAG,(char*)&tempvalue,sizeof(tempvalue));
          if(tempvalue==1)
          {
               //ui->label_title->setText(QString::fromUtf8("按 时 间 充 电 完 成"));
               ui->label_title->setText(QString::fromUtf8("充 电 完 成"));

          }
          else if(tempvalue==2)
          {
               //ui->label_title->setText(QString::fromUtf8("按 电 量 充 电 已 完 成"));
               ui->label_title->setText(QString::fromUtf8("充 电 完 成"));

          }
          else if(tempvalue==3)
          {
              //ui->label_speaker->setText(QString::fromUtf8("如需结束本次充电,请刷卡!"));
              ui->label_title->setText(QString::fromUtf8("充 电 结 束"));
              //ui->label_speaker_2->setText(QString::fromUtf8("设备故障，暂停使用"));
          }
          else if(tempvalue==4)
          {
              ui->label_title->setText(QString::fromUtf8("远 程 停 机"));
          }
          else if(tempvalue==5)
          {
              //ui->label_speaker->setText(QString::fromUtf8("如需结束本次充电,请刷卡!"));
              ui->label_title->setText(QString::fromUtf8("充电异常结束,请刷卡拔枪结算!"));
              //ui->label_speaker_2->setText(QString::fromUtf8("良 好"));
          }
          else
          {
              ui->label_title->setText(QString::fromUtf8("充 电 中 "));
              //ui->label_speaker_2->setText(QString::fromUtf8("良 好"));
          }

          API_Read_DB_Nbyte(PL_CARDPROMPT_FLAG,(char*)&tempvalue,sizeof(tempvalue));
          if(tempvalue==1)
          {
               ui->label_speaker->setText(QString::fromUtf8("刷卡不正确，请刷本次服务所提供的加电卡"));

          }
          else if(tempvalue==2)
          {
               ui->label_speaker->setText(QString::fromUtf8("如需结束本次充电,请拔车辆端枪!"));

          }
          else if(tempvalue==3)
          {
               ui->label_speaker->setText(QString::fromUtf8("如需结束本次充电,请重新扫描二维码!"));

          }
          else
          {
              ui->label_speaker->setText(QString::fromUtf8("如需结束充电,请刷卡!"));
          }

    }
    else  if(language_num == 2)
    {
       //   ui->label_logo->setText("AC charging pile");//lbl_time_hour_2
          ui->label_title->setText("Charge State");
          ui->label_stubnum->setText("Telephone :");
          ui->label_char_time->setText("Time :");
          ui->label_energy->setText("Energy :");
          ui->label_volt->setText(" Volt :");
          ui->label_cur->setText(" Current :");
          ui->lbl_time_hour_2->setText("H");
          ui->lbl_time_hour_3->setText("M");

          API_Read_DB_Nbyte(PL_STUBERRSTATE_FLAG,(int *)(&error_state_flag),sizeof(error_state_flag));
          if((error_state_flag > 0) && (error_state_flag != 0x800000))
          {
              ui->label_speaker->setText("Equipment error, please swipe your card !");
          }

          API_Read_DB_Nbyte(PL_CARDPROMPT_FLAG,(char*)&tempvalue,sizeof(tempvalue));
          if(tempvalue)
          {
            //   call_diff_card_dlg();
             ui->label_speaker->setText("The card you swiped is not the card  providing services!");
            //  ui->label_10->setText("The card you swiped is not the card  providing services!");
          }
    }

    API_Read_DB_Nbyte(PL_CHRTOTALUSE_TIME,(INT8 *)(&u16_data),sizeof(u16_data));
    ui->lbl_time_hour->setText(QString::number(u16_data/60,'f',0));
    ui->lbl_time_min->setText(QString::number(u16_data%60,'f',0));
    ui->label_piccode->setPixmap(QPixmap("/usr/APP/1.png"));

    API_Read_DB_Nbyte(PL_CHROUTPT_VOLT,(INT8 *)(&f32_data),sizeof(f32_data));

   // ErrMsg("$$$$VOLT=[%f]\n",f32_data);

    ui->lbl_output_voltage->setText(QString::number(f32_data,'f',1));

    API_Read_DB_Nbyte(PL_CHROUTPT_CURRENT,(INT8 *)(&f32_data),sizeof(f32_data));

   // ErrMsg("$$$$Current=[%f]\n",f32_data);

    ui->lbl_ouput_current->setText(QString::number(f32_data,'f',1));

    API_Read_DB_Nbyte(PL_CHRUSED_KWH,(INT8 *)(&f32_data),sizeof(f32_data));
    ui->lbl_caculate_energy->setText(QString::number(f32_data,'f',2));

    /*
    API_Read_DB_Nbyte(PL_CHR_STATE,(INT8 *)(&u16_data),sizeof(u16_data));
    if(u16_data==CUR_CHG_STAT_CHARGING)
    {
        ui->lbl_chg_cur_stat->setText(QString::fromUtf8("充电中"));

    }else
    if(u16_data==CUR_CHG_STAT_STOP)
    {
        ui->lbl_chg_cur_stat->setText(QString::fromUtf8("充电结束"));
    }else{
        ui->lbl_chg_cur_stat->setText(QString::fromUtf8("充电出错"));
    }

    API_Read_DB_Nbyte(PL_CHRSTART_KWH,(INT8 *)(&f32_data),sizeof(f32_data));
    ui->lbl_init_energy->setText(QString::number(f32_data,'f',2));

    API_Read_DB_Nbyte(PL_CHRCURRRENT_KWH,(INT8 *)(&f32_data),sizeof(f32_data));
    ui->lbl_current_energy->setText(QString::number(f32_data,'f',2));
*/
}

void p19_charging_dialog::update_hmi_page_index()
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

    if(hmi_page_index != PAGEINDEX_ACCHARGEPROCESS)
    {
        exit_page_dlg();
    }
    else
    {

    }
}

void p19_charging_dialog::call_checkcard_dlg()
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

void p19_charging_dialog::call_diff_card_dlg()
{
    timer->stop();
    if(diff_card_dlg){
            delete diff_card_dlg;
            diff_card_dlg = NULL;
    }
    diff_card_dlg = new  Dialog_diff_card;
    diff_card_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_diff_card_timer()),diff_card_dlg,SLOT(init_page_dlg()));
    connect(diff_card_dlg,SIGNAL(signal_exit_diff_card()),this,SLOT(start_timer()));

    emit signal_enable_diff_card_timer();
    diff_card_dlg->exec();
}

void p19_charging_dialog::call_link_err_dlg()
{
    timer->stop();
    if(link_err_dlg){
            delete link_err_dlg;
            link_err_dlg = NULL;
    }
    link_err_dlg = new  Dialog_link_err;
    link_err_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_link_err_timer()),link_err_dlg,SLOT(init_page_dlg()));
    connect(link_err_dlg,SIGNAL(signal_exit_dlg_charge()),this,SLOT(start_timer()));

    emit signal_enable_link_err_timer();
    link_err_dlg->exec();
}

void p19_charging_dialog::call_err_dlg()
{
    timer->stop();
    if(err_dlg){
            delete err_dlg;
            err_dlg = NULL;
    }
    err_dlg = new  Dialog_error;
    err_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_err_timer()),err_dlg,SLOT(init_page_dlg()));
    connect(err_dlg,SIGNAL(signal_exit_errdlg_charging()),this,SLOT(start_timer()));

    emit signal_enable_err_timer();
    err_dlg->exec();
}

void p19_charging_dialog::call_p21_dlg()
{
    timer->stop();
    if(p21_dlg){
            delete p21_dlg;
            p21_dlg = NULL;
    }
    p21_dlg = new  p21_judge_continue;
    p21_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p21dlg_timer()),p21_dlg,SLOT(init_page_dlg()));
    connect(p21_dlg,SIGNAL(signal_exit_p21dlg()),this,SLOT(exit_page_dlg()));
//    connect(p21_dlg,SIGNAL(signal_timer_p21dlg()),this,SLOT(start_timer()));
    connect(p21_dlg,SIGNAL(signal_timer_p21dlg()),this,SLOT(call_p05_dlg()));
    emit signal_enable_p21dlg_timer();
    p21_dlg->exec();
}

void p19_charging_dialog::call_p05_dlg()
{
    timer->stop();
    emit signal_timer_p19dlg();
    delete p19_dlg;
    p19_dlg = NULL;
}

void p19_charging_dialog::call_p20_dlg()
{
    timer->stop();
    if(p20_dlg){
            delete p20_dlg;
            p20_dlg = NULL;
            handle_dlg_p20--;
    }
    p20_dlg = new  p20_payoff_dialog;
    p20_dlg->setWindowFlags(Qt::FramelessWindowHint);
    handle_dlg_p20++;

    connect(this,SIGNAL(signal_enable_p20dlg_timer()),p20_dlg,SLOT(init_page_dlg()));
    connect(p20_dlg,SIGNAL(signal_exit_p20dlg()),this,SLOT(exit_page_dlg()));
    emit signal_enable_p20dlg_timer();
    p20_dlg->exec();
}

/*
void p19_charging_dialog::call_dlg_1()
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
void p19_charging_dialog::call_dlg_2()
{
    timer->stop();
    if(dlg_2){
            delete dlg_2;
            dlg_2 = NULL;
    }
    dlg_2 = new  dialog_2;
    dlg_2->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_dlg_2_timer()),dlg_2,SLOT(init_page_dlg()));
    connect(dlg_2,SIGNAL(signal_exit_dlg_2()),this,SLOT(exit_page_dlg()));
    connect(dlg_2,SIGNAL(signal_timer_dlg_2()),this,SLOT(start_timer()));
    emit signal_enable_dlg_2_timer();
    dlg_2->exec();
}

void p19_charging_dialog::exit_page_dlg()
{
    DebugMsg(hmilev,8,"exit_page_dlg\n");
    init_page_val();
    timer->stop();
    emit signal_exit_p19dlg();
   // delete p19_dlg;
  //  p19_dlg = NULL;
}

