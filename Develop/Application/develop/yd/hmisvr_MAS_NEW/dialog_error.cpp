#include "dialog_error.h"
#include "ui_dialog_error.h"
#include "globalhmi.h"

Dialog_error::Dialog_error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_error)
{
    ui->setupUi(this);
}

Dialog_error::~Dialog_error()
{
    delete ui;
}

int dialog_error_addnum = 0;
void Dialog_error::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    btn_press();
    init_page_val();
    ui->label_phone->setText(phonenum);
    ui->label_phone_2->setText(phonenum_2);
}

void Dialog_error::btn_press()
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
        array[12] = ui->pbtn_go;
        array[13] = ui->pbtn_ok;

        int num = 0;
        for(num = 0; num < 14;num++)
        {
            array[num]->setStyleSheet("QPushButton{border-image: url(:/icon/qrc/keyboard-b/T.png);}\
                                      QPushButton:pressed{border-image: url(:/icon/qrc/keyboard-b/T_press.png);}");
        }
}

char temp_buf[30][50]={0};
int temp_add = 0;
int num_sum = 0;
UINT8 jump_num_err;
BOOL enter_clc_err;
void Dialog_error::init_page_val()
{
    jump_num_err = 0;
    enter_clc_err = 0;
    temp_add = 0;
    num_sum = 0;
    memset(temp_buf,0,sizeof(temp_buf));
    btn_passwd_pos=0;
    memset(btn_passwd_disp,0,sizeof(btn_passwd_disp));
    memset(btn_passwd,0,sizeof(btn_passwd));

    memset(Set_paswd,0,sizeof(Set_paswd));
    memset(Tempor_name,0,sizeof(Tempor_name));
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"settingpwd");
    if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
    {
        memcpy(Set_paswd,Tempor_name,sizeof(Set_paswd));
    }
    else
    {
        memset(Set_paswd,0,sizeof(Set_paswd));
    }

    lbl_num=1;
    lbl_num_2=2;
    lbl_num_3=3;
    lbl_num_4=4;
    lbl_num_5=5;

    memset(lbl_txt, 0,sizeof(lbl_txt));
    memset(lbl_txt_2, 0,sizeof(lbl_txt_2));
    memset(lbl_txt_3, 0,sizeof(lbl_txt_3));
    memset(lbl_txt_4, 0,sizeof(lbl_txt_4));
    memset(lbl_txt_5, 0,sizeof(lbl_txt_5));


    ui->label_num->setText(NULL);
    ui->label_num_2->setText(NULL);
    ui->label_num_3->setText(NULL);
    ui->label_num_4->setText(NULL);
    ui->label_num_5->setText(NULL);
    ui->label_txt->setText(NULL);
    ui->label_txt_2->setText(NULL);
    ui->label_txt_3->setText(NULL);
    ui->label_txt_4->setText(NULL);
    ui->label_txt_5->setText(NULL);


    ui->label_code->setText(code);
    ui->label_piccode->setPixmap(QPixmap("/usr/APP/1.png"));

    if(language_num == 1)
    {
      //   ui->label_logo->setText(QString::fromUtf8("直 流 充 电 桩"));
    //    ui->label_state->setText(QString::fromUtf8("设备故障，暂停使用"));
       // ui->pbtn_err->setText(QString::fromUtf8("故障详情"));
        ui->pbtn_up->setText(QString::fromUtf8("上一页"));
        ui->pbtn_down->setText(QString::fromUtf8("下一页"));
        ui->pbtn_back_2->setText(QString::fromUtf8("返 回"));
        ui->label_stubnum->setText(QString::fromUtf8("桩编号："));

        ui->lbl_num->setText(QString::fromUtf8("故障序号"));
        ui->lbl_infor->setText(QString::fromUtf8(" 故障信息"));
    }
    else  if(language_num == 2)
    {
      //  ui->label_logo->setText("DC charging pile");
    //    ui->label_state->setText("Equipment Error");
        //ui->pbtn_err->setText("Error Detail");
        ui->pbtn_up->setText("Page Up");
        ui->pbtn_down->setText("Page Down");
        ui->pbtn_back_2->setText("back");
        ui->label_stubnum->setText("Telephone :");
        ui->lbl_num->setText("Num");
        ui->lbl_infor->setText("ErrInfor");

    }
    else
    {

    }

    ui->frame_5->move(20,100);
    ui->frame->move(34,610);
    ui->frame_2->move(190,500);
    ui->frame_3->move(35,500);

    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));

    int state_flag = 0;
     API_Write_DB_Nbyte(PL_STUBERRSTATE_FLAG,(int *)(&state_flag),sizeof(state_flag));
}

void Dialog_error::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_error::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void Dialog_error::on_pbtn_set_clicked()
{
    UINT8 data = SET_PARA_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

 void Dialog_error::on_pbtn_err_clicked()
 {
     ui->frame->move(34,610);
     ui->frame_2->move(34,100);
     ui->frame_3->move(464,100);
     ui->frame_5->move(20,700);
 }

 void Dialog_error::on_pbtn_back_2_clicked()
 {
     ui->frame_5->move(20,100);
     ui->frame->move(34,610);
     ui->frame_2->move(190,500);
     ui->frame_3->move(35,500);
 }

 void Dialog_error::on_pbtn_up_clicked()
 {
      if(lbl_num-5>0)
      {
              lbl_num=lbl_num-5;
              lbl_num_2=lbl_num_2-5;
              lbl_num_3=lbl_num_3-5;
              lbl_num_4=lbl_num_4-5;
              lbl_num_5=lbl_num_5-5;
     }
     else
     {

     }
 }

 void Dialog_error::on_pbtn_down_clicked()
 {
     if(lbl_num_5+5<num_sum)
     {
             lbl_num=lbl_num+5;
             lbl_num_2=lbl_num_2+5;
             lbl_num_3=lbl_num_3+5;
             lbl_num_4=lbl_num_4+5;
             lbl_num_5=lbl_num_5+5;
    }
    else
    {

    }
 }


 int   Err_anasys()
 {
     if(language_num == 1)
     {

         temp_add = 0;
         if( (error_state_flag & (1<<0)) || (error_state_flag &(1<<24)) || (error_state_flag & (1<<1))  || (error_state_flag & (1<<25)) )
         {

             memcpy(&temp_buf[temp_add++],"读 卡 器 故 障",sizeof("读 卡 器 故 障"));
         }
         if( (error_state_flag & (1<<20)) )
         {
             memcpy(&temp_buf[temp_add++],"电 表 通 讯 故 障",sizeof("电 表 通 讯 故 障"));
         }
         if( (error_state_flag & (1<<3)) )
         {
             memcpy(&temp_buf[temp_add++],"显 示 屏 通 讯 故 障",sizeof("显 示 屏 通 讯 故 障"));
         }
         if( (error_state_flag & (1<<8)) )
         {
             memcpy(&temp_buf[temp_add++],"主 板 软 件 故 障",sizeof("主 板 软 件 故 障"));
         }
         if( (error_state_flag & (1<<21)) )
         {
             memcpy(&temp_buf[temp_add++],"急停按钮被按下,请恢复",sizeof("急停按钮被按下,请恢复"));
         }
         if( (error_state_flag & (1<<7)) )
         {
             memcpy(&temp_buf[temp_add++],"主 板 硬 件 故 障",sizeof("主 板 硬 件 故 障"));
         }
         if( (error_state_flag & (1<<4)) ||(error_state_flag & (1<<5)))
         {
             memcpy(&temp_buf[temp_add++],"交流接触器故障",sizeof("交流接触器故障"));
         }
         if( (error_state_flag & (1<<10)) )
         {
             memcpy(&temp_buf[temp_add++],"模块通讯故障",sizeof("模块通讯故障"));
         }
         if( (error_state_flag & (1<<30)) )
         {
             memcpy(&temp_buf[temp_add++],"输入过压",sizeof("输入过压"));
         }
         if( (error_state_flag & (1<<31)) )
         {
             memcpy(&temp_buf[temp_add++],"输入欠压",sizeof("输入欠压"));
         }
         if( (error_state_flag & (1<<18)) )
         {
             memcpy(&temp_buf[temp_add++],"电磁锁故障",sizeof("电磁锁故障"));
         }
         if( (error_state_flag & (1<<11)) )
         {
             memcpy(&temp_buf[temp_add++],"数据传输错误",sizeof("数据传输错误"));
         }
         if( (error_state_flag & (1<<12)) )
         {
             memcpy(&temp_buf[temp_add++],"输出过流",sizeof("输出过流"));
         }
         if( (error_state_flag & (1<<13)) )
         {
             memcpy(&temp_buf[temp_add++],"输出短路",sizeof("输出短路"));
         }
         if( (error_state_flag & (1<<14)) )
         {
             memcpy(&temp_buf[temp_add++],"出风口温度过高",sizeof("出风口温度过高"));
         }
         if( (error_state_flag & (1<<15)) )
         {
             memcpy(&temp_buf[temp_add++],"存储器已满",sizeof("存储器已满"));
         }
         if( (error_state_flag & (1<<23)) )
         {
             memcpy(&temp_buf[temp_add++],"网 络 连 接 故 障",sizeof("网 络 连 接 故 障"));
         }
     }
     else  if(language_num == 2)
     {

         temp_add = 0;
         if( (error_state_flag & (1<<0)) || (error_state_flag &(1<<24)) || (error_state_flag & (1<<1))  || (error_state_flag & (1<<25)) )
         {
             memcpy(&temp_buf[temp_add++],"card reader error",sizeof("card reader error"));
         }
         if( (error_state_flag & (1<<20)) )
         {
             memcpy(&temp_buf[temp_add++],"meter error",sizeof("meter error"));
         }
         if( (error_state_flag & (1<<8)) )
         {
             memcpy(&temp_buf[temp_add++],"software in board error",sizeof("software in board error"));
         }
         if( (error_state_flag & (1<<21)) )
         {
             memcpy(&temp_buf[temp_add++],"emergency is pressed,please recover it",sizeof("emergency is pressed,please recover it"));
         }
         if( (error_state_flag & (1<<7)) )
         {
             memcpy(&temp_buf[temp_add++],"hardware in board error",sizeof("hardware in board error"));
         }
         if( (error_state_flag & (1<<4)) ||(error_state_flag & (1<<5)))
         {
             memcpy(&temp_buf[temp_add++],"ac contactor error",sizeof("ac contactor error"));
         }
         if( (error_state_flag & (1<<23)) )
         {
             memcpy(&temp_buf[temp_add++],"net link error",sizeof("net link error"));
         }
     }
     else
     {

     }
     return temp_add;
 }

UINT8 tempvalue=0;
 int temp_error_state = 0;
void Dialog_error::update_page_info()
{
    ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));

    DebugMsg(hmilev,8,"btn_passwd[%s][%d]\n",btn_passwd,btn_passwd_pos);
    memset(btn_passwd_disp,0,sizeof(btn_passwd_disp));
    #ifdef DEF_DEBUG_PASSWD_BY_NUM
    strcpy(btn_passwd_disp,btn_passwd);
    #else
    memset(btn_passwd_disp,'*',btn_passwd_pos);
    #endif

    ui->label_passwd->setText(btn_passwd_disp);



    if(jump_num_err==0)
    {
         ui->label_speaker->setText(QString::fromUtf8("安全提示:请注意遮挡键盘!"));
    }
    else if(jump_num_err==1&&enter_clc_err)
    {

        ui->label_speaker->setText(QString::fromUtf8("密码验证失败,请重新输入!"));
        btn_passwd_pos=0;
        memset(btn_passwd,0,sizeof(btn_passwd));
        enter_clc_err=FALSE;
    }
    else if(jump_num_err==2)
    {
        ui->label_speaker->setText(QString::fromUtf8("密码不能为空,请重新输入!"));
    }


    API_Read_DB_Nbyte(PL_STUBERRSTATE_FLAG,(int *)(&error_state_flag),sizeof(error_state_flag));
    //printf("*************************** 8388608 ***\n");
    //printf("********* error_state_flag = %x ********\n",error_state_flag);

    //if(temp_error_state != error_state_flag)
    {
        temp_error_state = error_state_flag;
        memset(temp_buf,0,sizeof(temp_buf));
        num_sum = Err_anasys();
    }

    API_Read_DB_Nbyte(PL_ERROR_TXT_FLAG,(char*)&tempvalue,sizeof(tempvalue));
    //printf("!!!!!!!!!!!Chr_Process_ERROR_TXT=%d\r\n",tempvalue);
   if(tempvalue==1)
   {
        //ui->label_state_2->setText(QString::fromUtf8("请移除车辆端充电枪"));

   }
   else if(tempvalue==2)
   {
       //ui->label_state_2->setText(QString::fromUtf8("请先移除车辆端充电枪,再移除充电桩端充电枪"));

   }
   else
   {
      //ui->label_state_2->setText(QString::fromUtf8(" "));

   }


#if 1
    memcpy(lbl_txt, &temp_buf[lbl_num-1],sizeof(temp_buf[lbl_num-1]));
    memcpy(lbl_txt_2,& temp_buf[lbl_num_2-1],sizeof(temp_buf[lbl_num_2-1]));
    memcpy(lbl_txt_3, &temp_buf[lbl_num_3-1],sizeof(temp_buf[lbl_num_3-1]));
    memcpy(lbl_txt_4, &temp_buf[lbl_num_4-1],sizeof(temp_buf[lbl_num_4-1]));
    memcpy(lbl_txt_5, &temp_buf[lbl_num_5-1],sizeof(temp_buf[lbl_num_5-1]));


    ui->label_txt->setText(QString::fromUtf8(lbl_txt));
    ui->label_txt_2->setText(QString::fromUtf8(lbl_txt_2));
    ui->label_txt_3->setText(QString::fromUtf8(lbl_txt_3));
    ui->label_txt_4->setText(QString::fromUtf8(lbl_txt_4));
    ui->label_txt_5->setText(QString::fromUtf8(lbl_txt_5));

    if(lbl_txt[0])
    {
         ui->label_num->setNum(lbl_num);
    }
    else
    {
         ui->label_num->setText(NULL);
    }

    if(lbl_txt_2[0])
    {
       ui->label_num_2->setNum(lbl_num_2);
    }
    else
    {
        ui->label_num_2->setText(NULL);
    }

    if(lbl_txt_3[0])
    {
         ui->label_num_3->setNum(lbl_num_3);
    }
    else
    {
         ui->label_num_3->setText(NULL);
    }

    if(lbl_txt_4[0])
    {
        ui->label_num_4->setNum(lbl_num_4);
    }
    else
    {
         ui->label_num_4->setText(NULL);
    }

    if(lbl_txt_5[0])
    {
       ui->label_num_5->setNum(lbl_num_5);
    }
    else
    {
         ui->label_num_5->setText(NULL);
    }
#endif
    
    int net_flg2 = 0;
    ui->pbtn_setnet->setStyleSheet("border-image: url(:/icon/qrc/icon/0.png);");
    
    API_Read_DB_Nbyte(PL_NETWORKLINKSTATE_FLAG,(BOOL *)(&net_flg2),sizeof(net_flg2));
    if(net_flg2)
    {
        dialog_error_addnum=0;
        ui->pbtn_setnet->setStyleSheet("border-image: url(:/icon/qrc/icon/1.png);");
    }
    else
    {
        dialog_error_addnum++;
        if(dialog_error_addnum>=750)
        {
            ui->pbtn_setnet->setStyleSheet("border-image: url(:/icon/qrc/icon/0.png);");
            dialog_error_addnum=0;
        }
    }    
}

void Dialog_error::update_hmi_page_index()
{
     API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
    if(hmi_page_index != PAGEINDEX_ERRORCHECK)
    {
        exit_page_dlg();
    }
    else
    {

    }
}

void Dialog_error::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_errdlg();
    //delete err_dlg;
    //err_dlg = NULL;
}

void Dialog_error::on_pbtn_num0_clicked()
{
    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='0';
    }
}

void Dialog_error::on_pbtn_num1_clicked()
{
    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='1';
    }
}

void Dialog_error::on_pbtn_num2_clicked()
{
    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='2';
    }
}

void Dialog_error::on_pbtn_num3_clicked()
{
    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='3';
    }
}

void Dialog_error::on_pbtn_num4_clicked()
{
    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='4';
    }
}

void Dialog_error::on_pbtn_num5_clicked()
{
    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='5';
    }
}

void Dialog_error::on_pbtn_num6_clicked()
{
    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='6';
    }
}

void Dialog_error::on_pbtn_num7_clicked()
{

    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='7';
    }
}

void Dialog_error::on_pbtn_num8_clicked()
{
    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='8';
    }
}

void Dialog_error::on_pbtn_num9_clicked()
{
    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='9';
    }
}

void Dialog_error::on_pbtn_dot_clicked()
{
    if(btn_passwd_pos>=MAX_PASSWD_LEN)
    {
        btn_passwd_pos=MAX_PASSWD_LEN;
    }else{
        btn_passwd[btn_passwd_pos++]='.';
    }
}

void Dialog_error::on_pbtn_back_clicked()
{
    if(btn_passwd_pos>0)
    {
        btn_passwd_pos--;
        btn_passwd[btn_passwd_pos]=0;
    }
    else
    {
        btn_passwd_pos=0;
    }
}

void Dialog_error::on_pbtn_go_clicked()
{
    DebugMsg(hmilev,5,"on_pbtn_cancel_clicked\n");
    btn_passwd_pos=0;
    memset(btn_passwd_disp,0,sizeof(btn_passwd_disp));
    memset(btn_passwd,0,sizeof(btn_passwd));

    ui->frame->move(34,610);
    ui->frame_2->move(190,500);
    ui->frame_3->move(35,500);
    ui->frame_5->move(20,100);
}

void Dialog_error::on_pbtn_ok_clicked()
{
    DebugMsg(hmilev,5,"on_pbtn_enter_clicked\n");
     enter_clc_err=TRUE;
     if(btn_passwd_pos==0)
     {
         jump_num_err=2;
         return;
     }
    if(memcmp(Set_paswd,btn_passwd,sizeof(btn_passwd))!=0)
    {
        jump_num_err=1;
        return;
    }
    btn_passwd_pos=0;
    memset(btn_passwd_disp,0,sizeof(btn_passwd_disp));
    memset(btn_passwd,0,sizeof(btn_passwd));


    ui->frame->move(34,87);
    ui->frame_2->move(190,500);
    ui->frame_3->move(35,500);
    ui->frame_5->move(20,700);
}
