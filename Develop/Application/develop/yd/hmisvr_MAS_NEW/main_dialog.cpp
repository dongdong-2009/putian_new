#include "main_dialog.h"
#include "ui_main_dialog.h"
#include "globalhmi.h"

main_dialog::main_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::main_dialog)
{
    ui->setupUi(this);
    init_main_dlg();
}

main_dialog::~main_dialog()
{
    delete ui;
}

void main_dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void main_dialog::init_main_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(SETPAGE_FLUSH_TIMER);
    init_database();

    //QPalette pe;
    //pe.setColor(QPalette::WindowText,Qt::white);

}

int add_num=0;
char web[50]= {};
static char web_real[50]= {};
void main_dialog::init_database()
{
    void *fp;
    DebugMsg(hmilev,8,"init_database\n");
    if((fp=dlopen("libdatabase.so",RTLD_LAZY))==NULL)
    {
        fputs(dlerror(),stderr);
        printf("\n");
        printf("can not open the library\n");
        exit(1);
    }
    API_Read_DB_Nbyte = (INT16 (*)(UINT32,void*,UINT16))dlsym(fp,"API_Read_DB_Nbyte");
    API_Write_DB_Nbyte = (INT16 (*)(UINT32,void*,UINT16))dlsym(fp,"API_Write_DB_Nbyte");
    API_DB_Initial = (void (*)())dlsym(fp,"API_DB_Initial");

    API_DB_Initial();

    UINT8 data = PAGEINDEX_MAIN;
    API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&data),sizeof(data));
    API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX_CUR,(INT8 *)(&data),sizeof(data));
    data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));

    int net_flg;
    net_flg=0;
    int temp_net;
    temp_net=0;
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"networkservice");
    net_flg=read_profile_int(Section_name,Key_name,temp_net,config_path);
    API_Write_DB_Nbyte(PL_NEEDNETWORK_FLAG,(BOOL *)(&net_flg),sizeof(net_flg));

    UINT8 card_check = 0;
    API_Write_DB_Nbyte(PL_CHRPASSWRDERR_FLAG,(UINT8 *)(&card_check),sizeof(card_check));
}

void main_dialog::start_timer()
{
    timer->start(SETPAGE_FLUSH_TIMER);
}

int num_move = 0;
int move_flag = 0;
void main_dialog::timer_handle()
{
    memset(code,0,sizeof(code));
    memset(Tempor_name,0,sizeof(Tempor_name));
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"stubcode");
    char buf_code[100]= {0};

    if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
    {
        int num_add = 0;
        for(num_add = 0; num_add < strlen(Tempor_name); num_add++)
        {
            Tempor_name[num_add]=toupper(Tempor_name[num_add]);
        }
        memcpy(code,Tempor_name,sizeof(code));
        memset(Tempor_name,0,sizeof(Tempor_name));
        Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
        Inibuf_init(Key_name,BUFFERLEN_32,"websize");
        if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
        {
            memcpy(websize,Tempor_name,sizeof(websize));
        }
        else
        {
            memset(websize,0,sizeof(websize));
        }

        snprintf(buf_code,100,"/usr/APP/qrencode -o 1.png -s 4 %s%s%s%s",qrencd_str_header,websize,qrencd_str_middle,code);

        system(buf_code);
        memset(buf_code,0,100);
        snprintf(buf_code,100,"pkill qrencode");
        system(buf_code);
    }
    else
    {
        memset(code,0,sizeof(code));
    }

    ui->label_piccode->setPixmap(QPixmap("/usr/APP/1.png"));

    memset(web_real,0,sizeof(web_real));
    memset(Tempor_name,0,sizeof(Tempor_name));
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"real_websize");
    if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
    {
        memcpy(web_real,Tempor_name,sizeof(web_real));
    }
    else
    {
        memset(web_real,0,sizeof(web_real));
    }

    memset(phonenum,0,sizeof(phonenum));
    memset(Tempor_name,0,sizeof(Tempor_name));
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"oneemergencycall");
    if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
    {
        memcpy(phonenum,Tempor_name,sizeof(phonenum));
    }
    else
    {
        memset(phonenum,0,sizeof(phonenum));
    }

    memset(phonenum_2,0,sizeof(phonenum_2));
    memset(Tempor_name,0,sizeof(Tempor_name));
    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"twoemergencycall");
    if(read_profile_string(Section_name, Key_name, Tempor_name, INIFILE_LININBUF_SIZE,"",config_path))
    {
        memcpy(phonenum_2,Tempor_name,sizeof(phonenum_2));
        // sprintf(phonenum_2,"%c%c%c-%c%c%c%c-%c%c%c%c",phonenum_2[0],phonenum_2[1],phonenum_2[2],phonenum_2[3],phonenum_2[4],phonenum_2[5],phonenum_2[6],phonenum_2[7],phonenum_2[8],phonenum_2[9],phonenum_2[10]);
    }
    else
    {
        memset(phonenum_2, 0, sizeof(phonenum_2));
    }

    BOOL net_flg2 = 0;
    BOOL service_open = 0;
    ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));
    ui->label_code->setText(code);
    ui->label_phone->setText(phonenum);
    ui->label_phone_2->setText(phonenum_2);

    ui->lbl_web->setText(web_real);

    ui->pbtn_setnet->setStyleSheet("border-image: url(:/icon/qrc/icon/0.png);");

    API_Read_DB_Nbyte(PL_NETWORKLINKSTATE_FLAG,(BOOL *)(&net_flg2),sizeof(net_flg2));
    if(net_flg2)
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

    Inibuf_init(Section_name,BUFFERLEN_32,"SYSTEMINFOR");
    Inibuf_init(Key_name,BUFFERLEN_32,"open_service");
    service_open=read_profile_int(Section_name,Key_name,1,config_path);
    if(language_num == 1)
    {
        //ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
        ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
        if(service_open == 1)
        {
            ui->label_title_3->setText(QString::fromUtf8("请  刷  卡  充  电"));
        }
        else   if(service_open == 2)
        {
            ui->label_title_3->setText(QString::fromUtf8("设备未开放充电服务"));
        }
    }
    else  if(language_num == 2)
    {
        // ui->label_logo->setText("AC charging pile");
        ui->label_title_2->setText("Welcome to use Charging system of Potevio");
        // ui->label_title_3->setText("Please swipe the card");
        ui->label_stubnum->setText("Telephone :");
    }
    check_hmi_page_index();
}

void main_dialog::check_hmi_page_index()
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

    //printf("************** page_index: %d **************\n",hmi_page_index);

    if(hmi_page_index==PAGEINDEX_MAIN)
    {
        if(firsterr_dlg)
        {
            delete firsterr_dlg;
            firsterr_dlg = NULL;
        }
        if(p01_dlg)
        {
            delete p01_dlg;
            p01_dlg = NULL;
        }
        if(p02_dlg)
        {
            delete p02_dlg;
            p02_dlg = NULL;
        }
        if(p03_dlg)
        {
            delete p03_dlg;
            p03_dlg = NULL;
        }
        if(p05_dlg)
        {
            delete p05_dlg;
            p05_dlg = NULL;
        }
        if(p07_dlg)
        {
            delete p07_dlg;
            p07_dlg = NULL;
        }
        if(p08_dlg)
        {
            delete p08_dlg;
            p08_dlg = NULL;
        }
        if(p09_dlg)
        {
            delete p09_dlg;
            p09_dlg = NULL;
        }
        if(p13_dlg)
        {
            delete p13_dlg;
            p13_dlg = NULL;
        }
        if(p14_dlg)
        {
            delete p14_dlg;
            p14_dlg = NULL;
        }
        if(p15_dlg)
        {
            delete p15_dlg;
            p15_dlg = NULL;
        }
        if(p16_dlg)
        {
            delete p16_dlg;
            p16_dlg = NULL;
        }
        if(p17_dlg)
        {
            delete p17_dlg;
            p17_dlg = NULL;
        }
        if(p18_dlg)
        {
            delete p18_dlg;
            p18_dlg = NULL;
        }
        if(p19_dlg)
        {
            delete p19_dlg;
            p19_dlg = NULL;
        }
        if(p20_dlg)
        {
            delete p20_dlg;
            p20_dlg = NULL;
        }
        if(p21_dlg)
        {
            delete p21_dlg;
            p21_dlg = NULL;
        }
        if(p24_dlg)
        {
            delete p24_dlg;
            p24_dlg = NULL;
        }
        if(dlg_1)
        {
            delete dlg_1;
            dlg_1 = NULL;
        }
        if(dlg_2)
        {
            delete dlg_2;
            dlg_2 = NULL;
        }
        if(err_dlg)
        {
            delete err_dlg;
            err_dlg = NULL;
        }
        if(book_dlg)
        {
            delete book_dlg;
            book_dlg = NULL;
        }
        if(back_dlg)
        {
            delete back_dlg;
            back_dlg = NULL;
        }
        if(checkcard_dlg)
        {
            delete checkcard_dlg;
            checkcard_dlg = NULL;
        }
        if(diff_card_dlg)
        {
            delete diff_card_dlg;
            diff_card_dlg = NULL;
        }
        if(end_dlg)
        {
            delete end_dlg;
            end_dlg = NULL;
        }
        if(link_err_dlg)
        {
            delete link_err_dlg;
            link_err_dlg = NULL;
        }
        if(money_left_dlg)
        {
            delete money_left_dlg;
            money_left_dlg = NULL;
        }
        if(pull_gun_dlg)
        {
            delete pull_gun_dlg;
            pull_gun_dlg = NULL;
        }
        if(history_dlg)
        {
            delete history_dlg;
            history_dlg = NULL;
        }
        if(his_choose_dlg)
        {
            delete his_choose_dlg;
            his_choose_dlg = NULL;
        }
        if(passwd_app_dlg)
        {
            delete passwd_app_dlg;
            passwd_app_dlg = NULL;
        }
        if(carnum_dlg)
        {
            delete carnum_dlg;
            carnum_dlg=NULL;
        }
        if(err_carconfirm_dlg)
        {
            delete err_carconfirm_dlg;
            err_carconfirm_dlg=NULL;
        }
        if(not_putiancard_dlg)
        {
            delete not_putiancard_dlg;
            not_putiancard_dlg=NULL;
        }
        if(err_choose_dlg)
        {
            delete err_choose_dlg;
            err_choose_dlg=NULL;
        }
        if(local_err_dlg)
        {
            delete local_err_dlg;
            local_err_dlg=NULL;
        }
        if(remote_err_dlg)
        {
            delete remote_err_dlg;
            remote_err_dlg=NULL;
        }
    }
    else if(hmi_page_index==PAGEINDEX_ERR_CHOOSE)
    {
        printf("@@@@Go to PAGEINDEX_ERR_CHOOSE!\r\n");
        call_err_choose();
    }
    else if(hmi_page_index==PAGEINDEX_LOCAL_ERR)
    {
        printf("@@@@Go to PAGEINDEX_LOCAL_ERR!\r\n");
        call_local_err();
    }
    else if(hmi_page_index==PAGEINDEX_REMOTE_ERR)
    {
        printf("@@@@Go to PAGEINDEX_REMOTE_ERR!\r\n");
        call_remote_err();
    }
    else if(hmi_page_index==PAGEINDEX_HISTORY_NET)
    {
        //    printf("@@@@Go to PAGE_PASSWD!\r\n");
        call_history_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_PASSWD)
    {
        //    printf("@@@@Go to PAGE_PASSWD!\r\n");
        call_p01_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_SERVICECHOICE)
    {
        //    printf("@@@@Go to PAGE_SERVICECHOICE!\r\n");
        call_p02_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_HISTORYCHECK)
    {
        //    printf("@@@@Go to PAGEINDEX_HISTORYCHECK!\r\n");
        call_p03_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_CHARGELINK)
    {
        //     printf("@@@@Go to PAGEINDEX_CHARGELINK!\r\n");
        call_p05_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_CHARGETYPECHOSE)
    {
        //     printf("@@@@Go to PAGEINDEX_CHARGELINK!\r\n");
        call_p07_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_CHARGEBYTIME)
    {
        //     printf("@@@@Go to PAGEINDEX_CHARGELINK!\r\n");
        call_p08_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_CHARGEBYCAPA)
    {
        //     printf("@@@@Go to PAGEINDEX_CHARGELINK!\r\n");
        call_p09_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_SETPASSWRDIPT)
    {
        //     printf("@@@@Go to PAGEINDEX_SETPASSWRDIPT!\r\n");
        call_p13_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_SETPAGE_ONE)
    {
        //     printf("@@@@Go to PAGEINDEX_SETPASSWRDIPT!\r\n");
        call_p14_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_SETPAGE_TWO)
    {
        //     printf("@@@@Go to PAGEINDEX_SETPASSWRDIPT!\r\n");
        call_p15_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_SETPAGE_THR)
    {
        //     printf("@@@@Go to PAGEINDEX_SETPASSWRDIPT!\r\n");
        call_p16_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_SETPAGE_FOUR)
    {
        // printf("@@@@Go to PAGEINDEX_SETPASSWRDIPT!\r\n");
        call_p17_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_SETPAGE_FIVE)
    {
        // printf("@@@@Go to PAGEINDEX_SETPAGE_FIVE!\r\n");
        call_p18_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_ACCHARGEPROCESS)
    {
        //    printf("@@@@Go to PAGEINDEX_ACCHARGEPROCESS!\r\n");
        call_p19_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_ACPAYOFF)
    {
        //  printf("@@@@Go to PAGEINDEX_ACPAYOFF!\r\n");
        call_p20_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_JUDGE_CONTINUE)
    {
        //      printf("@@@@Go to PAGEINDEX_JUDGE_CONTINUE!\r\n");
        call_p21_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_SETPAGE_SIX)
    {
        // printf("@@@@Go to PAGEINDEX_SETPAGE_SIX!\r\n");
        call_p24_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_LITTLEWINDOW_ONE)
    {
        // printf("@@@@Go to PAGEINDEX_LITTLEWINDOW_ONE!\r\n");
        call_dlg_1();
    }
    else if(hmi_page_index==PAGEINDEX_PASSWD_TWO)
    {
//       printf("@@@@Go to PAGEINDEX_PASSWD_TWO!\r\n");
        call_dlg_2();
    }
    else if(hmi_page_index==PAGEINDEX_ERRORCHECK)
    {
        //      printf("@@@@Go to PAGEINDEX_ERRORCHECK!\r\n");
        call_err_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_BOOKSERVICE)
    {
        //    printf("@@@@Go to PAGEINDEX_BOOKSERVICE!\r\n");
        call_book_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_LEFTMONEY)
    {
        //    printf("@@@@Go to PAGEINDEX_LEFTMONEY!\r\n");
        call_money_left_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_CHARGELINK_ERR)
    {
        //    printf("@@@@Go to PAGEINDEX_CHARGELINK_ERR!\r\n");
        call_link_err_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_END)
    {
        //    printf("@@@@Go to PAGEINDEX_CHARGELINK_ERR!\r\n");
        call_end_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_FIRST_ERR)
    {
        //    printf("@@@@Go to PAGEINDEX_CHARGELINK_ERR!\r\n");
        call_firsterr_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_DIFFERENT_CARD)
    {
        //    printf("@@@@Go to PAGEINDEX_DIFFERENT_CARD!\r\n");
        call_diff_card_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_PULLGUN)
    {
        //    printf("@@@@Go to PAGEINDEX_PULLGUN!\r\n");
        call_pull_gun();
    }
    else if(hmi_page_index==PAGEINDEX_BACK)
    {
        //    printf("@@@@Go to PAGEINDEX_PULLGUN!\r\n");
        call_back();
    }
    else if(hmi_page_index==PAGEINDEX_CHECKCARD)
    {
        //    printf("@@@@Go to PAGEINDEX_PULLGUN!\r\n");
        call_checkcard_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_HISTORY_CHOOSE)
    {
        //    printf("@@@@Go to PAGEINDEX_PULLGUN!\r\n");
        call_his_choose_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_PASSWD_APP)
    {
        //    printf("@@@@Go to PAGEINDEX_PULLGUN!\r\n");
        call_passwd_app_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_CARNUM)
    {
        //    printf("@@@@Go to PAGEINDEX_PULLGUN!\r\n");
        call_carnum_dlg();
    }
    else if(hmi_page_index==PAGEINDEX_ERR_CARCONFIRM)
    {
        //    printf("@@@@Go to PAGEINDEX_ERR_CARCONFIRM!\r\n");
        call_err_carconfirm();
    }
    else if(hmi_page_index==PAGEINDEX_NOT_PUTIANCARD)
    {
        printf("@@@@Go to PAGEINDEX_NOT_PUTIANCARD!\r\n");
        call_not_putiancard();
    }
    else
    {
        ErrMsg("hmi_page_index error[%d]\n",hmi_page_index);
        //exit(1);
    }

}

void main_dialog::call_remote_err()
{
    timer->stop();
    if(remote_err_dlg)
    {
        delete remote_err_dlg;
        remote_err_dlg = NULL;
    }
    remote_err_dlg = new  dialog_remote_err;
    remote_err_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_remoterr_timer()),remote_err_dlg,SLOT(init_page_dlg()));
    connect(remote_err_dlg,SIGNAL(signal_exit_dlg()),this,SLOT(start_timer()));

    emit signal_enable_remoterr_timer();
    remote_err_dlg->exec();

    printf("*********** start to  remote_err_dlg ************\n");

}

void main_dialog::call_local_err()
{
    timer->stop();
    if(local_err_dlg)
    {
        delete local_err_dlg;
        local_err_dlg = NULL;
    }
    local_err_dlg = new  dialog_local_err;
    local_err_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_localerr_timer()),local_err_dlg,SLOT(init_page_dlg()));
    connect(local_err_dlg,SIGNAL(signal_exit_dlg()),this,SLOT(start_timer()));

    emit signal_enable_localerr_timer();
    local_err_dlg->exec();

}

void main_dialog::call_err_choose()
{
    timer->stop();
    if(err_choose_dlg)
    {
        delete err_choose_dlg;
        err_choose_dlg = NULL;
    }
    err_choose_dlg = new  dialog_err_choose;
    err_choose_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_errchoose_timer()),err_choose_dlg,SLOT(init_page_dlg()));
    connect(err_choose_dlg,SIGNAL(signal_exit_dlg()),this,SLOT(start_timer()));

    emit signal_enable_errchoose_timer();
    err_choose_dlg->exec();

}

void main_dialog::call_not_putiancard()
{
    timer->stop();
    if(not_putiancard_dlg)
    {
        delete not_putiancard_dlg;
        not_putiancard_dlg = NULL;
    }
    not_putiancard_dlg = new  dialog_not_putiancard;
    not_putiancard_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_notputiancard_timer()),not_putiancard_dlg,SLOT(init_page_dlg()));
    connect(not_putiancard_dlg,SIGNAL(signal_exit_dlg()),this,SLOT(start_timer()));

    emit signal_enable_notputiancard_timer();
    not_putiancard_dlg->exec();

    //printf("****** PAGEINDEX_NOT_PUTIANCARD = (46)******\n");
    //printf("************** page_index: %d **************\n",hmi_page_index);
}
void main_dialog::call_err_carconfirm()
{
    timer->stop();
    if(err_carconfirm_dlg)
    {
        delete err_carconfirm_dlg;
        err_carconfirm_dlg = NULL;
    }
    err_carconfirm_dlg = new  dialog_err_carconfirm;
    err_carconfirm_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_errconfirm_timer()),err_carconfirm_dlg,SLOT(init_page_dlg()));
    connect(err_carconfirm_dlg,SIGNAL(signal_exit_dlg()),this,SLOT(start_timer()));

    emit signal_enable_errconfirm_timer();
    err_carconfirm_dlg->exec();
}

void main_dialog::call_carnum_dlg()
{
    timer->stop();
    if(carnum_dlg)
    {
        delete carnum_dlg;
        carnum_dlg = NULL;
    }
    carnum_dlg = new  Dialog_carnum;
    carnum_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_carnum_timer()),carnum_dlg,SLOT(init_page_dlg()));
    connect(carnum_dlg,SIGNAL(signal_exit_dlg()),this,SLOT(start_timer()));

    emit signal_enable_carnum_timer();
    carnum_dlg->exec();
}

void main_dialog::call_passwd_app_dlg()
{
    timer->stop();
    if(passwd_app_dlg)
    {
        delete passwd_app_dlg;
        passwd_app_dlg = NULL;
    }
    passwd_app_dlg = new  Dialog_passwd_app;
    passwd_app_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_passwd_app_timer()),passwd_app_dlg,SLOT(init_page_dlg()));
    connect(passwd_app_dlg,SIGNAL(signal_exit_dlg()),this,SLOT(start_timer()));

    emit signal_enable_passwd_app_timer();
    passwd_app_dlg->exec();
}


void main_dialog::call_his_choose_dlg()
{
    timer->stop();
    if(his_choose_dlg)
    {
        delete his_choose_dlg;
        his_choose_dlg = NULL;
    }
    his_choose_dlg = new  Dialog_history_choose;
    his_choose_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_his_choose_timer()),his_choose_dlg,SLOT(init_page_dlg()));
    connect(his_choose_dlg,SIGNAL(signal_exit_dlg()),this,SLOT(start_timer()));

    emit signal_enable_his_choose_timer();
    his_choose_dlg->exec();
}

void main_dialog::call_pull_gun()
{
    timer->stop();
    if(pull_gun_dlg)
    {
        delete pull_gun_dlg;
        pull_gun_dlg = NULL;
    }
    pull_gun_dlg = new  Dialog_pull_gun;
    pull_gun_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_pull_gun_timer()),pull_gun_dlg,SLOT(init_page_dlg()));
    connect(pull_gun_dlg,SIGNAL(signal_exit_pulldlg()),this,SLOT(start_timer()));

    emit signal_enable_pull_gun_timer();
    pull_gun_dlg->exec();
}

void main_dialog::call_diff_card_dlg()
{
    timer->stop();
    if(diff_card_dlg)
    {
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


void main_dialog::call_end_dlg()
{
    timer->stop();
    if(end_dlg)
    {
        delete end_dlg;
        end_dlg = NULL;
    }
    end_dlg = new  Dialog_end;
    end_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_end_timer()),end_dlg,SLOT(init_page_dlg()));
    connect(end_dlg,SIGNAL(signal_exit_end()),this,SLOT(start_timer()));

    emit signal_enable_end_timer();
    end_dlg->exec();
}

void main_dialog::call_firsterr_dlg()
{
    timer->stop();
    if(firsterr_dlg)
    {
        delete firsterr_dlg;
        firsterr_dlg = NULL;
    }
    firsterr_dlg = new  Dialog_first_err;
    firsterr_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_firsterr_timer()),firsterr_dlg,SLOT(init_page_dlg()));
    connect(firsterr_dlg,SIGNAL(signal_exit_firsterr()),this,SLOT(start_timer()));

    emit signal_enable_firsterr_timer();
    firsterr_dlg->exec();
}

void main_dialog::call_link_err_dlg()
{
    timer->stop();
    if(link_err_dlg)
    {
        delete link_err_dlg;
        link_err_dlg = NULL;
    }
    link_err_dlg = new  Dialog_link_err;
    link_err_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_link_err_timer()),link_err_dlg,SLOT(init_page_dlg()));
    connect(link_err_dlg,SIGNAL(signal_exit_dlg_link()),this,SLOT(start_timer()));

    emit signal_enable_link_err_timer();
    link_err_dlg->exec();
}
void main_dialog::call_money_left_dlg()
{
    timer->stop();
    if(money_left_dlg)
    {
        delete money_left_dlg;
        money_left_dlg = NULL;
    }
    money_left_dlg = new  Dialog_money_left;
    money_left_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_money_left_timer()),money_left_dlg,SLOT(init_page_dlg()));
    connect(money_left_dlg,SIGNAL(signal_exit_money_left()),this,SLOT(start_timer()));
    emit signal_enable_money_left_timer();
    money_left_dlg->exec();
}

void main_dialog::call_back()
{
    timer->stop();
    if(back_dlg)
    {
        delete back_dlg;
        back_dlg = NULL;
    }
    back_dlg = new  Dialog_back;
    back_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_back_timer()),back_dlg,SLOT(init_page_dlg()));
    connect(back_dlg,SIGNAL(signal_exit_backdlg_judge()),this,SLOT(start_timer()));

    emit signal_enable_back_timer();
    back_dlg->exec();
}
void main_dialog::call_checkcard_dlg()
{
    timer->stop();
    if(checkcard_dlg)
    {
        delete checkcard_dlg;
        checkcard_dlg = NULL;
    }
    checkcard_dlg = new  Dialog_checkcaed;
    checkcard_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_checkcard_timer()),checkcard_dlg,SLOT(init_page_dlg()));
    connect(checkcard_dlg,SIGNAL(signal_exit_checkcarddlg()),this,SLOT(start_timer()));
    emit signal_enable_checkcard_timer();
    checkcard_dlg->exec();
}

void main_dialog::call_dlg_1()
{
    timer->stop();
    if(dlg_1)
    {
        delete dlg_1;
        dlg_1 = NULL;
    }
    dlg_1 = new  dialog_1;
    dlg_1->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_dlg_1_timer()),dlg_1,SLOT(init_page_dlg()));
    connect(dlg_1,SIGNAL(signal_exit_dlg_1()),this,SLOT(start_timer()));
    emit signal_enable_dlg_1_timer();
    dlg_1->exec();

    //printf("******** go to the dialog_1,%s**********\n",__FILE__);
}

void main_dialog::call_dlg_2()
{
    timer->stop();
    if(dlg_2)
    {
        delete dlg_2;
        dlg_2 = NULL;
    }
    dlg_2 = new  dialog_2;
    dlg_2->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_dlg_2_timer()),dlg_2,SLOT(init_page_dlg()));
    connect(dlg_2,SIGNAL(signal_exit_dlg_2()),this,SLOT(start_timer()));
    emit signal_enable_dlg_2_timer();
    dlg_2->exec();
}

void main_dialog::call_book_dlg()
{
    timer->stop();
    if(book_dlg)
    {
        delete book_dlg;
        book_dlg = NULL;
    }
    book_dlg = new  Dialog_book;
    book_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_book_timer()),book_dlg,SLOT(init_page_dlg()));
    connect(book_dlg,SIGNAL(signal_exit_bookdlg()),this,SLOT(start_timer()));

    emit signal_enable_book_timer();
    book_dlg->exec();
}

void main_dialog::call_err_dlg()
{
    timer->stop();
    if(err_dlg)
    {
        delete err_dlg;
        err_dlg = NULL;
    }
    err_dlg = new  Dialog_error;
    err_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_err_timer()),err_dlg,SLOT(init_page_dlg()));
    connect(err_dlg,SIGNAL(signal_exit_errdlg()),this,SLOT(start_timer()));

    emit signal_enable_err_timer();
    err_dlg->exec();
}

void main_dialog::call_history_dlg()
{
    timer->stop();
    if(history_dlg)
    {
        delete history_dlg;
        history_dlg = NULL;
    }
    history_dlg = new  Dialog_history_net;
    history_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_historydlg_timer()),history_dlg,SLOT(init_page_dlg()));
    connect(history_dlg,SIGNAL(signal_exit_historydlg()),this,SLOT(start_timer()));

    emit signal_enable_historydlg_timer();
    history_dlg->exec();
}

void main_dialog::call_p02_dlg()
{
    timer->stop();
    if(p02_dlg)
    {
        delete p02_dlg;
        p02_dlg = NULL;
    }
    p02_dlg = new  p02_servchoose_dialog;
    p02_dlg->setWindowFlags(Qt::FramelessWindowHint);
    connect(this,SIGNAL(signal_enable_p02dlg_timer()),p02_dlg,SLOT(init_page_dlg()));
    connect(p02_dlg,SIGNAL(signal_exit_p02dlg()),this,SLOT(start_timer()));
    emit signal_enable_p02dlg_timer();
    p02_dlg->exec();
}

void main_dialog::call_p03_dlg()
{
    timer->stop();
    if(p03_dlg)
    {
        delete p03_dlg;
        p03_dlg = NULL;
    }
    p03_dlg = new  p03_historyquery_dialog;
    p03_dlg->setWindowFlags(Qt::FramelessWindowHint);
    connect(this,SIGNAL(signal_enable_p03dlg_timer()),p03_dlg,SLOT(init_page_dlg()));
    connect(p03_dlg,SIGNAL(signal_exit_p03dlg()),this,SLOT(start_timer()));
    emit signal_enable_p03dlg_timer();
    p03_dlg->exec();
}


void main_dialog::call_p01_dlg()
{
    timer->stop();
    if(p01_dlg)
    {
        delete p01_dlg;
        p01_dlg = NULL;
        handle_dlg_p01--;
    }
    p01_dlg = new  p01_passwd_dialog;
    p01_dlg->setWindowFlags(Qt::FramelessWindowHint);
    handle_dlg_p01++;

    connect(this,SIGNAL(signal_enable_p01dlg_timer()),p01_dlg,SLOT(init_page_dlg()));
    connect(p01_dlg,SIGNAL(signal_exit_p01dlg()),this,SLOT(start_timer()));

    emit signal_enable_p01dlg_timer();
    p01_dlg->exec();
}

void main_dialog::call_p05_dlg()
{
    timer->stop();
    if(p05_dlg)
    {
        delete p05_dlg;
        p05_dlg = NULL;
    }
    p05_dlg = new  p05_chargelink_dialog;
    p05_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p05dlg_timer()),p05_dlg,SLOT(init_page_dlg()));
    connect(p05_dlg,SIGNAL(signal_exit_p05dlg()),this,SLOT(start_timer()));

    emit signal_enable_p05dlg_timer();
    p05_dlg->exec();
}

void main_dialog::call_p07_dlg()
{
    timer->stop();
    if(p07_dlg)
    {
        delete p07_dlg;
        p07_dlg = NULL;
    }
    p07_dlg = new  p07_chargetypechoose_dialog;
    p07_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p07dlg_timer()),p07_dlg,SLOT(init_page_dlg()));
    connect(p07_dlg,SIGNAL(signal_exit_p07dlg()),this,SLOT(start_timer()));

    emit signal_enable_p07dlg_timer();
    p07_dlg->exec();
}

void main_dialog::call_p08_dlg()
{
    timer->stop();
    if(p08_dlg)
    {
        delete p08_dlg;
        p08_dlg = NULL;
    }
    p08_dlg = new  p08_chargebytime_dialog;
    p08_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p08dlg_timer()),p08_dlg,SLOT(init_page_dlg()));
    connect(p08_dlg,SIGNAL(signal_exit_p08dlg()),this,SLOT(start_timer()));
    emit signal_enable_p08dlg_timer();
    p08_dlg->exec();
}

void main_dialog::call_p09_dlg()
{
    timer->stop();
    if(p09_dlg)
    {
        delete p09_dlg;
        p09_dlg = NULL;
    }
    p09_dlg = new  p09_chargebyenergy_dialog;
    p09_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p09dlg_timer()),p09_dlg,SLOT(init_page_dlg()));
    connect(p09_dlg,SIGNAL(signal_exit_p09dlg()),this,SLOT(start_timer()));

    emit signal_enable_p09dlg_timer();
    p09_dlg->exec();
}


void main_dialog::call_p13_dlg()
{
    timer->stop();
    if(p13_dlg)
    {
        delete p13_dlg;
        p13_dlg = NULL;
        handle_dlg_p13--;
    }
    p13_dlg = new  p13_setpara_dialog;
    p13_dlg->setWindowFlags(Qt::FramelessWindowHint);
    handle_dlg_p13++;

    connect(this,SIGNAL(signal_enable_p13dlg_timer()),p13_dlg,SLOT(init_page_dlg()));
    connect(p13_dlg,SIGNAL(signal_exit_p13dlg()),this,SLOT(start_timer()));

    emit signal_enable_p13dlg_timer();
    p13_dlg->exec();
}

void main_dialog::call_p14_dlg()
{
    timer->stop();
    if(p14_dlg)
    {
        delete p14_dlg;
        p14_dlg = NULL;
    }
    p14_dlg = new  p14_setpara_sub1_dialog;
    p14_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p14dlg_timer()),p14_dlg,SLOT(init_page_dlg()));
    connect(p14_dlg,SIGNAL(signal_exit_p14dlg()),this,SLOT(start_timer()));
    emit signal_enable_p14dlg_timer();
    p14_dlg->exec();
}

void main_dialog::call_p15_dlg()
{
    timer->stop();
    if(p15_dlg)
    {
        delete p15_dlg;
        p15_dlg = NULL;
    }
    p15_dlg = new  p15_setpara_sub2_dialog;
    p15_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p15dlg_timer()),p15_dlg,SLOT(init_page_dlg()));
    connect(p15_dlg,SIGNAL(signal_exit_p15dlg()),this,SLOT(start_timer()));
    emit signal_enable_p15dlg_timer();
    p15_dlg->exec();
}

void main_dialog::call_p16_dlg()
{
    timer->stop();
    if(p16_dlg)
    {
        delete p16_dlg;
        p16_dlg = NULL;
    }
    p16_dlg = new  p16_setpara_sub3_dialog;
    p16_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p16dlg_timer()),p16_dlg,SLOT(init_page_dlg()));
    connect(p16_dlg,SIGNAL(signal_exit_p16dlg()),this,SLOT(start_timer()));
    emit signal_enable_p16dlg_timer();
    p16_dlg->exec();
}

void main_dialog::call_p17_dlg()
{
    timer->stop();
    if(p17_dlg)
    {
        delete p17_dlg;
        p17_dlg = NULL;
    }
    p17_dlg = new  p17_setpara_sub4_dialog;
    p17_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p17dlg_timer()),p17_dlg,SLOT(init_page_dlg()));
    connect(p17_dlg,SIGNAL(signal_exit_p17dlg()),this,SLOT(start_timer()));
    emit signal_enable_p17dlg_timer();
    p17_dlg->exec();
}

void main_dialog::call_p18_dlg()
{
    timer->stop();
    if(p18_dlg)
    {
        delete p18_dlg;
        p18_dlg = NULL;
    }
    p18_dlg = new  p18_setpara_sub5_dialog;
    p18_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p18dlg_timer()),p18_dlg,SLOT(init_page_dlg()));
    connect(p18_dlg,SIGNAL(signal_exit_p18dlg()),this,SLOT(start_timer()));
    emit signal_enable_p18dlg_timer();
    p18_dlg->exec();
}

void main_dialog::call_p19_dlg()
{
    timer->stop();
    if(p19_dlg)
    {
        delete p19_dlg;
        p19_dlg = NULL;
    }
    p19_dlg = new  p19_charging_dialog;
    p19_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p19dlg_timer()),p19_dlg,SLOT(init_page_dlg()));
    connect(p19_dlg,SIGNAL(signal_exit_p19dlg()),this,SLOT(start_timer()));
    emit signal_enable_p19dlg_timer();
    p19_dlg->exec();
}

void main_dialog::call_p20_dlg()
{
    timer->stop();
    if(p20_dlg)
    {
        delete p20_dlg;
        p20_dlg = NULL;
    }
    p20_dlg = new  p20_payoff_dialog;
    p20_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p20dlg_timer()),p20_dlg,SLOT(init_page_dlg()));
    connect(p20_dlg,SIGNAL(signal_exit_p20dlg()),this,SLOT(start_timer()));
    emit signal_enable_p20dlg_timer();
    p20_dlg->exec();
}

void main_dialog::call_p21_dlg()
{
    timer->stop();
    if(p21_dlg)
    {
        delete p21_dlg;
        p21_dlg = NULL;
    }
    p21_dlg = new  p21_judge_continue;
    p21_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p21dlg_timer()),p21_dlg,SLOT(init_page_dlg()));
    connect(p21_dlg,SIGNAL(signal_exit_p21dlg()),this,SLOT(start_timer()));
    emit signal_enable_p21dlg_timer();
    p21_dlg->exec();
}

void main_dialog::call_p24_dlg()
{
    timer->stop();
    if(p24_dlg)
    {
        delete p24_dlg;
        p24_dlg = NULL;
    }
    p24_dlg = new  p24_setpara_sub6_dialog;
    p24_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p24dlg_timer()),p24_dlg,SLOT(init_page_dlg()));
    connect(p24_dlg,SIGNAL(signal_exit_p24dlg()),this,SLOT(start_timer()));
    emit signal_enable_p24dlg_timer();
    p24_dlg->exec();
}

void main_dialog::on_pbtn_setpara_clicked()
{
    hmi_button_dn_num=SET_PARA_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

void main_dialog::on_pbtn_language_clicked()
{
    if(1 == language_num)
    {
        language_num = 2;
        return;
    }

    if(2 == language_num)
    {
        language_num = 1;
        return;
    }
}

void main_dialog::on_pbtn_test_1_clicked()
{
    hmi_page_index =  PAGEINDEX_LOCAL_ERR;
    API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
}

void main_dialog::on_pbtn_test_2_clicked()
{
    hmi_page_index =  PAGEINDEX_REMOTE_ERR;
    API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
}

