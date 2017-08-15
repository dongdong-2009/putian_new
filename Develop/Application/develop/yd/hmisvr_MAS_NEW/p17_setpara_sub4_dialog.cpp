#include "p17_setpara_sub4_dialog.h"
#include "ui_p17_setpara_sub4_dialog.h"
#include "globalhmi.h"

p17_setpara_sub4_dialog::p17_setpara_sub4_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::p17_setpara_sub4_dialog)
{
    ui->setupUi(this);
}

p17_setpara_sub4_dialog::~p17_setpara_sub4_dialog()
{
    delete ui;
}

void p17_setpara_sub4_dialog::changeEvent(QEvent *e)
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



static int add_num=0;
static int Timer=0;

void p17_setpara_sub4_dialog::init_page_dlg()
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

BOOL flg=TRUE;
BOOL web_flg=FALSE;

static BOOL fmaxv_flg=FALSE;
static BOOL fmaxi_flg=FALSE;
static BOOL fcost_flg=FALSE;
static BOOL fcost_serv_flg=FALSE;
static BOOL zero_add_flag=FALSE;

void p17_setpara_sub4_dialog::init_page_val()
{
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));

    ac_len=0;
    maxv_len=0;
    maxi_len=0;
    cost_len=0;
    cost_len_serv=0;
    websize_len=0;

    fac=0;
    fmaxv=0;
    fmaxi=0;
    fcost=0;
    fcost_serv=0;

    memset(ac,0,sizeof(ac));
    memset(maxv,0,sizeof(maxv));
    memset(maxi,0,sizeof(maxi));
    memset(cost,0,sizeof(cost));
    memset(cost_serv,0,sizeof(cost_serv));
   // memset(websize,0,sizeof(websize));

    int type_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"chargetype");
    type_val= read_profile_int(Section_name, Key_name,type_temp,config_path);

    int first_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"firsttype");
    first_val= read_profile_int(Section_name, Key_name,first_temp,config_path);

    int shape_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"gunshape");
    shape_val= read_profile_int(Section_name, Key_name,shape_temp,config_path);

    //最大电压
    float max_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestvolt");

    printf("****************** fmaxv_flg = %d\n",fmaxv_flg);

    if(read_profile_float(Section_name, Key_name,max_temp,config_path))
    {
        fmaxv= read_profile_float(Section_name, Key_name,max_temp,config_path);
        fmaxv_flg = TRUE;
        printf("****************** 1-fmaxv_flg = %d\n",fmaxv_flg);
    }
    else
    {

    }
    sprintf(maxv,"%0.2f",fmaxv);

    //最大电流
    max_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestcurrent");

    if(read_profile_float(Section_name, Key_name,max_temp,config_path))
    {
        fmaxi= read_profile_float(Section_name, Key_name,max_temp,config_path);
        fmaxi_flg = TRUE;
    }
    else
    {

    }
    sprintf(maxi,"%0.2f",fmaxi);

    /*
    max_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"carchecklen");
    fcost= read_profile_float(Section_name, Key_name,max_temp,config_path);
    sprintf(cost,"%d",(int)fcost);
    */

    //电费
    max_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"electricityprice");

    if(read_profile_float(Section_name, Key_name,max_temp,config_path))
    {
        fcost= read_profile_float(Section_name, Key_name,max_temp,config_path);
        fcost_flg = TRUE;
    }
    else
    {

    }
    sprintf(cost,"%0.2f",fcost);

    /*
    max_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"historysaveinterval");
    fcost_serv= read_profile_float(Section_name, Key_name,max_temp,config_path);
    sprintf(cost_serv,"%d",(int)fcost_serv);
    */

    //服务费
    max_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"servicemoney");

    if(read_profile_float(Section_name, Key_name,max_temp,config_path))
    {
        fcost_serv = read_profile_float(Section_name, Key_name,max_temp,config_path);
        fcost_serv_flg = TRUE;
    }
    else
    {

    }

    sprintf(cost_serv,"%0.2f",fcost_serv);

    max_temp=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"aclimitcurrent");
    fac= read_profile_float(Section_name, Key_name,max_temp,config_path);
    sprintf(ac,"%0.2f",fac);

    memset(Tempor_name,0,sizeof(Tempor_name));
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"websize");

    if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
    {
       // memcpy(websize,Tempor_name,sizeof(websize));
        web_flg=TRUE;
    }
    else
    {
        //memset(websize,0,sizeof(websize));
    }

}

void p17_setpara_sub4_dialog::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
}

void p17_setpara_sub4_dialog::btn_press()
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
    int num = 0;
    for(num = 0; num < 16;num++)
    {
        array[num]->setStyleSheet("QPushButton{border-image: url(:/icon/qrc/keyboard-b/T.png);}\
                                  QPushButton:pressed{border-image: url(:/icon/qrc/keyboard-b/T_press.png);}");
    }

}

void p17_setpara_sub4_dialog::timer_handle()
{
     update_page_info();
     update_hmi_page_index();
}

void p17_setpara_sub4_dialog::update_page_info()
{
    if(language_num == 1)
    {
         // ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
          //ui->label_stubnum->setText(QString::fromUtf8(" 客  服  电  话  :"));
    }
    else  if(language_num == 2)
    {
        //  ui->label_logo->setText("AC charging pile");
        ui->label_stubnum->setText("Telephone :");
    }

    //电压，电流，电费，服务费
    ui->label_maxv->setText(maxv);
    ui->label_maxi->setText(maxi);
    ui->lbl_cost->setText(cost);
    ui->lbl_cost_serv->setText(cost_serv);

    ui->lbl_accurrent->setText(ac);
   // ui->lbl_websize->setText(websize);

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

    if(type_val == 1)
    {
        ui->type_A->setChecked(TRUE);
        ui->type_B->setChecked(FALSE);
    }
    else if(type_val == 2)
    {
        ui->type_A->setChecked(FALSE);
        ui->type_B->setChecked(TRUE);
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

    add_num++;
    if(add_num==20)
    {
        add_num=0;
        Timer--;
        if(Timer<=0)
        {
            Timer = 0;
            ui->label_tip->setText(QString::fromUtf8(" "));
        }
    }
}

void p17_setpara_sub4_dialog::update_hmi_page_index()
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
    if(hmi_page_index != PAGEINDEX_SETPAGE_FOUR)
    {
        exit_page_dlg();
    }
    else
    {

    }
}

void p17_setpara_sub4_dialog::on_pbtn_16_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestcurrent");
    fmaxi=16;
    write_profile_int(Section_name,Key_name,fmaxi,config_path);
}

void p17_setpara_sub4_dialog::on_pbtn_32_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestcurrent");
    fmaxi=32;
    write_profile_int(Section_name,Key_name,fmaxi,config_path);
}

void p17_setpara_sub4_dialog::on_pbtn_63_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestcurrent");
    fmaxi=63;
    write_profile_int(Section_name,Key_name,fmaxi,config_path);
}

void p17_setpara_sub4_dialog::on_char_first_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"firsttype");
    first_val=1;
    write_profile_int(Section_name,Key_name,first_val,config_path);
}

void p17_setpara_sub4_dialog::on_net_first_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"firsttype");
    first_val=2;
    write_profile_int(Section_name,Key_name,first_val,config_path);
}

void p17_setpara_sub4_dialog::on_type_A_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"chargetype");
    type_val=1;
    write_profile_int(Section_name,Key_name,type_val,config_path);
}

void p17_setpara_sub4_dialog::on_type_B_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"chargetype");
    type_val=2;
    write_profile_int(Section_name,Key_name,type_val,config_path);
}

void p17_setpara_sub4_dialog::on_gun_line_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"gunshape");
    shape_val=1;
    write_profile_int(Section_name,Key_name,shape_val,config_path);
}

void p17_setpara_sub4_dialog::on_gun_socket_clicked()
{
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"gunshape");
    shape_val=2;
    write_profile_int(Section_name,Key_name,shape_val,config_path);
}

void p17_setpara_sub4_dialog::call_p16_dlg()
{

    timer->stop();
    emit signal_timer_p17dlg();
    delete p17_dlg;
    p17_dlg = NULL;
}

void p17_setpara_sub4_dialog::call_p24_dlg()
{
    timer->stop();
    if(p24_dlg){
            delete p24_dlg;
            p24_dlg = NULL;

    }
    p24_dlg = new  p24_setpara_sub6_dialog;
    p24_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p24dlg_timer()),p24_dlg,SLOT(init_page_dlg()));
    connect(p24_dlg,SIGNAL(signal_exit_p24dlg()),this,SLOT(exit_page_dlg()));
    connect(p24_dlg,SIGNAL(signal_timer_p24dlg()),this,SLOT(start_timer()));
    emit signal_enable_p24dlg_timer();
    p24_dlg->exec();
}

int num_17=0;

//电压
void p17_setpara_sub4_dialog::on_pbtn_1_clicked()
{
  num_17=1;

}

//电流
void p17_setpara_sub4_dialog::on_pbtn_2_clicked()
{
  //num_17=2;
  num_17=0;
  ui->label_tip->setText(QString::fromUtf8("该项不可更改!"));
  Timer = 3;
}

//电费
void p17_setpara_sub4_dialog::on_pbtn_3_clicked()
{
  num_17=3;

}

//服务费
void p17_setpara_sub4_dialog::on_pbtn_4_clicked()
{
  num_17=4;

}
void p17_setpara_sub4_dialog::on_pbtn_5_clicked()
{
  num_17=5;

}

static int index_temp = 0;
static int index_dot = 0;
static int index_dot_temp = 0;
static int count_dot = 0;
static int maxv_count_dot = 0;
static int maxi_count_dot = 0;
static int eleccost_count_dot = 0;
static int sercost_count_dot = 0;
static int dot_existmany_flg = 0;
static int num_temp = 0;

int p17_setpara_sub4_dialog::on_pbtn_num0_clicked()
{
    num_temp = 0;
    zero_add_flag=FALSE;

    switch(num_17)
    {
        case 1:
            if(0 == maxv_len)
            {
                ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                Timer = 3;
                return -1;
            }
            zero_add_flag=TRUE;
            break;

        case 2:
            if(0 == maxi_len)
            {
                ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                Timer = 3;
                return -1;
            }
            zero_add_flag=TRUE;
            break;

        case 3:  //electric fee

            zero_add_flag=TRUE;
            break;

        case 4:  //service fee

            zero_add_flag=TRUE;
            break;

         case 5:
            ac[ac_len++]='0';
            break;
       // default:
    }

    if(TRUE == zero_add_flag)
        answer_number_button();

    return 0;
}

void p17_setpara_sub4_dialog::on_pbtn_num1_clicked()
{
    num_temp = 1;
    answer_number_button();
}

void p17_setpara_sub4_dialog::on_pbtn_num2_clicked()
{
    num_temp = 2;
    answer_number_button();
}

void p17_setpara_sub4_dialog::on_pbtn_num3_clicked()
{
    num_temp = 3;
    answer_number_button();
}

void p17_setpara_sub4_dialog::on_pbtn_num4_clicked()
{
    num_temp = 4;
    answer_number_button();
}

void p17_setpara_sub4_dialog::on_pbtn_num5_clicked()
{
    num_temp = 5;
    answer_number_button();
}

void p17_setpara_sub4_dialog::on_pbtn_num6_clicked()
{
    num_temp = 6;
    answer_number_button();
}

void p17_setpara_sub4_dialog::on_pbtn_num7_clicked()
{
    num_temp = 7;
    answer_number_button();
}

void p17_setpara_sub4_dialog::on_pbtn_num8_clicked()
{
    num_temp = 8;
    answer_number_button();
}

void p17_setpara_sub4_dialog::on_pbtn_num9_clicked()
{
    num_temp = 9;
    answer_number_button();
}

void p17_setpara_sub4_dialog::on_pbtn_dot_clicked()
{
    answer_dot_button();
}

void p17_setpara_sub4_dialog::on_pbtn_back_clicked()
{
        switch(num_17)
        {
            case 1:
                maxv_len=0;
                memset(maxv,0,sizeof(maxv));
                maxv_count_dot = 0;
                break;

            case 2:
                maxi_len=0;
                memset(maxi,0,sizeof(maxi));
                maxi_count_dot = 0;
                break;

            case 3:
                cost_len=0;
                memset(cost,0,sizeof(cost));
                eleccost_count_dot = 0;
                break;

            case 4:
                cost_len_serv=0;
                memset(cost_serv,0,sizeof(cost_serv));
                sercost_count_dot = 0;
                break;

             case 5:
                ac_len=0;
                memset(ac,0,sizeof(ac));
                count_dot = 0;
                break;


            default:
                break;
        }

}

void p17_setpara_sub4_dialog::on_pbtn_up_clicked()
{

    DebugMsg(hmilev,5,"on_pbtn_up_clicked\n");

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestvolt");
    if(maxv_len>0)
    {
        fmaxv=atof(maxv);
        write_profile_float(Section_name,Key_name,fmaxv,config_path);
    }
    else
    {
         //ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestcurrent");
    if(maxi_len>0)
    {
        fmaxi=atof(maxi);
        write_profile_float(Section_name,Key_name,fmaxi,config_path);
    }
    else
    {
         //ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"electricityprice");
    if(cost_len>0)
    {
        write_profile_string(Section_name,Key_name,cost,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"servicemoney");
    if(cost_len_serv>0)
    {
        write_profile_string(Section_name,Key_name,cost_serv,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }
    hmi_button_dn_num=PAGEUP_BUTTON ;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

void p17_setpara_sub4_dialog::on_pbtn_down_clicked()
{
   DebugMsg(hmilev,5,"on_pbtn_down_clicked\n");
    //printf("****************** pbtn_down clicked!!! *******************\n");
    hmi_button_dn_num=PAGEDOWN_BUTTON ;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestvolt");
    if(maxv_len>0)
    {
        fmaxv=atof(maxv);
        write_profile_float(Section_name,Key_name,fmaxv,config_path);
    }
    else
    {
         //ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestcurrent");
    if(maxi_len>0)
    {
        fmaxi=atof(maxi);
        write_profile_float(Section_name,Key_name,fmaxi,config_path);
    }
    else
    {
         //ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"electricityprice");
    if(cost_len>0)
    {
        write_profile_string(Section_name,Key_name,cost,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"servicemoney");
    if(cost_len_serv>0)
    {
        write_profile_string(Section_name,Key_name,cost_serv,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }
    //hmi_page_index=PAGEINDEX_SETPAGE_FIVE;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

}

void p17_setpara_sub4_dialog::on_pbtn_go_clicked()
{
    DebugMsg(hmilev,5,"on_pbtn_cancel_clicked\n");
    hmi_button_dn_num=CANCEL_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

}

void p17_setpara_sub4_dialog::on_pbtn_ok_clicked()
{

    DebugMsg(hmilev,5,"on_pbtn_enter_clicked\n");

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestvolt");
    if(maxv_len>0)
    {
        fmaxv=atof(maxv);
        write_profile_float(Section_name,Key_name,fmaxv,config_path);
    }
    else
    {
         //ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"handsethigestcurrent");
    if(maxi_len>0)
    {
        fmaxi=atof(maxi);
        write_profile_float(Section_name,Key_name,fmaxi,config_path);
    }
    else
    {
         //ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"electricityprice");
    if(cost_len>0)
    {
        write_profile_string(Section_name,Key_name,cost,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"servicemoney");
    if(cost_len_serv>0)
    {
        write_profile_string(Section_name,Key_name,cost_serv,config_path);
    }
    else
    {
      //   ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
    }

    hmi_button_dn_num=OK_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

}

void p17_setpara_sub4_dialog::exit_page_dlg()
{
    DebugMsg(hmilev,8,"exit_page_dlg\n");
    init_page_val();
    timer->stop();
    emit signal_exit_p17dlg();
    num_17=0;
    index_temp = 0;
    index_dot = 0;
    index_dot_temp = 0;

    maxv_count_dot = 0;
    maxi_count_dot = 0;
    eleccost_count_dot = 0;
    sercost_count_dot = 0;

    dot_existmany_flg=0;
    zero_add_flag=FALSE;
    num_temp = 0;
}

void p17_setpara_sub4_dialog::answer_number_button()
{
    switch(num_17)
    {
        case 1:
            //判断有没有添加小数点
            if(index_dot_temp > 0)
            {
                //printf("***************** maxv_len = %d\n",maxv_len);
                //printf("***************** index_dot_temp = %d\n",index_dot_temp);

                if(maxv_len - index_dot_temp > 2)
                {
                    //提示 输入不符合规范
                    ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                    Timer = 3;
                }
                else
                {
                    //直接添加
                    if(fmaxv_flg)
                    {
                        memset(maxv,0,sizeof(maxv));
                        fmaxv_flg=FALSE;
                    }
                    maxv[maxv_len++]='0' + num_temp;
                }
            }
            else
            {
                //printf("***************** maxv_len = %d\n",maxv_len);
                //printf("***************** index_dot_temp = %d\n",index_dot_temp);

                //直接添加到数组的后面
                if(fmaxv_flg)
                {
                    memset(maxv,0,sizeof(maxv));
                    fmaxv_flg=FALSE;
                }
                maxv[maxv_len++]='0' + num_temp;
            }
            break;

        case 2:
            //printf("***************** maxv_len = %d\n",maxv_len);
            //printf("***************** index_dot_temp = %d\n",index_dot_temp);

            //判断有没有添加小数点
            if(index_dot_temp > 0)
            {

                if(maxv_len - index_dot_temp > 2)
                {
                    //提示 输入不符合规范
                    ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                    Timer = 3;
                }
                else
                {
                    //直接添加
                    if(fmaxi_flg)
                    {
                        memset(maxi,0,sizeof(maxi));
                        fmaxi_flg=FALSE;
                    }
                    maxi[maxi_len++]='0' + num_temp;
                }
            }
            else
            {
                //直接添加到数组的后面
                if(fmaxi_flg)
                {
                    memset(maxi,0,sizeof(maxi));
                    fmaxi_flg=FALSE;
                }
                maxi[maxi_len++]='0' + num_temp;
            }
            break;

        case 3:
            //printf("***************** case 3: - cost_len = %d\n",cost_len);
            //printf("***************** case 3: - index_dot_temp = %d\n",index_dot_temp);

            //判断有没有添加小数点
            if(index_dot_temp > 0)
            {
                if(cost_len - index_dot_temp > 2)
                {
                    //提示 输入不符合规范
                    ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                    Timer = 3;
                }
                else
                {
                    //直接添加
                    if(fcost_flg)
                    {
                        memset(cost,0,sizeof(cost));
                        fcost_flg=FALSE;
                    }
                    cost[cost_len++]='0' + num_temp;
                }
            }
            else
            {
                //直接添加到数组的后面
                if(fcost_flg)
                {
                    memset(cost,0,sizeof(cost));
                    fcost_flg=FALSE;
                }
                cost[cost_len++]='0' + num_temp;
            }

            break;

        case 4:
            //printf("***************** case 4:  cost_len_serv = %d\n",cost_len_serv);
            //printf("***************** case 4: index_dot_temp = %d\n",index_dot_temp);

            //判断有没有添加小数点
            if(index_dot_temp > 0)
            {
                if(cost_len_serv - index_dot_temp > 2)
                {
                    //提示 输入不符合规范
                    ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                    Timer = 3;
                }
                else
                {
                    //直接添加
                    if(fcost_serv_flg)
                    {
                        memset(cost_serv,0,sizeof(cost_serv));
                        fcost_serv_flg=FALSE;
                    }
                    cost_serv[cost_len_serv++]='0' + num_temp;
                }
            }
            else
            {
                //直接添加到数组的后面
                if(fcost_serv_flg)
                {
                    memset(cost_serv,0,sizeof(cost_serv));
                    fcost_serv_flg=FALSE;
                }
                cost_serv[cost_len_serv++]='0' + num_temp;
            }
            break;

         case 5:

                ac[ac_len++]='1';
                break;
       // default:
    }
}

void p17_setpara_sub4_dialog::answer_dot_button()
{
static int maxv_count_dot = 0;
static int maxi_count_dot = 0;
static int eleccost_count_dot = 0;
static int sercost_count_dot = 0;
    switch(num_17)
    {
        case 1:
            //提示输入错误
            if(0 == maxv_len)
            {
                ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                Timer = 3;
            }
            else
            {
                //查看如果超出了一个，就提示错误;
                for(index_dot = 0;index_dot < maxv_len;index_dot++)
                {
                    if('.' == maxv[index_dot])
                    {
                        if(maxv_count_dot > 0)
                            //提示输入错误
                            ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                            Timer = 3;
                            dot_existmany_flg = 1;
                            break;
                    }
                    else
                    {

                    }
                }

                //如果没有多个小数点，就向后面添加小数点
                if(0 == dot_existmany_flg)
                {
                    //存入
                    if(fmaxv_flg)
                    {
                        memset(maxv,0,sizeof(maxv));
                        fmaxv_flg=FALSE;
                    }
                    //记下小数点的位置
                    index_dot_temp = maxv_len;

                    maxv[maxv_len++]='.';
                    maxv_count_dot++;
                }
            }

            index_dot = 0;
            dot_existmany_flg = 0;
            break;

        case 2:
            //提示输入错误
            if(0 == maxi_len)
            {
                ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                Timer = 3;
            }
            else
            {
                //查看如果超出了一个，就提示错误;
                for(index_dot = 0;index_dot < maxi_len;index_dot++)
                {
                    if('.' == maxi[index_dot])
                    {
                        if(maxi_count_dot > 0)
                            //提示输入错误
                            ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                            Timer = 3;
                            dot_existmany_flg = 1;
                            break;
                    }
                    else
                    {

                    }
                }

                //如果没有多个小数点，就向后面添加小数点
                if(0 == dot_existmany_flg)
                {
                    //存入
                    if(fmaxi_flg)
                    {
                        memset(maxi,0,sizeof(maxi));
                        fmaxi_flg=FALSE;
                    }
                    //记下小数点的位置
                    index_dot_temp = maxi_len;

                    maxi[maxi_len++]='.';
                    maxi_count_dot++;
                }
            }
            index_dot = 0;
            dot_existmany_flg = 0;
            break;

        case 3:
            //提示输入错误
            if(0 == cost_len)
            {
                ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                Timer = 3;
            }
            else
            {
                //查看如果超出了一个，就提示错误;
                for(index_dot = 0;index_dot < cost_len;index_dot++)
                {
                    if('.' == cost[index_dot])
                    {
                        if(eleccost_count_dot > 0)
                            //提示输入错误
                            ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                            Timer = 3;
                            dot_existmany_flg = 1;
                            break;
                    }
                    else
                    {

                    }
                }

                //如果没有多个小数点，就向后面添加小数点
                if(0 == dot_existmany_flg)
                {
                    //存入
                    if(fcost_flg)
                    {
                        memset(cost,0,sizeof(cost));
                        fcost_flg=FALSE;
                    }
                    //记下小数点的位置
                    index_dot_temp = cost_len;

                    cost[cost_len++]='.';
                    eleccost_count_dot++;
                }
            }

            index_dot = 0;
            dot_existmany_flg = 0;
            break;

            //printf("***************** case 3 - dot: maxv_len = %d\n",maxv_len);
            //printf("***************** case 3 - dot: index_dot_temp = %d\n",index_dot_temp);


        case 4:
            //提示输入错误
            if(0 == cost_len_serv)
            {
                ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                Timer = 3;
            }
            else
            {
                //查看如果超出了一个，就提示错误;
                for(index_dot = 0;index_dot < cost_len_serv;index_dot++)
                {
                    if('.' == cost_serv[index_dot])
                    {
                        if(sercost_count_dot > 0)
                            //提示输入错误
                            ui->label_tip->setText(QString::fromUtf8("输入不符合规范!"));
                            Timer = 3;
                            dot_existmany_flg = 1;
                            break;
                    }
                    else
                    {

                    }
                }

                //如果没有多个小数点，就向后面添加小数点
                if(0 == dot_existmany_flg)
                {
                    //存入
                    if(fcost_serv_flg)
                    {
                        memset(cost_serv,0,sizeof(cost_serv));
                        fcost_flg=FALSE;
                    }
                    //记下小数点的位置
                    index_dot_temp = cost_len_serv;

                    cost_serv[cost_len_serv++]='.';
                    sercost_count_dot++;
                }
            }
            index_dot = 0;
            dot_existmany_flg = 0;
            break;

            //printf("***************** case 4 - dot: cost_len_serv = %d\n",cost_len_serv);
            //printf("***************** case 4 - dot: index_dot_temp = %d\n",index_dot_temp);

         case 5:

                ac[ac_len++]='.';
                break;
       // default:

                //

    }
}