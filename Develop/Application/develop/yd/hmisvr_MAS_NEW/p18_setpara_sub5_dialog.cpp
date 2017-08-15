#include "p18_setpara_sub5_dialog.h"
#include "ui_p18_setpara_sub5_dialog.h"
#include "globalhmi.h"

p18_setpara_sub5_dialog::p18_setpara_sub5_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::p18_setpara_sub5_dialog)
{
    ui->setupUi(this);
}

p18_setpara_sub5_dialog::~p18_setpara_sub5_dialog()
{
    delete ui;
}

/*
    厂家软件版本号：manufactor_time_flg
    上传软件版本号：upload_flg
*/
BOOL manufactor_time_flg = FALSE;
BOOL upload_flg = FALSE;

static int add_num = 0;
static int Timer = 0;

int num_18=0;
int change_num_18 = 0;//0 for num; 1 for letter;
void char_cutpoint(char *upload_soft_temp);
void p18_setpara_sub5_dialog::changeEvent(QEvent *e)
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

void p18_setpara_sub5_dialog::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
    btn_press();
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
}

void p18_setpara_sub5_dialog::btn_press()
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
    array[12] = ui->pbtn_cancel;
    array[13] = ui->pbtn_ok;
    array[14] = ui->pbtn_up;
    array[15] = ui->pbtn_down;
    int num = 0;
    for(num = 0; num < 16;num++)
    {
        array[num]->setStyleSheet("QPushButton{border-image: url(:/icon/qrc/keyboard-b/T.png);}\
                                  QPushButton:pressed{border-image: url(:/icon/qrc/keyboard-b/T_press.png);}");
    }

}

void p18_setpara_sub5_dialog::init_page_val()
{
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));

    /*
        厂家软件版本号
    */
    API_Read_DB_Nbyte(PL_SOFT_TIME,(INT8 *)(&manufactor_time),sizeof(manufactor_time));
    ui->lbl_manufactor_ver->setText(QString::fromLocal8Bit(manufactor_time));
    
    /*
        上传后台软件版本
    */
    upload_length = 0;
    
    
    memset(Tempor_name,0,sizeof(Tempor_name));
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"softwareversion");

    if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
    {
        char temp_soft[5]={0};
        memcpy(temp_soft,Tempor_name,sizeof(temp_soft));
        
        //1602464
       // printf("%x   %x   %x  %x \r\n",temp_upload_soft[0],temp_upload_soft[1],temp_upload_soft[2],temp_upload_soft[3]);

        sprintf(upload_soft,"%d.%d.%d.%d",(temp_soft[0]-48),(temp_soft[1]-48),(temp_soft[2]-48),(temp_soft[3]-48));
        //printf("*********** 1-upload_soft = %s *********\n",upload_soft);
        /*
        int temp_a,temp_b,temp_c,temp_d;
        temp_a = toInt(0,16);
        sprintf(upload_soft,"%d.%d.%d.%d",temp_a,temp_b,temp_c,temp_d);
        */
        upload_flg=TRUE;
    }
    else
    {
        memset(upload_soft,0,sizeof(upload_soft));
    }
    ui->lbl_upload_ver->setText(QString::fromLocal8Bit(upload_soft));
    //4.13.12.2
    
    //认证优先和充电优先
    int first_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"firsttype");
    first_val= read_profile_int(Section_name, Key_name,first_temp,config_path);

    //充电插座和充电枪
    int shape_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"gunshape");
    shape_val= read_profile_int(Section_name, Key_name,shape_temp,config_path);
  
}

void p18_setpara_sub5_dialog::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
}

void p18_setpara_sub5_dialog::timer_handle()
{
     update_page_info();
     update_hmi_page_index();
}

void p18_setpara_sub5_dialog::update_page_info()
{
    ui->lbl_manufactor_ver->setText(QString::fromLocal8Bit(manufactor_time));
    //ui->lbl_upload_ver->setText(upload_soft);
    ui->lbl_upload_ver->setText(QString::fromLocal8Bit(upload_soft));

    if(first_val == 1)
    {
        ui->char_first->setChecked(TRUE);
        ui->net_first->setChecked(FALSE);
    }
    else if(first_val == 2)
    {
        ui->char_first->setChecked(FALSE);
        ui->net_first->setChecked(TRUE);
    }
    else
    {

    }

    if(shape_val == 1)
    {
        ui->gun_line->setChecked(TRUE);
        ui->gun_socket->setChecked(FALSE);
    }
    else if(shape_val == 2)
    {
        ui->gun_line->setChecked(FALSE);
        ui->gun_socket->setChecked(TRUE);
    }
    else
    {

    }
    if(5 == num_18)
    {
        add_num++;
        if(add_num==20)
        {
            add_num=0;
            Timer--;
            if(Timer<=0)
            {
                Timer = 0;
                num_18 = 0;
                ui->label_tip->setText(QString::fromLocal8Bit(" "));
            }
        }
    }
}

void p18_setpara_sub5_dialog::update_hmi_page_index()
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
    if(hmi_page_index != PAGEINDEX_SETPAGE_FIVE)
    {
        exit_page_dlg();
    }
    else
    {

    }
}

void p18_setpara_sub5_dialog::exit_page_dlg()
{
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
    timer->stop();
    emit signal_exit_p18dlg();
    //delete p18_dlg;
    //p18_dlg = NULL;
    num_18 = 0;
}

void p18_setpara_sub5_dialog::on_char_first_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"firsttype");
    first_val=1;
    write_profile_int(Section_name,Key_name,first_val,config_path);
}

void p18_setpara_sub5_dialog::on_net_first_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"firsttype");
    first_val=2;
    write_profile_int(Section_name,Key_name,first_val,config_path);
}

void p18_setpara_sub5_dialog::on_gun_line_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"gunshape");
    shape_val=1;
    write_profile_int(Section_name,Key_name,shape_val,config_path);
}

void p18_setpara_sub5_dialog::on_gun_socket_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"gunshape");
    shape_val=2;
    write_profile_int(Section_name,Key_name,shape_val,config_path);
}

void p18_setpara_sub5_dialog::on_btn_3_clicked()
{
  num_18=5;
  //num_18=3;
  ui->label_tip->setText(QString::fromUtf8("该项不可更改！"));  
  Timer = 3;
}

void p18_setpara_sub5_dialog::on_btn_4_clicked()
{
  num_18=4;
}

void p18_setpara_sub5_dialog::on_pbtn_num0_clicked()
{
     switch(num_18)
    {
        case 3:
         if(manufactor_time_flg)
         {
             memset(manufactor_time,0,sizeof(manufactor_time));
             manufactor_time_flg=FALSE;
         }
         manufactor_time[manufactor_time_len++]='0';
         break;

        case 4:
         if(upload_flg)
         {
             memset(upload_soft,0,sizeof(upload_soft));
             upload_flg=FALSE;
         }
         upload_soft[upload_length++]='0';
         break;
    }

}

void p18_setpara_sub5_dialog::on_pbtn_num1_clicked()
{
if(change_num_18)
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='A';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='A';
             break;
        }
    }
    else
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='1';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='1';
             break;
        }
    }
}

void p18_setpara_sub5_dialog::on_pbtn_num2_clicked()
{
    if(change_num_18)
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='B';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='B';
             break;
        }
    }
    else
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='2';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='2';
             break;
        }
    }
}

void p18_setpara_sub5_dialog::on_pbtn_num3_clicked()
{
 if(change_num_18)
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='C';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='C';
             break;
        }
    }
    else
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='3';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='3';
             break;
        }
    }

}

void p18_setpara_sub5_dialog::on_pbtn_num4_clicked()
{
    if(change_num_18)
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='D';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='D';
             break;
        }
    }
    else
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='4';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='4';
             break;
        }
    }

}

void p18_setpara_sub5_dialog::on_pbtn_num5_clicked()
{
    if(change_num_18)
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='E';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='E';
             break;
        }
    }
    else
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='5';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='5';
             break;
        }
    }
}

void p18_setpara_sub5_dialog::on_pbtn_num6_clicked()
{
    if(change_num_18)
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='F';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='F';
             break;
        }
    }
    else
    {
        switch(num_18)
        {
            case 3:
             if(manufactor_time_flg)
             {
                 memset(manufactor_time,0,sizeof(manufactor_time));
                 manufactor_time_flg=FALSE;
             }
             manufactor_time[manufactor_time_len++]='6';
             break;

            case 4:
             if(upload_flg)
             {
                 memset(upload_soft,0,sizeof(upload_soft));
                 upload_flg=FALSE;
             }
             upload_soft[upload_length++]='6';
             break;
        }
    }

}

void p18_setpara_sub5_dialog::on_pbtn_num7_clicked()
{
    switch(num_18)
    {
        case 3:
         if(manufactor_time_flg)
         {
             memset(manufactor_time,0,sizeof(manufactor_time));
             manufactor_time_flg=FALSE;
         }
         manufactor_time[manufactor_time_len++]='7';
         break;

        case 4:
         if(upload_flg)
         {
             memset(upload_soft,0,sizeof(upload_soft));
             upload_flg=FALSE;
         }
         upload_soft[upload_length++]='7';
         break;
    }
}

void p18_setpara_sub5_dialog::on_pbtn_num8_clicked()
{
    switch(num_18)
    {
        case 3:
         if(manufactor_time_flg)
         {
             memset(manufactor_time,0,sizeof(manufactor_time));
             manufactor_time_flg=FALSE;
         }
         manufactor_time[manufactor_time_len++]='8';
         break;

        case 4:
         if(upload_flg)
         {
             memset(upload_soft,0,sizeof(upload_soft));
             upload_flg=FALSE;
         }
         upload_soft[upload_length++]='8';
         break;
    }
}

void p18_setpara_sub5_dialog::on_pbtn_num9_clicked()
{
    switch(num_18)
    {
        case 3:
         if(manufactor_time_flg)
         {
             memset(manufactor_time,0,sizeof(manufactor_time));
             manufactor_time_flg=FALSE;
         }
         manufactor_time[manufactor_time_len++]='9';
         break;

        case 4:
         if(upload_flg)
         {
             memset(upload_soft,0,sizeof(upload_soft));
             upload_flg=FALSE;
         }
         upload_soft[upload_length++]='9';
         break;
    }
}

void p18_setpara_sub5_dialog::on_pbtn_dot_clicked()
{
    switch(num_18)
    {
        case 3:
         if(manufactor_time_flg)
         {
             memset(manufactor_time,0,sizeof(manufactor_time));
             manufactor_time_flg=FALSE;
         }
         manufactor_time[manufactor_time_len++]='.';
         break;

        case 4:
         if(upload_flg)
         {
             memset(upload_soft,0,sizeof(upload_soft));
             upload_flg=FALSE;
         }
         upload_soft[upload_length++]='.';
         break;
    }
}

void p18_setpara_sub5_dialog::on_pbtn_back_clicked()
{
    switch(num_18)
    {
        case 3:
        if(manufactor_time_len>0)
        {
            manufactor_time_len--;
            manufactor_time[manufactor_time_len]=0;
        }
        else
        {
            manufactor_time_len=0;
        }
        break;

        case 4:
        if(upload_length>0)
        {
            upload_length--;
            upload_soft[upload_length]=0;
        }
        else
        {
            upload_length=0;
        }
        break;

    }

}

void p18_setpara_sub5_dialog::on_pbtn_cancel_clicked()
{
    ErrMsg("*****************\n");
    hmi_button_dn_num=CANCEL_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

void p18_setpara_sub5_dialog::on_pbtn_ok_clicked()
{
    //厂家软件版本号:
    API_Write_DB_Nbyte(PL_SOFT_TIME,(INT8 *)(&manufactor_time),sizeof(manufactor_time));
   
    //上传后台软件版本号
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"softwareversion");
    
    if(upload_length>0)
    {   
        //upsoft "4.34.13.2"  -> 4R=2
        char_cutpoint(upload_soft);
        write_profile_string(Section_name,Key_name,upload_soft,config_path);
    }
    else
    {
        // ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }
    
    hmi_button_dn_num=OK_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

void p18_setpara_sub5_dialog::on_pbtn_up_clicked()
{
    API_Write_DB_Nbyte(PL_SOFT_TIME,(INT8 *)(&manufactor_time),sizeof(manufactor_time));
   
    //上传后台软件版本号
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"softwareversion");
    
    if(upload_length>0)
    {   
        //upsoft "4.34.13.2"  -> 4R=2
        char_cutpoint(upload_soft);
        write_profile_string(Section_name,Key_name,upload_soft,config_path);
    }
    else
    {
        // ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }
    hmi_button_dn_num=PAGEUP_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
    
    //hmi_page_index = PAGEINDEX_SETPAGE_FOUR;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
}

void p18_setpara_sub5_dialog::on_pbtn_down_clicked()
{
    API_Write_DB_Nbyte(PL_SOFT_TIME,(INT8 *)(&manufactor_time),sizeof(manufactor_time));
   
    //上传后台软件版本号
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"softwareversion");
    
    if(upload_length>0)
    {   
        //upsoft "4.34.13.2"  -> 4R=2
        char_cutpoint(upload_soft);
        write_profile_string(Section_name,Key_name,upload_soft,config_path);
    }
    else
    {
        // ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }
    hmi_button_dn_num=PAGEDOWN_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

    //hmi_page_index = PAGEINDEX_SETPAGE_SIX;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
}

void char_cutpoint(char *upload_soft)
{
    int upsoft_index=0;
    int recode_upsoft_index=0;
    int upsoft_section_number[15];
    int upsoft_section_numberall[4];
    int upsoft_section_numindex=0;
    int upsoft_section_numberall_index=0;
    char recode_upsoft_char[5];
    int upsoft_section_len=0;
    int index_point=0;
    int last_char_num=0;

    for(upsoft_index=0;upload_soft[upsoft_index] != '\0';upsoft_index ++)
    {
            if(3 != index_point)
            {
                if('.' == upload_soft[upsoft_index])
                {   
                    index_point++;
                    upsoft_section_len = upsoft_index - recode_upsoft_index;
                    if(1 == upsoft_section_len)
                    {   
                        recode_upsoft_index=recode_upsoft_index+2;
                        upsoft_section_number[upsoft_section_numindex] = upload_soft[upsoft_index-1] - 48;
                        upsoft_section_numindex++;
                        upsoft_section_numberall[upsoft_section_numberall_index] = upsoft_section_number[upsoft_section_numindex-1];
                        upsoft_section_numberall_index++;
                    }
                    else if(2 == upsoft_section_len)
                    {
                        recode_upsoft_index =recode_upsoft_index+3;
                        upsoft_section_number[upsoft_section_numindex] = upload_soft[upsoft_index-2] - 48;
                        upsoft_section_numindex++;
                        upsoft_section_number[upsoft_section_numindex] = upload_soft[upsoft_index-1] - 48;
                        upsoft_section_numberall[upsoft_section_numberall_index] = upsoft_section_number[upsoft_section_numindex-1]*10 + \
                        upsoft_section_number[upsoft_section_numindex]; 

                        upsoft_section_numberall_index++;
                    }
                    else
                    {

                    }

                }
                else
                {

                }//end of if('.' == )
            }
            else
            {
                last_char_num++;
            }

    }//end of for()

    if(1 == last_char_num)
    {
        upsoft_section_number[upsoft_section_numindex] = upload_soft[upsoft_index-1] - 48;

        upsoft_section_numberall[upsoft_section_numberall_index] = upsoft_section_number[upsoft_section_numindex];
    }
    else if(2 == last_char_num)
    {
        upsoft_section_number[upsoft_section_numindex] = upload_soft[upsoft_index-2] - 48;
        upsoft_section_numindex++;
        upsoft_section_number[upsoft_section_numindex] = upload_soft[upsoft_index-1] - 48;
        upsoft_section_numberall[upsoft_section_numberall_index] = upsoft_section_number[upsoft_section_numindex-1]*10 + \
        upsoft_section_number[upsoft_section_numindex]; 
    }

    memset(upload_soft,0,sizeof(upload_soft));
    //sprintf(temp_soft,"%d.%d.%d.%d",(upsoft_section_numberall[0]),(upsoft_section_numberall[1]), \
    //                (upsoft_section_numberall[2]),(upsoft_section_numberall[3]));

    sprintf(upload_soft,"%c%c%c%c",(upsoft_section_numberall[0]+48),(upsoft_section_numberall[1]+48), \
                    (upsoft_section_numberall[2]+48),(upsoft_section_numberall[3])+48);
    //printf("***** upload_soft = %s ******\n",upload_soft);
}
