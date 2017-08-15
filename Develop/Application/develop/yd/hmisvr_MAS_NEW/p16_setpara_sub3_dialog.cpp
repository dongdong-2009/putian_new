#include "p16_setpara_sub3_dialog.h"
#include "ui_p16_setpara_sub3_dialog.h"
#include "globalhmi.h"


p16_setpara_sub3_dialog::p16_setpara_sub3_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::p16_setpara_sub3_dialog)
{
    ui->setupUi(this);

}
p16_setpara_sub3_dialog::~p16_setpara_sub3_dialog()
{
    delete ui;
}

void p16_setpara_sub3_dialog::changeEvent(QEvent *e)
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

void p16_setpara_sub3_dialog::init_page_dlg()
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

BOOL soft_flg=FALSE;
BOOL source_flg=FALSE;
BOOL dev_flg=FALSE;
BOOL money_flg=FALSE;
INT8 softtime[24]={0};
int change_num = 0;         //0 for num; 1 for letter;
void p16_setpara_sub3_dialog::init_page_val()
{
        UINT8 data = NO_BUTTON;
        API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
        API_Read_DB_Nbyte(PL_SOFT_TIME,(INT8 *)(&softtime),sizeof(softtime));

        change_num = 0;
         soft_len=0;
         btn_devwd_len=0;
         cost_len=0;
         source_len=0;
         money_len=0;

         fmaxi=0;

         memset(soft,0,sizeof(soft));
         memset(cost,0,sizeof(cost));
         memset(source,0,sizeof(source));
         memset(btn_devwd,0,sizeof(btn_devwd));
         memset(money,0,sizeof(money));
/*
         memset(Tempor_name,0,sizeof(Tempor_name));
         Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
         Inibuf_init(Key_name,BUFFERLEN_32,"createtime");
         if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
         {
                ui->lbl_ch_time->setText(QString::fromLocal8Bit(guestname));
         }
         else
         {
                ui->lbl_ch_time->setText(" ");
         }
*/
         ui->lbl_ch_time->setText(QString::fromLocal8Bit(softtime));
         int net_temp;
         net_temp=0;
         Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
         Inibuf_init(Key_name,BUFFERLEN_32,"networkservice");
         net_check= read_profile_int(Section_name, Key_name,net_temp,config_path);

        Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
        Inibuf_init(Key_name,BUFFERLEN_32,"DataPackTranformWay");
        line_check= read_profile_int(Section_name, Key_name,net_temp,config_path);

        float max_temp=0;
        Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
        Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestcurrent");
        fmaxi= read_profile_float(Section_name, Key_name,max_temp,config_path);
        sprintf(maxi,"%0.2f",fmaxi);

        //3.13 增加
        connect_net_way = line_check;

        Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
        Inibuf_init(Key_name,BUFFERLEN_32,"palate_carnum");
        palate_check= read_profile_int(Section_name, Key_name,net_temp,config_path);

        memset(Tempor_name,0,sizeof(Tempor_name));
        Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
        Inibuf_init(Key_name,BUFFERLEN_32,"stubcode");

        if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
        {
            memcpy(btn_devwd,Tempor_name,sizeof(btn_devwd));
            dev_flg=TRUE;
        }
        else
        {
            memset(btn_devwd,0,sizeof(btn_devwd));
        }

        memset(Tempor_name,0,sizeof(Tempor_name));
        Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
        Inibuf_init(Key_name,BUFFERLEN_32,"electricityprice");
        if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
        {
            memcpy(money,Tempor_name,sizeof(money));
            money_flg=TRUE;
        }
        else
        {
            memset(money,0,sizeof(money));
        }

        memset(Tempor_name,0,sizeof(Tempor_name));
        Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
        Inibuf_init(Key_name,BUFFERLEN_32,"softwareversion");

        if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
        {
            char temp_soft[5]={0};
            memcpy(temp_soft,Tempor_name,sizeof(temp_soft));

           // printf("%x   %x   %x  %x \r\n",temp_soft[0],temp_soft[1],temp_soft[2],temp_soft[3]);

            sprintf(soft,"%d.%d.%d.%d",(temp_soft[0]-48),(temp_soft[1]-48),(temp_soft[2]-48),(temp_soft[3]-48));
            /*
            int temp_a,temp_b,temp_c,temp_d;
            temp_a = toInt(0,16);
            sprintf(soft,"%d.%d.%d.%d",temp_a,temp_b,temp_c,temp_d);
*/
            soft_flg=TRUE;
        }
        else
        {
            memset(soft,0,sizeof(soft));
        }

        memset(Tempor_name,0,sizeof(Tempor_name));
        Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
        Inibuf_init(Key_name,BUFFERLEN_32,"meterfactor");

        if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
        {
            memcpy(cost,Tempor_name,sizeof(cost));
        }
        else
        {
            memset(cost,0,sizeof(cost));
        }

        memset(Tempor_name,0,sizeof(Tempor_name));
        Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
        Inibuf_init(Key_name,BUFFERLEN_32,"propertycode");

        if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
        {
            memcpy(source,Tempor_name,sizeof(source));
            source_flg=TRUE;
        }
        else
        {
            memset(source,0,sizeof(source));
        }

}

void p16_setpara_sub3_dialog::start_timer()
{
    timer->start(SETPAGE_FLUSH_TIMER);
}


void p16_setpara_sub3_dialog::timer_handle()
{
     update_page_info();
     update_hmi_page_index();
}

void p16_setpara_sub3_dialog::btn_press()
{

    QPushButton* array[16]={0};
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
    array[12] = ui->pbtn_go;
    array[13] = ui->pbtn_ok;
    array[14] = ui->pbtn_up;
    array[15] = ui->pbtn_down;
    //array[16] = ui->pbtn_change;
    int num = 0;
    for(num = 0; num < 16;num++)
    {
        array[num]->setStyleSheet("QPushButton{border-image: url(:/icon/qrc/keyboard-b/T.png);}\
                                  QPushButton:pressed{border-image: url(:/icon/qrc/keyboard-b/T_press.png);}");
    }

}

void p16_setpara_sub3_dialog::update_page_info()
{
    if(change_num)
    {
        ui->pbtn_num1->setText("A");
        ui->pbtn_num2->setText("B");
        ui->pbtn_num3->setText("C");
        ui->pbtn_num4->setText("D");
        ui->pbtn_num5->setText("E");
        ui->pbtn_num6->setText("F");
    }
    else
    {
        ui->pbtn_num1->setText("1");
        ui->pbtn_num2->setText("2");
        ui->pbtn_num3->setText("3");
        ui->pbtn_num4->setText("4");
        ui->pbtn_num5->setText("5");
        ui->pbtn_num6->setText("6");
    }

    if(language_num == 1)
    {
       // ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
       // ui->label_stubnum->setText(QString::fromUtf8(" 客  服  热  线  :"));
    }
    else  if(language_num == 2)
    {
        //  ui->label_logo->setText("AC charging pile");
          ui->label_stubnum->setText("Telephone :");
    }

        ui->lbl_dev_sn->setText(btn_devwd);
        ui->lbl_soft_ver->setText(soft);
        ui->lbl_cost->setText(money);
        ui->lbl_source_sn->setText(source);

        if(fmaxi==16)
        {
            ui->pbtn_16->setChecked(TRUE);
            ui->pbtn_32->setChecked(FALSE);
        }
        else if(fmaxi==32)
        {
            ui->pbtn_16->setChecked(FALSE);
            ui->pbtn_32->setChecked(TRUE);
        }

        if(palate_check)
        {
            ui->open_palate_btn->setChecked(TRUE);
            ui->close_palate_btn->setChecked(FALSE);
        }
        else
        {
            ui->open_palate_btn->setChecked(FALSE);
            ui->close_palate_btn->setChecked(TRUE);
        }

        if(net_check)
        {
            ui->start_btn->setChecked(TRUE);
            ui->cancle_btn->setChecked(FALSE);
        }
        else
        {
            ui->start_btn->setChecked(FALSE);
            ui->cancle_btn->setChecked(TRUE);

        }



        if(line_check)
        {
            //wifi
            if(line_check==10)
            {
                ui->wifi_btn->setChecked(TRUE);
                ui->liantong_btn->setChecked(FALSE);
                ui->yidong_btn->setChecked(FALSE);
                ui->dianxin_btn->setChecked(FALSE);
                ui->online_btn->setChecked(FALSE);
            }//CDMA2000 - YIDONG
            else  if(line_check==13)
            {
                ui->wifi_btn->setChecked(FALSE);
                ui->liantong_btn->setChecked(FALSE);
                ui->yidong_btn->setChecked(TRUE);
                ui->dianxin_btn->setChecked(FALSE);
                ui->online_btn->setChecked(FALSE);
            }//WCDMA    - LIANTONG
            else  if(line_check==12)
            {
                ui->wifi_btn->setChecked(FALSE);
                ui->liantong_btn->setChecked(TRUE);
                ui->yidong_btn->setChecked(FALSE);
                ui->dianxin_btn->setChecked(FALSE);
                ui->online_btn->setChecked(FALSE);
            }//TDSCDMA  - DIANXING
            else  if(line_check==11)
            {
                ui->wifi_btn->setChecked(FALSE);
                ui->liantong_btn->setChecked(FALSE);
                ui->yidong_btn->setChecked(FALSE);
                ui->dianxin_btn->setChecked(TRUE);
                ui->online_btn->setChecked(FALSE);
            }//ETHERNET - WANGXIAN
            else  if(line_check==2)
            {
                ui->wifi_btn->setChecked(FALSE);
                ui->liantong_btn->setChecked(FALSE);
                ui->yidong_btn->setChecked(FALSE);
                ui->dianxin_btn->setChecked(FALSE);
                ui->online_btn->setChecked(TRUE);
            }
            else
            {

            }
        }

    /*
        if(connect_net_way)
        {
            if(connect_net_way==10)
            {
                ui->wifi_btn->setChecked(TRUE);
                ui->liantong_btn->setChecked(FALSE);
                ui->yidong_btn->setChecked(FALSE);
                ui->dianxin_btn->setChecked(FALSE);
                ui->online_btn->setChecked(FALSE);
            }
            else  if(connect_net_way==11)
            {
                ui->wifi_btn->setChecked(FALSE);
                ui->liantong_btn->setChecked(FALSE);
                ui->yidong_btn->setChecked(TRUE);
                ui->dianxin_btn->setChecked(FALSE);
                ui->online_btn->setChecked(FALSE);
            }
            else  if(connect_net_way==14)
            {
                ui->wifi_btn->setChecked(FALSE);
                ui->liantong_btn->setChecked(TRUE);
                ui->yidong_btn->setChecked(FALSE);
                ui->dianxin_btn->setChecked(FALSE);
                ui->online_btn->setChecked(FALSE);
            }
            else  if(connect_net_way==17)
            {
                ui->wifi_btn->setChecked(FALSE);
                ui->liantong_btn->setChecked(FALSE);
                ui->yidong_btn->setChecked(FALSE);
                ui->dianxin_btn->setChecked(TRUE);
                ui->online_btn->setChecked(FALSE);
            }
            else  if(connect_net_way==2)
            {
                ui->wifi_btn->setChecked(FALSE);
                ui->liantong_btn->setChecked(FALSE);
                ui->yidong_btn->setChecked(FALSE);
                ui->dianxin_btn->setChecked(FALSE);
                ui->online_btn->setChecked(TRUE);
            }
            else
            {

            }
        }
        */
}

void p16_setpara_sub3_dialog::update_hmi_page_index()
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
    if(hmi_page_index != PAGEINDEX_SETPAGE_THR)
    {
        exit_page_dlg();
    }
    else
    {

    }
}

void p16_setpara_sub3_dialog::call_p15_dlg()
{

    timer->stop();
    emit signal_timer_p16dlg();
    delete p16_dlg;
    p16_dlg = NULL;
}

void p16_setpara_sub3_dialog::call_p17_dlg()
{
    timer->stop();
    if(p17_dlg){
            delete p17_dlg;
            p17_dlg = NULL;
            handle_dlg_p17--;
    }
    p17_dlg = new  p17_setpara_sub4_dialog;
    p17_dlg->setWindowFlags(Qt::FramelessWindowHint);
    handle_dlg_p17++;

    connect(this,SIGNAL(signal_enable_p17dlg_timer()),p17_dlg,SLOT(init_page_dlg()));
    connect(p17_dlg,SIGNAL(signal_exit_p17dlg()),this,SLOT(exit_page_dlg()));
    connect(p17_dlg,SIGNAL(signal_timer_p17dlg()),this,SLOT(start_timer()));
    emit signal_enable_p17dlg_timer();
    p17_dlg->exec();
}

void p16_setpara_sub3_dialog::exit_page_dlg()
{
    DebugMsg(hmilev,8,"exit_page_dlg\n");
    init_page_val();
    timer->stop();
    emit signal_exit_p16dlg();
}

void p16_setpara_sub3_dialog::on_pbtn_change_clicked()
{
  if(change_num)
  {
         change_num = 0;
  }
  else
  {
        change_num = 1;
  }
}

  void p16_setpara_sub3_dialog::on_open_palate_btn_clicked()
  {
      Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
      Inibuf_init(Key_name,BUFFERLEN_32,"palate_carnum");
      palate_check=1;
      write_profile_int(Section_name,Key_name,palate_check,config_path);
  }

  void p16_setpara_sub3_dialog::on_close_palate_btn_clicked()
  {
      Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
      Inibuf_init(Key_name,BUFFERLEN_32,"palate_carnum");
      palate_check=0;
      write_profile_int(Section_name,Key_name,palate_check,config_path);
  }


BOOL neednet_flg;
void p16_setpara_sub3_dialog::on_start_btn_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"networkservice");
    net_check=1;
    write_profile_int(Section_name,Key_name,net_check,config_path);
    neednet_flg=1;
    API_Write_DB_Nbyte(PL_NEEDNETWORK_FLAG ,(BOOL *)(&neednet_flg),sizeof(neednet_flg));
}

void p16_setpara_sub3_dialog::on_cancle_btn_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"networkservice");
    net_check=0;
    write_profile_int(Section_name,Key_name,net_check,config_path);
    neednet_flg=0;
    API_Write_DB_Nbyte(PL_NEEDNETWORK_FLAG ,(BOOL *)(&neednet_flg),sizeof(neednet_flg));
}


void p16_setpara_sub3_dialog::on_wifi_btn_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"DataPackTranformWay");
    line_check=10;
    //connect_net_way = 10;
    write_profile_int(Section_name,Key_name,line_check,config_path);
}

void p16_setpara_sub3_dialog::on_yidong_btn_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"DataPackTranformWay");
    line_check=13;
    //connect_net_way = 11;
    write_profile_int(Section_name,Key_name,line_check,config_path);
}
 void p16_setpara_sub3_dialog::on_liantong_btn_clicked()
 {
     Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
     Inibuf_init(Key_name,BUFFERLEN_32,"DataPackTranformWay");
     line_check=12;
     //connect_net_way = 14;
     write_profile_int(Section_name,Key_name,line_check,config_path);
 }
  void p16_setpara_sub3_dialog::on_dianxin_btn_clicked()
  {
      Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
      Inibuf_init(Key_name,BUFFERLEN_32,"DataPackTranformWay");
      line_check=15;
      connect_net_way = 17;
      write_profile_int(Section_name,Key_name,line_check,config_path);
  }

void p16_setpara_sub3_dialog::on_online_btn_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"DataPackTranformWay");
    line_check=2;
    //connect_net_way = 2;
    write_profile_int(Section_name,Key_name,line_check,config_path);
}

int num_16=0;

void p16_setpara_sub3_dialog::on_btn_1_clicked()
{
  //num_16=1;

}
void p16_setpara_sub3_dialog::on_btn_3_clicked()
{
  num_16=3;

}
void p16_setpara_sub3_dialog::on_btn_4_clicked()
{
  num_16=4;

}
void p16_setpara_sub3_dialog::on_btn_5_clicked()
{
  num_16=5;
}

void p16_setpara_sub3_dialog::on_pbtn_16_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestcurrent");
    fmaxi=16;
    write_profile_int(Section_name,Key_name,fmaxi,config_path);
}

void p16_setpara_sub3_dialog::on_pbtn_32_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestcurrent");
    fmaxi=32;
    write_profile_int(Section_name,Key_name,fmaxi,config_path);
}

void p16_setpara_sub3_dialog::on_pbtn_num0_clicked()
{
     switch(num_16)
    {
        case 1:
         if(soft_flg)
         {
             memset(soft,0,sizeof(soft));
             soft_flg=FALSE;
         }
            soft[soft_len++]='0';
             break;

        case 2:

            cost[cost_len++]='0';
               break;

        case 3:
         if(dev_flg)
         {
             memset(btn_devwd,0,sizeof(btn_devwd));
             dev_flg=FALSE;
         }
                  btn_devwd[btn_devwd_len++]='0';
                   break;

        case 4:
         if(source_flg)
         {
             memset(source,0,sizeof(source));
             source_flg=FALSE;
         }
                 source[source_len++]='0';
                   break;
     case 5:
      if(money_flg)
      {
          memset(money,0,sizeof(money));
          money_flg=FALSE;
      }
        money[money_len++]='0';
        break;
       // default:

                //

    }



}

void p16_setpara_sub3_dialog::on_pbtn_num1_clicked()
{
    if(change_num)
    {
        switch(num_16)
        {
            case 1:
             if(soft_flg)
             {
                 memset(soft,0,sizeof(soft));
                 soft_flg=FALSE;
             }
                soft[soft_len++]='A';
                 break;

            case 2:

                cost[cost_len++]='A';
                   break;

            case 3:
             if(dev_flg)
             {
                 memset(btn_devwd,0,sizeof(btn_devwd));
                 dev_flg=FALSE;
             }
                      btn_devwd[btn_devwd_len++]='A';
                       break;

            case 4:
             if(source_flg)
             {
                 memset(source,0,sizeof(source));
                 source_flg=FALSE;
             }
                     source[source_len++]='A';
                       break;
            case 5:
             if(money_flg)
             {
                 memset(money,0,sizeof(money));
                 money_flg=FALSE;
             }
               money[money_len++]='A';
               break;
                //default:

                        //
        }
    }
    else
    {
        switch(num_16)
        {
            case 1:
             if(soft_flg)
             {
                 memset(soft,0,sizeof(soft));
                 soft_flg=FALSE;
             }
                soft[soft_len++]='1';
                 break;

            case 2:

                cost[cost_len++]='1';
                   break;

            case 3:
             if(dev_flg)
             {
                 memset(btn_devwd,0,sizeof(btn_devwd));
                 dev_flg=FALSE;
             }
                      btn_devwd[btn_devwd_len++]='1';
                       break;

            case 4:
             if(source_flg)
             {
                 memset(source,0,sizeof(source));
                 source_flg=FALSE;
             }
                     source[source_len++]='1';
                       break;
            case 5:
             if(money_flg)
             {
                 memset(money,0,sizeof(money));
                 money_flg=FALSE;
             }
               money[money_len++]='1';
               break;
                //default:

                        //
        }
    }
}

void p16_setpara_sub3_dialog::on_pbtn_num2_clicked()
{
    if(change_num)
    {
        switch(num_16)
         {
        case 1:
         if(soft_flg)
         {
             memset(soft,0,sizeof(soft));
             soft_flg=FALSE;
         }
            soft[soft_len++]='B';
             break;

        case 2:

            cost[cost_len++]='B';
               break;

        case 3:
         if(dev_flg)
         {
             memset(btn_devwd,0,sizeof(btn_devwd));
             dev_flg=FALSE;
         }
                  btn_devwd[btn_devwd_len++]='B';
                   break;

        case 4:
         if(source_flg)
         {
             memset(source,0,sizeof(source));
             source_flg=FALSE;
         }
                 source[source_len++]='B';
                   break;

        case 5:
         if(money_flg)
         {
             memset(money,0,sizeof(money));
             money_flg=FALSE;
         }
           money[money_len++]='B';
           break;
             //default:

                     //

         }
    }
    else
    {
           switch(num_16)
            {
           case 1:
            if(soft_flg)
            {
                memset(soft,0,sizeof(soft));
                soft_flg=FALSE;
            }
               soft[soft_len++]='2';
                break;

           case 2:

               cost[cost_len++]='2';
                  break;

           case 3:
            if(dev_flg)
            {
                memset(btn_devwd,0,sizeof(btn_devwd));
                dev_flg=FALSE;
            }
                     btn_devwd[btn_devwd_len++]='2';
                      break;

           case 4:
            if(source_flg)
            {
                memset(source,0,sizeof(source));
                source_flg=FALSE;
            }
                    source[source_len++]='2';
                      break;

           case 5:
            if(money_flg)
            {
                memset(money,0,sizeof(money));
                money_flg=FALSE;
            }
              money[money_len++]='2';
              break;
                //default:

                        //

            }
    }
}

void p16_setpara_sub3_dialog::on_pbtn_num3_clicked()
{
    if(change_num)
    {
        switch(num_16)
       {
        case 1:
         if(soft_flg)
         {
             memset(soft,0,sizeof(soft));
             soft_flg=FALSE;
         }
            soft[soft_len++]='C';
             break;

        case 2:

            cost[cost_len++]='C';
               break;

        case 3:
         if(dev_flg)
         {
             memset(btn_devwd,0,sizeof(btn_devwd));
             dev_flg=FALSE;
         }
                  btn_devwd[btn_devwd_len++]='C';
                   break;

        case 4:
         if(source_flg)
         {
             memset(source,0,sizeof(source));
             source_flg=FALSE;
         }
                 source[source_len++]='C';
                   break;

        case 5:
         if(money_flg)
         {
             memset(money,0,sizeof(money));
             money_flg=FALSE;
         }
           money[money_len++]='C';
           break;
          // default:

                   //

       }
    }
    else
    {
        switch(num_16)
       {
        case 1:
         if(soft_flg)
         {
             memset(soft,0,sizeof(soft));
             soft_flg=FALSE;
         }
            soft[soft_len++]='3';
             break;

        case 2:

            cost[cost_len++]='3';
               break;

        case 3:
         if(dev_flg)
         {
             memset(btn_devwd,0,sizeof(btn_devwd));
             dev_flg=FALSE;
         }
                  btn_devwd[btn_devwd_len++]='3';
                   break;

        case 4:
         if(source_flg)
         {
             memset(source,0,sizeof(source));
             source_flg=FALSE;
         }
                 source[source_len++]='3';
                   break;

        case 5:
         if(money_flg)
         {
             memset(money,0,sizeof(money));
             money_flg=FALSE;
         }
           money[money_len++]='3';
           break;
          // default:

                   //

       }
    }

}

void p16_setpara_sub3_dialog::on_pbtn_num4_clicked()
{
    if(change_num)
    {
        switch(num_16)
        {
        case 1:
         if(soft_flg)
         {
             memset(soft,0,sizeof(soft));
             soft_flg=FALSE;
         }
            soft[soft_len++]='D';
             break;

        case 2:

            cost[cost_len++]='D';
               break;

        case 3:
         if(dev_flg)
         {
             memset(btn_devwd,0,sizeof(btn_devwd));
             dev_flg=FALSE;
         }
                  btn_devwd[btn_devwd_len++]='D';
                   break;

        case 4:
         if(source_flg)
         {
             memset(source,0,sizeof(source));
             source_flg=FALSE;
         }
                 source[source_len++]='D';
                   break;
        case 5:
         if(money_flg)
         {
             memset(money,0,sizeof(money));
             money_flg=FALSE;
         }
           money[money_len++]='D';
           break;
            //default:

                    //

        }
    }
    else
    {
        switch(num_16)
        {
        case 1:
         if(soft_flg)
         {
             memset(soft,0,sizeof(soft));
             soft_flg=FALSE;
         }
            soft[soft_len++]='4';
             break;

        case 2:

            cost[cost_len++]='4';
               break;

        case 3:
         if(dev_flg)
         {
             memset(btn_devwd,0,sizeof(btn_devwd));
             dev_flg=FALSE;
         }
                  btn_devwd[btn_devwd_len++]='4';
                   break;

        case 4:
         if(source_flg)
         {
             memset(source,0,sizeof(source));
             source_flg=FALSE;
         }
                 source[source_len++]='4';
                   break;
        case 5:
         if(money_flg)
         {
             memset(money,0,sizeof(money));
             money_flg=FALSE;
         }
           money[money_len++]='4';
           break;
            //default:

                    //

        }
    }

}

void p16_setpara_sub3_dialog::on_pbtn_num5_clicked()
{
    if(change_num)
    {
        switch(num_16)
        {
        case 1:
         if(soft_flg)
         {
             memset(soft,0,sizeof(soft));
             soft_flg=FALSE;
         }
            soft[soft_len++]='E';
             break;

        case 2:

            cost[cost_len++]='E';
               break;

        case 3:
         if(dev_flg)
         {
             memset(btn_devwd,0,sizeof(btn_devwd));
             dev_flg=FALSE;
         }
                  btn_devwd[btn_devwd_len++]='E';
                   break;

        case 4:
         if(source_flg)
         {
             memset(source,0,sizeof(source));
             source_flg=FALSE;
         }
                 source[source_len++]='E';
                   break;
        case 5:
         if(money_flg)
         {
             memset(money,0,sizeof(money));
             money_flg=FALSE;
         }
           money[money_len++]='E';
           break;
            //default:

                    //

        }
    }
    else
    {
        switch(num_16)
        {
        case 1:
         if(soft_flg)
         {
             memset(soft,0,sizeof(soft));
             soft_flg=FALSE;
         }
            soft[soft_len++]='5';
             break;

        case 2:

            cost[cost_len++]='5';
               break;

        case 3:
         if(dev_flg)
         {
             memset(btn_devwd,0,sizeof(btn_devwd));
             dev_flg=FALSE;
         }
                  btn_devwd[btn_devwd_len++]='5';
                   break;

        case 4:
         if(source_flg)
         {
             memset(source,0,sizeof(source));
             source_flg=FALSE;
         }
                 source[source_len++]='5';
                   break;
        case 5:
         if(money_flg)
         {
             memset(money,0,sizeof(money));
             money_flg=FALSE;
         }
           money[money_len++]='5';
           break;
            //default:

                    //

        }
    }
}

void p16_setpara_sub3_dialog::on_pbtn_num6_clicked()
{
    if(change_num)
    {
        switch(num_16)
        {
        case 1:
         if(soft_flg)
         {
             memset(soft,0,sizeof(soft));
             soft_flg=FALSE;
         }
            soft[soft_len++]='F';
             break;

        case 2:

            cost[cost_len++]='F';
               break;

        case 3:
         if(dev_flg)
         {
             memset(btn_devwd,0,sizeof(btn_devwd));
             dev_flg=FALSE;
         }
                  btn_devwd[btn_devwd_len++]='F';
                   break;

        case 4:
         if(source_flg)
         {
             memset(source,0,sizeof(source));
             source_flg=FALSE;
         }
                 source[source_len++]='F';
                   break;
        case 5:
         if(money_flg)
         {
             memset(money,0,sizeof(money));
             money_flg=FALSE;
         }
           money[money_len++]='F';
           break;
            //default:

                    //

        }
    }
    else
    {
        switch(num_16)
        {
        case 1:
         if(soft_flg)
         {
             memset(soft,0,sizeof(soft));
             soft_flg=FALSE;
         }
            soft[soft_len++]='6';
             break;

        case 2:

            cost[cost_len++]='6';
               break;

        case 3:
         if(dev_flg)
         {
             memset(btn_devwd,0,sizeof(btn_devwd));
             dev_flg=FALSE;
         }
                  btn_devwd[btn_devwd_len++]='6';
                   break;

        case 4:
         if(source_flg)
         {
             memset(source,0,sizeof(source));
             source_flg=FALSE;
         }
                 source[source_len++]='6';
                   break;
        case 5:
         if(money_flg)
         {
             memset(money,0,sizeof(money));
             money_flg=FALSE;
         }
           money[money_len++]='6';
           break;
            //default:

                    //

        }
    }

}

void p16_setpara_sub3_dialog::on_pbtn_num7_clicked()
{

    switch(num_16)
    {
    case 1:
     if(soft_flg)
     {
         memset(soft,0,sizeof(soft));
         soft_flg=FALSE;
     }
        soft[soft_len++]='7';
         break;

    case 2:

        cost[cost_len++]='7';
           break;

    case 3:
     if(dev_flg)
     {
         memset(btn_devwd,0,sizeof(btn_devwd));
         dev_flg=FALSE;
     }
              btn_devwd[btn_devwd_len++]='7';
               break;

    case 4:
     if(source_flg)
     {
         memset(source,0,sizeof(source));
         source_flg=FALSE;
     }
             source[source_len++]='7';
               break;
    case 5:
     if(money_flg)
     {
         memset(money,0,sizeof(money));
         money_flg=FALSE;
     }
       money[money_len++]='7';
       break;
       // default:

                //

    }
}

void p16_setpara_sub3_dialog::on_pbtn_num8_clicked()
{
     switch(num_16)
    {
     case 1:
      if(soft_flg)
      {
          memset(soft,0,sizeof(soft));
          soft_flg=FALSE;
      }
         soft[soft_len++]='8';
          break;

     case 2:

         cost[cost_len++]='8';
            break;

     case 3:
      if(dev_flg)
      {
          memset(btn_devwd,0,sizeof(btn_devwd));
          dev_flg=FALSE;
      }
               btn_devwd[btn_devwd_len++]='8';
                break;

     case 4:
      if(source_flg)
      {
          memset(source,0,sizeof(source));
          source_flg=FALSE;
      }
              source[source_len++]='8';
                break;
     case 5:
      if(money_flg)
      {
          memset(money,0,sizeof(money));
          money_flg=FALSE;
      }
        money[money_len++]='8';
        break;

       // default:

                //

    }
}

void p16_setpara_sub3_dialog::on_pbtn_num9_clicked()
{
   switch(num_16)
    {
   case 1:
    if(soft_flg)
    {
        memset(soft,0,sizeof(soft));
        soft_flg=FALSE;
    }
       soft[soft_len++]='9';
        break;

   case 2:

       cost[cost_len++]='9';
          break;

   case 3:
    if(dev_flg)
    {
        memset(btn_devwd,0,sizeof(btn_devwd));
        dev_flg=FALSE;
    }
             btn_devwd[btn_devwd_len++]='9';
              break;

   case 4:
    if(source_flg)
    {
        memset(source,0,sizeof(source));
        source_flg=FALSE;
    }
            source[source_len++]='9';
              break;
   case 5:
    if(money_flg)
    {
        memset(money,0,sizeof(money));
        money_flg=FALSE;
    }
      money[money_len++]='9';
      break;
       // default:

                //

    }
}

void p16_setpara_sub3_dialog::on_pbtn_dot_clicked()
{
   switch(num_16)
    {
   case 1:
    if(soft_flg)
    {
        memset(soft,0,sizeof(soft));
        soft_flg=FALSE;
    }
       soft[soft_len++]='.';
        break;

   case 2:

       cost[cost_len++]='.';
          break;

   case 3:
    if(dev_flg)
    {
        memset(btn_devwd,0,sizeof(btn_devwd));
        dev_flg=FALSE;
    }
             btn_devwd[btn_devwd_len++]='.';
              break;

   case 4:
    if(source_flg)
    {
        memset(source,0,sizeof(source));
        source_flg=FALSE;
    }
            source[source_len++]='.';
              break;
   case 5:
    if(money_flg)
    {
        memset(money,0,sizeof(money));
        money_flg=FALSE;
    }
      money[money_len++]='.';
      break;

       // default:

                //

    }
}



void p16_setpara_sub3_dialog::on_pbtn_back_clicked()
{
        switch(num_16)
        {
        case 1:
        if(soft_len>0)
        {
            soft_len--;
            soft[soft_len]=0;
        }
        else
        {
            soft_len=0;
        }
        break;

        case 2:
        if(cost_len>0)
        {
            cost_len--;
            cost[cost_len]=0;
        }
        else
        {
            cost_len=0;
        }
        break;

        case 3:
        if(btn_devwd_len>0)
        {
            btn_devwd_len--;
            btn_devwd[btn_devwd_len]=0;
        }
        else
        {
            btn_devwd_len=0;
        }

        break;

        case 4:
        if(source_len>0)
        {
            source_len--;
            source[source_len]=0;
        }
        else
        {
            source_len=0;
        }

        break;

        case 5:
        if(money_len>0)
        {
            money_len--;
            money[money_len]=0;
        }
        else
        {
            money_len=0;
        }

        break;

        default:
        break;
        //

        }

}

void p16_setpara_sub3_dialog::on_pbtn_up_clicked()
{

    DebugMsg(hmilev,5,"on_pbtn_up_clicked\n");

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"stubcode");
    if(btn_devwd_len>0)
    {
        write_profile_string(Section_name,Key_name,btn_devwd,config_path);
    }
    else
    {
       //  ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"softwareversion");
    if(soft_len>0)
    {
        write_profile_string(Section_name,Key_name,soft,config_path);
    }
    else
    {
        // ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"electricityprice");
    if(money_len>0)
    {
        write_profile_string(Section_name,Key_name,money,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"propertycode");
    if(source_len>0)
    {
        write_profile_string(Section_name,Key_name,source,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"meterfactor");
    if(cost_len>0)
    {
        write_profile_string(Section_name,Key_name,cost,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }
    hmi_button_dn_num=PAGEUP_BUTTON ;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

void p16_setpara_sub3_dialog::on_pbtn_down_clicked()
{
    DebugMsg(hmilev,5,"on_pbtn_down_clicked\n");

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"stubcode");
    if(btn_devwd_len>0)
    {
        write_profile_string(Section_name,Key_name,btn_devwd,config_path);
    }
    else
    {
       //  ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"softwareversion");
    if(soft_len>0)
    {
        write_profile_string(Section_name,Key_name,soft,config_path);
    }
    else
    {
        // ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"electricityprice");
    if(money_len>0)
    {
        write_profile_string(Section_name,Key_name,money,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"propertycode");
    if(source_len>0)
    {
        write_profile_string(Section_name,Key_name,source,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"meterfactor");
    if(cost_len>0)
    {
        write_profile_string(Section_name,Key_name,cost,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    hmi_button_dn_num=PAGEDOWN_BUTTON ;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

}

void p16_setpara_sub3_dialog::on_pbtn_go_clicked()
{

    DebugMsg(hmilev,5,"on_pbtn_cancel_clicked\n");

  //  btn_devwd_len=0;
   // memset(btn_devwd,0,sizeof(btn_devwd));

    hmi_button_dn_num=CANCEL_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

}


/*
void p16_setpara_sub3_dialog::on_pbtn_enter_clicked()
{
    DebugMsg(hmilev,5,"on_pbtn_enter_clicked\n");

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"stubcode");
    if(btn_devwd_len>=MAX_DEVWD_LEN)
    {
        write_profile_string(Section_name,Key_name,btn_devwd,config_path);
    }
    else
    {
         ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"softwareversion");
    if(soft_len>=MAX_SOFT_LEN)
    {
        write_profile_string(Section_name,Key_name,soft,config_path);
    }
    else
    {
         ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"propertycode");
    if(source_len>=MAX_SOURCE_LEN)
    {
        write_profile_string(Section_name,Key_name,source,config_path);
    }
    else
    {
         ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"meterfactor");
    if(cost_len>=MAX_COST_LEN)
    {
        write_profile_string(Section_name,Key_name,cost,config_path);
    }
    else
    {
         ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    hmi_button_dn_num=OK_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}
*/

void p16_setpara_sub3_dialog::on_pbtn_ok_clicked()
{
    DebugMsg(hmilev,5,"on_pbtn_enter_clicked\n");

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"stubcode");
    if(btn_devwd_len>0)
    {
        write_profile_string(Section_name,Key_name,btn_devwd,config_path);
    }
    else
    {
     //    ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"softwareversion");
    if(soft_len>0)
    {
        write_profile_string(Section_name,Key_name,soft,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"propertycode");
    if(source_len>0)
    {
        write_profile_string(Section_name,Key_name,source,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"electricityprice");
    if(money_len>0)
    {
        write_profile_string(Section_name,Key_name,money,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"meterfactor");
    if(cost_len>0)
    {
        write_profile_string(Section_name,Key_name,cost,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    hmi_button_dn_num=OK_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}
