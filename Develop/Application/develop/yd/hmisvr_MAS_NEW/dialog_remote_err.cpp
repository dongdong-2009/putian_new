#include "dialog_remote_err.h"
#include "ui_dialog_remote_err.h"
#include "globalhmi.h"

dialog_remote_err::dialog_remote_err(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_remote_err)
{
    ui->setupUi(this);
    //printf("*********** it is dialog_remote_err ***********\n");
}

dialog_remote_err::~dialog_remote_err()
{
    delete ui;
}

int remote_errsum = 0;

int remote_errsum_flag,remote_errsum_flag_2,remote_errsum_flag_3;
int remote_errsum_temp,remote_errsum_temp_2,remote_errsum_temp_3;

int remote_pagenum_all=0;
int remote_page_number=0;
int remote_pagenum_temp=0;

char remote_tempsub2_buf[30][50]={0};
int remote_tempadd_sub2 = 0;

char remote_temperr_array[50] = {0};

#define  REMOTE_ERR_FILE  "/usr/data/warning.txt"
struct  _partbuf_0x97 remote_array_errfile[500]={0};

int Err_remotefile_analysis(const char *file_name, struct _partbuf_0x97  *partbuf_0x97_OutPt);
//int Err_remote_analysis(int error_state_flag);
//int Err_local_analysis(int error_state_flag,int err_type_index);

int Err_remote_analysis(int error_state_flag,int err_type_index);

void dialog_remote_err::changeEvent(QEvent *e)
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

void dialog_remote_err::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void dialog_remote_err::init_page_val()
{
    printf("*********** start to  init_page_val ************\n");
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));

    ui->frame_2->move(36,800);

    llbl_num=1;
    llbl_num_2=2;
    llbl_num_3=3;
    llbl_num_4=4;
    llbl_num_5=5;

    /*
        故障序号: 发生的序号
    */
    remote_errsum = Err_remotefile_analysis(REMOTE_ERR_FILE,remote_array_errfile);

    if(remote_errsum > 0)
    {

        if(remote_errsum >= 3)
        {
             lbl_num  =remote_errsum ;    //71
             lbl_num_2=remote_errsum - 1; //70
             lbl_num_3=remote_errsum - 2; //69
        }else if(remote_errsum == 2)
        {
             lbl_num  =remote_errsum ;
             lbl_num_2=remote_errsum - 1;
        }
        else if(remote_errsum == 1)
        {
             lbl_num  =remote_errsum ;
        }else{

        }

        //总页数
        remote_pagenum_all = remote_errsum/3;    //7条 ， 3页
        remote_pagenum_temp = remote_errsum%3;
        if(remote_pagenum_temp > 0)
        {
            remote_pagenum_all++;
        }
        //当前页数
        remote_page_number = (remote_errsum/3 + 1) - (lbl_num/3); //3 - 2
        ui->label_pagenum->setNum(remote_page_number);
        ui->label_pagenum_all->setNum(remote_pagenum_all);

        memcpy(&time,&remote_array_errfile[remote_errsum - lbl_num].OccurTm,sizeof(SYNCHRO_TIME_S));
        memcpy(&time_2,&remote_array_errfile[remote_errsum - lbl_num_2].OccurTm,sizeof(SYNCHRO_TIME_S));
        memcpy(&time_3,&remote_array_errfile[remote_errsum - lbl_num_3].OccurTm,sizeof(SYNCHRO_TIME_S));

        err_code = remote_array_errfile[remote_errsum - lbl_num].errcode;
        err_code_2 = remote_array_errfile[remote_errsum - lbl_num_2].errcode;
        err_code_3 = remote_array_errfile[remote_errsum - lbl_num_3].errcode;

        errtype_num_1 = remote_array_errfile[remote_errsum - lbl_num].err_protcl_type;
        errtype_num_2 = remote_array_errfile[remote_errsum - lbl_num_2].err_protcl_type;
        errtype_num_3 = remote_array_errfile[remote_errsum - lbl_num_3].err_protcl_type;

        memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
        remote_tempadd_sub2 = 0;
        Err_remote_analysis(err_code,errtype_num_1);
        memcpy(lbl_txt, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num]));
        ui->label_txt_6->setText(QString::fromUtf8(lbl_txt));

        memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
        remote_tempadd_sub2 = 0;
        Err_remote_analysis(err_code_2,errtype_num_2);
        memcpy(lbl_txt_2,&remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num_2]));
        ui->label_txt_7->setText(QString::fromUtf8(lbl_txt_2));

        memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
        remote_tempadd_sub2 = 0;
        Err_remote_analysis(err_code_3,errtype_num_3);
        memcpy(lbl_txt_3, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num_3]));
        ui->label_txt_8->setText(QString::fromUtf8(lbl_txt_3));

    }
    else
    {

    }
}

void dialog_remote_err::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void dialog_remote_err::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}

void dialog_remote_err::update_page_info()
{
    if(remote_errsum > 0)
    {
        if(err_code&&(lbl_num > 0))
        {
            ui->frame_5->move(20,65);

            ui->label_num->setNum(lbl_num);
            ui->label_txt->setText(itos(time));
            ui->pbtn_more_1->move(640,60);

        }
        else
        {
             ui->label_num->setText(NULL);
             ui->label_txt->setText(NULL);
             ui->pbtn_more_1->move(0,800);

             ui->frame_5->move(0,800);
        }


        if(err_code_2&&(lbl_num_2 > 0))
        {
            ui->frame_6->move(20,170);

            ui->label_num_2->setNum(lbl_num_2);
            ui->label_txt_2->setText(itos(time_2));
            ui->pbtn_more_2->move(640,60);
        }
        else
        {
             ui->label_num_2->setText(NULL);
             ui->label_txt_2->setText(NULL);
             ui->pbtn_more_2->move(0,800);

             ui->frame_6->move(0,800);
        }


        if(err_code_3&&(lbl_num_3 > 0))
        {
            ui->frame_7->move(20,275);

            ui->label_num_3->setNum(lbl_num_3);
            ui->label_txt_3->setText(itos(time_3));
            ui->pbtn_more_3->move(640,60);
        }
        else
        {
             ui->label_num_3->setText(NULL);
             ui->label_txt_3->setText(NULL);
             ui->pbtn_more_3->move(0,800);

             ui->frame_7->move(0,800);
        }

    }
    else
    {
        ui->label_tip->move(200,200);
    }


        if(remote_errsum > 0)
        {
 #if 0
            // remote_tempsub2_buf : 存储50列，30个故障，故为: [30][50]
            // 这里只需要显示一个时间上的一个故障，就显示: remote_tempsub2_buf[0]即可；
            memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
            remote_tempadd_sub2 = 0;
            Err_remote_analysis(err_code);
            memcpy(lbl_txt, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num]));
            ui->label_txt_6->setText(QString::fromUtf8(lbl_txt));

            memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
            remote_tempadd_sub2 = 0;
            Err_remote_analysis(err_code_2);
            memcpy(lbl_txt_2,&remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num_2]));
            ui->label_txt_7->setText(QString::fromUtf8(lbl_txt_2));

            memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
            remote_tempadd_sub2 = 0;
            Err_remote_analysis(err_code_3);
            memcpy(lbl_txt_3, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num_3]));
            ui->label_txt_8->setText(QString::fromUtf8(lbl_txt_3));
#endif
            memcpy(lbl_txt_11, &remote_tempsub2_buf[llbl_num-1],sizeof(remote_tempsub2_buf[llbl_num-1]));
            memcpy(lbl_txt_12,& remote_tempsub2_buf[llbl_num_2-1],sizeof(remote_tempsub2_buf[llbl_num_2-1]));
            memcpy(lbl_txt_13, &remote_tempsub2_buf[llbl_num_3-1],sizeof(remote_tempsub2_buf[llbl_num_3-1]));
            memcpy(lbl_txt_14, &remote_tempsub2_buf[llbl_num_4-1],sizeof(remote_tempsub2_buf[llbl_num_4-1]));
            memcpy(lbl_txt_15, &remote_tempsub2_buf[llbl_num_5-1],sizeof(remote_tempsub2_buf[llbl_num_5-1]));

            ui->label_txt_11->setText(QString::fromUtf8(lbl_txt_11));
            ui->label_txt_12->setText(QString::fromUtf8(lbl_txt_12));
            ui->label_txt_13->setText(QString::fromUtf8(lbl_txt_13));
            ui->label_txt_14->setText(QString::fromUtf8(lbl_txt_14));
            ui->label_txt_15->setText(QString::fromUtf8(lbl_txt_15));

            if(lbl_txt_11[0])
            {
                ui->label_num_11->setNum(llbl_num);
            }
            else
            {
                ui->label_num_11->setText(NULL);
            }

            if(lbl_txt_12[0])
            {
                ui->label_num_12->setNum(llbl_num_2);
            }
            else
            {
                ui->label_num_12->setText(NULL);
            }

            if(lbl_txt_13[0])
            {
                 ui->label_num_13->setNum(llbl_num_3);
            }
            else
            {
                ui->label_num_13->setText(NULL);
            }

            if(lbl_txt_14[0])
            {
                ui->label_num_14->setNum(llbl_num_4);
            }
            else
            {
                ui->label_num_14->setText(NULL);
            }

            if(lbl_txt_15[0])
            {
                ui->label_num_15->setNum(llbl_num_5);
            }
            else
            {
                ui->label_num_15->setText(NULL);
            }
        }
        else
        {

        }

}

void dialog_remote_err::update_hmi_page_index(void)
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
   if(hmi_page_index != PAGEINDEX_REMOTE_ERR)
   {
       exit_page_dlg();
   }
   else
   {

   }
}

void dialog_remote_err::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_dlg();
    //delete end_dlg;
    //end_dlg = NULL;
}

//首页
void dialog_remote_err::on_pbtn_first_page_clicked()
{

    /*
        故障序号: 发生的序号
    */
    remote_errsum = Err_remotefile_analysis(REMOTE_ERR_FILE,remote_array_errfile);
    if(remote_errsum > 0)
    {
        if(remote_errsum >= 3)
        {
             lbl_num  =remote_errsum ;    //71
             lbl_num_2=remote_errsum - 1; //70
             lbl_num_3=remote_errsum - 2; //69
        }else if(remote_errsum == 2)
        {
             lbl_num  =remote_errsum ;
             lbl_num_2=remote_errsum - 1;
        }
        else if(remote_errsum == 1)
        {
             lbl_num  =remote_errsum ;
        }else{

        }

        memcpy(&time,&remote_array_errfile[remote_errsum - lbl_num].OccurTm,sizeof(SYNCHRO_TIME_S));
        memcpy(&time_2,&remote_array_errfile[remote_errsum - lbl_num_2].OccurTm,sizeof(SYNCHRO_TIME_S));
        memcpy(&time_3,&remote_array_errfile[remote_errsum - lbl_num_3].OccurTm,sizeof(SYNCHRO_TIME_S));

        err_code = remote_array_errfile[remote_errsum - lbl_num].errcode;
        err_code_2 = remote_array_errfile[remote_errsum - lbl_num_2].errcode;
        err_code_3 = remote_array_errfile[remote_errsum - lbl_num_3].errcode;

        errtype_num_1 = remote_array_errfile[remote_errsum - lbl_num].err_protcl_type;
        errtype_num_2 = remote_array_errfile[remote_errsum - lbl_num_2].err_protcl_type;
        errtype_num_3 = remote_array_errfile[remote_errsum - lbl_num_3].err_protcl_type;

        memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
        remote_tempadd_sub2 = 0;
        Err_remote_analysis(err_code,errtype_num_1);
        memcpy(lbl_txt, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num]));
        ui->label_txt_6->setText(QString::fromUtf8(lbl_txt));

        memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
        remote_tempadd_sub2 = 0;
        Err_remote_analysis(err_code_2,errtype_num_2);
        memcpy(lbl_txt_2,&remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num_2]));
        ui->label_txt_7->setText(QString::fromUtf8(lbl_txt_2));

        memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
        remote_tempadd_sub2 = 0;
        Err_remote_analysis(err_code_3,errtype_num_3);
        memcpy(lbl_txt_3, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num_3]));
        ui->label_txt_8->setText(QString::fromUtf8(lbl_txt_3));

        //总页数
        remote_pagenum_all = remote_errsum/3;    //7条 ， 3页
        remote_pagenum_temp = remote_errsum%3;
        if(remote_pagenum_temp > 0)
        {
            remote_pagenum_all++;
        }
        //当前页数
        remote_page_number = (remote_errsum/3 + 1) - (lbl_num/3); //3 - 2
        ui->label_pagenum->setNum(remote_page_number);
        ui->label_pagenum_all->setNum(remote_pagenum_all);


    }
    else
    {

    }

    hmi_button_dn_num=FIRST_PAGE_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

}

//上一页
void dialog_remote_err::on_pbtn_up_clicked()
{
    ui->frame_5->move(20,65);
    ui->frame_6->move(20,170);
    ui->frame_7->move(20,275);

    hmi_button_dn_num=PAGEUP_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

    if(remote_errsum > 0)
    {

        if(remote_errsum - lbl_num >= 3)
        {
            lbl_num=lbl_num+3;
            lbl_num_2=lbl_num_2+3;
            lbl_num_3=lbl_num_3+3;

            memcpy(&time,&remote_array_errfile[remote_errsum - lbl_num].OccurTm,sizeof(SYNCHRO_TIME_S));
            memcpy(&time_2,&remote_array_errfile[remote_errsum - lbl_num_2].OccurTm,sizeof(SYNCHRO_TIME_S));
            memcpy(&time_3,&remote_array_errfile[remote_errsum - lbl_num_3].OccurTm,sizeof(SYNCHRO_TIME_S));

            err_code = remote_array_errfile[remote_errsum - lbl_num].errcode;
            err_code_2 = remote_array_errfile[remote_errsum - lbl_num_2].errcode;
            err_code_3 = remote_array_errfile[remote_errsum - lbl_num_3].errcode;

            errtype_num_1 = remote_array_errfile[remote_errsum - lbl_num].err_protcl_type;
            errtype_num_2 = remote_array_errfile[remote_errsum - lbl_num_2].err_protcl_type;
            errtype_num_3 = remote_array_errfile[remote_errsum - lbl_num_3].err_protcl_type;

            memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
            remote_tempadd_sub2 = 0;
            Err_remote_analysis(err_code,errtype_num_1);
            memcpy(lbl_txt, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[llbl_num-1]));
            ui->label_txt_6->setText(QString::fromUtf8(lbl_txt));

            memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
            remote_tempadd_sub2 = 0;
            Err_remote_analysis(err_code_2,errtype_num_2);
            memcpy(lbl_txt_2,& remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[llbl_num_2-1]));
            ui->label_txt_7->setText(QString::fromUtf8(lbl_txt_2));

            memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
            remote_tempadd_sub2 = 0;
            Err_remote_analysis(err_code_3,errtype_num_3);
            memcpy(lbl_txt_3, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[llbl_num_3-1]));
            ui->label_txt_8->setText(QString::fromUtf8(lbl_txt_3));
        }
        else
        {
        }

       //总页数
        remote_pagenum_all = remote_errsum/3;    //7条 ， 3页
        remote_pagenum_temp = remote_errsum%3;
        if(remote_pagenum_temp > 0)
        {
            remote_pagenum_all++;
        }
        //当前页数
        remote_page_number = (remote_errsum/3 + 1) - (lbl_num/3); //3 - 2
        ui->label_pagenum->setNum(remote_page_number);
        ui->label_pagenum_all->setNum(remote_pagenum_all);
    }
    else
    {
    }

}

//下一页
void dialog_remote_err::on_pbtn_down_clicked()
{
    hmi_button_dn_num=PAGEDOWN_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

    if(remote_errsum > 0)
    {
        if(lbl_num > 3)
        {
            if(lbl_num - 3 > 0)
            {
                lbl_num  =lbl_num - 3 ;
            }else if(lbl_num > 0)
            {
                remote_errsum_flag = 1;
                remote_errsum_temp = lbl_num - 3;
                lbl_num =remote_errsum + 1;

            }else{
            }

            if(lbl_num_2 - 3 > 0)
            {
                lbl_num_2  =lbl_num_2 - 3 ;
            }else if(lbl_num_2 > 0)
            {
                remote_errsum_flag_2 = 1;
                remote_errsum_temp_2= lbl_num_2 - 3;
                lbl_num_2  =remote_errsum + 1;

            }else{
            }

            if(lbl_num_3 - 3 > 0)
            {
                lbl_num_3  =lbl_num_3 - 3 ;
            }else if(lbl_num_3 > 0)
            {
                remote_errsum_flag_3 = 1;
                remote_errsum_temp_3= lbl_num_3 - 3;
                lbl_num_3  =remote_errsum + 1;

            }else{
        }


        //printf("********* 1 remote_errsum = %d*******\n",remote_errsum);

        memcpy(&time,&remote_array_errfile[remote_errsum - lbl_num].OccurTm,sizeof(SYNCHRO_TIME_S));
        memcpy(&time_2,&remote_array_errfile[remote_errsum - lbl_num_2].OccurTm,sizeof(SYNCHRO_TIME_S));
        memcpy(&time_3,&remote_array_errfile[remote_errsum - lbl_num_3].OccurTm,sizeof(SYNCHRO_TIME_S));

        err_code = remote_array_errfile[remote_errsum - lbl_num].errcode;
        err_code_2 = remote_array_errfile[remote_errsum - lbl_num_2].errcode;
        err_code_3 = remote_array_errfile[remote_errsum - lbl_num_3].errcode;

        errtype_num_1 = remote_array_errfile[remote_errsum - lbl_num].err_protcl_type;
        errtype_num_2 = remote_array_errfile[remote_errsum - lbl_num_2].err_protcl_type;
        errtype_num_3 = remote_array_errfile[remote_errsum - lbl_num_3].err_protcl_type;

        //printf("********* 1 err_code = %d*******\n",err_code);

        memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
        remote_tempadd_sub2 = 0;
        Err_remote_analysis(err_code,errtype_num_1);
        memcpy(lbl_txt, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[llbl_num-1]));
        ui->label_txt_6->setText(QString::fromUtf8(lbl_txt));

        memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
        remote_tempadd_sub2 = 0;
        Err_remote_analysis(err_code_2,errtype_num_2);
        memcpy(lbl_txt_2,& remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[llbl_num_2-1]));
        ui->label_txt_7->setText(QString::fromUtf8(lbl_txt_2));

        memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
        remote_tempadd_sub2 = 0;
        Err_remote_analysis(err_code_3,errtype_num_3);
        memcpy(lbl_txt_3, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[llbl_num_3-1]));
        ui->label_txt_8->setText(QString::fromUtf8(lbl_txt_3));

        if(remote_errsum_flag == 1)
        {
            lbl_num = remote_errsum_temp;
            remote_errsum_temp = 0;
            remote_errsum_flag = 0;
        }

        if(remote_errsum_flag_2 == 1)
        {
            lbl_num_2 = remote_errsum_temp_2;
            remote_errsum_temp_2 = 0;
            remote_errsum_flag_2 = 0;
        }
        if(remote_errsum_flag_3 == 1)
        {
            lbl_num_3 = remote_errsum_temp_3;
            remote_errsum_temp_3 = 0;
            remote_errsum_flag_3 = 0;
        }

        }
        else
        {
        }

        //总页数
        remote_pagenum_all = remote_errsum/3;    //7条 ， 3页
        remote_pagenum_temp = remote_errsum%3;
        if(remote_pagenum_temp > 0)
        {
            remote_pagenum_all++;
        }
        //当前页数
        remote_page_number = (remote_errsum/3 + 1) - (lbl_num/3); //3 - 2
        ui->label_pagenum->setNum(remote_page_number);
        ui->label_pagenum_all->setNum(remote_pagenum_all);


    }
    else
    {

    }


}

void dialog_remote_err::on_pbtn_back_clicked()
{
    hmi_button_dn_num=CANCEL_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));

    //hmi_page_index=PAGEINDEX_ERR_CHOOSE;
    //API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

}

void dialog_remote_err::on_pbtn_more_1_clicked()
{
    memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
    remote_tempadd_sub2 = 0;
    Err_remote_analysis(err_code,errtype_num_1);
    ui->frame_2->move(0,0);

    ui->frame_5->move(0,800);
    ui->frame_6->move(0,800);
    ui->frame_7->move(0,800);
}
void dialog_remote_err::on_pbtn_more_2_clicked()
{
    memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
    remote_tempadd_sub2 = 0;
    Err_remote_analysis(err_code_2,errtype_num_2);
    ui->frame_2->move(0,0);

    ui->frame_5->move(0,800);
    ui->frame_6->move(0,800);
    ui->frame_7->move(0,800);
}
void dialog_remote_err::on_pbtn_more_3_clicked()
{
    memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
    remote_tempadd_sub2 = 0;
    Err_remote_analysis(err_code_3,errtype_num_3);
    ui->frame_2->move(0,0);

    ui->frame_5->move(0,800);
    ui->frame_6->move(0,800);
    ui->frame_7->move(0,800);
}
void dialog_remote_err::on_pbtn_back_2_clicked()
{

    memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
    remote_tempadd_sub2 = 0;
    Err_remote_analysis(err_code,errtype_num_1);
    memcpy(lbl_txt, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num]));
    ui->label_txt_6->setText(QString::fromUtf8(lbl_txt));

    memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
    remote_tempadd_sub2 = 0;
    Err_remote_analysis(err_code_2,errtype_num_2);
    memcpy(lbl_txt_2,&remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num_2]));
    ui->label_txt_7->setText(QString::fromUtf8(lbl_txt_2));

    memset(remote_tempsub2_buf,0,sizeof(remote_tempsub2_buf));
    remote_tempadd_sub2 = 0;
    Err_remote_analysis(err_code_3,errtype_num_3);
    memcpy(lbl_txt_3, &remote_tempsub2_buf[0],sizeof(remote_tempsub2_buf[remote_errsum - lbl_num_3]));
    ui->label_txt_8->setText(QString::fromUtf8(lbl_txt_3));

    ui->frame_2->move(36,800);

    ui->frame_5->move(20,65);
    ui->frame_6->move(20,170);
    ui->frame_7->move(20,275);

}

int Err_remotefile_analysis(const char *file_name, struct _partbuf_0x97  *partbuf_0x97_OutPt)
{
    int num_add = 0;
    unsigned char linedatabuf[100] ;
    FILE *fp_file;
    unsigned  int startpos=0;
    //one line total len
    unsigned  int  readLen=0;

    //singal for each split
    unsigned  int Sectionindex=0;
    //store the char for each split
    unsigned char SectionBuf[50];
    //pos for each split
    unsigned  int  SectiondataPos=0;

    //flag for getting the start index of history
    unsigned  int  startInsertFlag=0;
       //insert history count
    unsigned  int  TempInsertCount=0;
    struct _partbuf_0x97 tempWaring ;
    int tempeventtype=0;
    int linetotal=0;
    fp_file = fopen(file_name, "r");
    if(fp_file ==0)//open file error
    {
        perror("open warning.txt: ");
        return 0;
    }
    else
    {
        printf("open warningfile success\r\n");
    }
    if(partbuf_0x97_OutPt==NULL)
    {
        fclose(fp_file);
        return 0;
    }
    memset(linedatabuf,0,100);
    TempInsertCount=0;
      //  while (fgets((char *)linedatabuf, sizeof(linedatabuf), fp_file))
    while (!feof(fp_file))
    {
        fgets((char *)linedatabuf, sizeof(linedatabuf), fp_file);
        if(feof(fp_file))
        {
                     //at the end of file ,stopping get historyrecord
               startInsertFlag=0;
            break;
        }

        readLen=strlen((char *)linedatabuf);
        if(readLen<=3)
        {
            continue;
        }


        //please tar the string buf for your struct
        //tile of the text
        //printf("####read linenumber=%d,%s\r\n",linetotal,linedatabuf);
        if( linedatabuf[startpos]=='i'&& linedatabuf[startpos+1]=='d'&&linedatabuf[startpos+2]=='x')
        {
            continue;
        }
        if( linedatabuf[startpos]=='#'&& linedatabuf[startpos+1]=='#'&&linedatabuf[startpos+2]=='#')
        {
            continue;
        }
           linetotal++;

        memset(SectionBuf,0,50);
        Sectionindex=0;
        SectiondataPos=0;
        for(startpos=0;startpos<readLen;startpos++)
        {

            if(linedatabuf[startpos]==0x0d||linedatabuf[startpos]==0x0a)
            {
                //break;
                continue;
            }
            if(linedatabuf[startpos]==0x7c)//"|"
            {
                     // printf("1111111111111\r\n");
                if(Sectionindex==0)//record index
                {
                    tempeventtype=atoi((char *)SectionBuf);
                    if(tempeventtype== 1)//find the startindex wo need
                    {
                      // tempWaring.index=linetotal;
                        //add by mj_1_29
                        num_add++;
                        tempWaring.index=num_add;
                       //tempWaring.type_inquire=tempeventtype;
                       startInsertFlag=1;

                       tempWaring.err_protcl_type = 1;
                    }
                    else if(tempeventtype == 2)                              //
                    {
                        // tempWaring.index=linetotal;
                        //add by mj_1_29
                        num_add++;
                        tempWaring.index=num_add;
                        //tempWaring.type_inquire=tempeventtype;
                        startInsertFlag=1;

                        tempWaring.err_protcl_type = 2;
                    }
                    else
                    {
                        startInsertFlag=0;
                        continue;
                    }

                // printf("%d\r\n",tempHistoryRecord.RecordIndex);
                }//end of if(Sectionindex==0)//record index
                else if(Sectionindex==1)//record index
                {
                    tempWaring.modnum=atoi((char *)SectionBuf);
                }//end of if(Sectionindex==0)//record index
                else if(Sectionindex==2)//record index
                {
                    //tempWaring.errcode=atoi((char *)SectionBuf);
                    strcat((char *)SectionBuf,"-");
                    TimeAnanisis(&tempWaring.OccurTm,SectionBuf);

                }//end of if(Sectionindex==0)//record index
                else if(Sectionindex==3)//errcode
                {
                       tempWaring.errcode=atoi((char *)SectionBuf);
                }

                memset(SectionBuf,0,50);
                SectiondataPos=0;
                Sectionindex++;
                continue;
            }//end of if(linedatabuf[startpos]==0x7c)//"|"
            else
            {
                if(SectiondataPos<50)
                {
                      SectionBuf[SectiondataPos++]=linedatabuf[startpos];
                }
            }

       }//end of for(startpos=0;startpos<readLen;startpos++)

        Sectionindex=0;
        // printf("\r\n");
        memset(linedatabuf,0,100);
        if(startInsertFlag==1&&TempInsertCount<500)//start insert history
        {
            memcpy(&partbuf_0x97_OutPt[TempInsertCount],&tempWaring,sizeof(struct _partbuf_0x97));
            //partbuf_0x96_OutPt[TempEventInsertCount].RecordIndex=linetotal;
            TempInsertCount++;
        }//end of  if(startInsertFlag==1)//start insert history
        memset(&tempWaring,0,sizeof(struct _partbuf_0x97));

    }//end of  while (fgets(linedatabuf, sizeof(linedatabuf), fp_file))

    fclose(fp_file);
    return TempInsertCount;
}

// 8388608  -> 网络故障: 80 0000
//remote_tempsub2_buf: 用来存储一条记录中可能出现的多条故障

int   Err_remote_analysis(int error_state_flag,int err_type_index)
{
    if(language_num == 1)
    {
        remote_tempadd_sub2 = 0;
        if( (error_state_flag & (1<<0)) )     //
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"读卡器通信故障",sizeof("读卡器通信故障"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"绝缘电阻值小于阀值",sizeof("绝缘电阻值小于阀值"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<1)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"读卡器与主控板通信超时",sizeof("读卡器与主控板通信超时"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"绝缘模块故障",sizeof("绝缘模块故障"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<2)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"显示屏硬件损坏",sizeof("显示屏硬件损坏"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"进风口温度过高",sizeof("进风口温度过高"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<3)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"显示屏与主控板通信超时",sizeof("显示屏与主控板通信超时"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"输 入 过 压",sizeof("输 入 过 压"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<4)))
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"交流接触器状态监测故障",sizeof("交流接触器状态监测故障"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"输 入 欠 压",sizeof("输 入 欠 压"));
            }
            else
            {
            }
        }

        if((error_state_flag & (1<<5)))
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"交流接触器供电故障",sizeof("交流接触器供电故障"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"输 入 缺 相",sizeof("输 入 缺 相"));
            }
            else
            {
            }
        }

        if((error_state_flag & (1<<6)))
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"低压电源异常",sizeof("低压电源异常"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"输 入 过 流",sizeof("输 入 过 流"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<7)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"主控板硬件故障",sizeof("主控板硬件故障"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"谐波超限（预留）",sizeof("谐波超限（预留）"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<8)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"主板软件故障",sizeof("主板软件故障"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"输 出 过 压",sizeof("输 出 过 压"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<9)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"控制板与模块通讯不稳定",sizeof("控制板与模块通讯不稳定"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"输 出 欠 压",sizeof("输 出 欠 压"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<10)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"模块通讯接收端故障",sizeof("模块通讯接收端故障"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"输 出 过 流",sizeof("输 出 过 流"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<11)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"数据传输丢包-1级",sizeof("数据传输丢包-1级"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"输 出 短 路",sizeof("输 出 短 路"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<12)) )
        {
            if(err_type_index == 1)
            {

            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"充电模块无输出电压、电流",sizeof("充电模块无输出电压、电流"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<13)) )
        {
            if(err_type_index == 1)
            {
            }
            else if(err_type_index == 2)
            {
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<14)) )
        {
            if(err_type_index == 1)
            {
            }
            else if(err_type_index == 2)
            {
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<15)) )
        {
            if(err_type_index == 1)
            {
            }
            else if(err_type_index == 2)
            {
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<16)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"键盘硬件损坏",sizeof("键盘硬件损坏"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"出风口温度过高",sizeof("出风口温度过高"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<17)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"键盘与主控板通信故障",sizeof("键盘与主控板通信故障"));
            }
            else if(err_type_index == 2)
            {
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<18)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"电磁锁故障",sizeof("电磁锁故障"));
            }
            else if(err_type_index == 2)
            {

            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<19)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"电表硬件故障",sizeof("电表硬件故障"));
            }
            else if(err_type_index == 2)
            {

            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<20)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"电表与主控板通信故障",sizeof("电表与主控板通信故障"));
            }
            else if(err_type_index == 2)
            {
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<21)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"急停按钮被按下,请恢复",sizeof("急停按钮被按下,请恢复"));
            }
            else if(err_type_index == 2)
            {

            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<22)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"数据传输丢包-2级",sizeof("数据传输丢包-2级"));
            }
            else if(err_type_index == 2)
            {

            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<23)) )
        {

            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"网 络 连 接 故 障",sizeof("网 络 连 接 故 障"));
            }
            else if(err_type_index == 2)
            {

            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<24)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"读卡器通信故障",sizeof("读卡器通信故障"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"风 扇 故 障",sizeof("风 扇 故 障"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<25)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"读卡器与主控板通信超时故障",sizeof("读卡器与主控板通信超时故障"));
            }
            else if(err_type_index == 2)
            {
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<26)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"打印机硬件损坏",sizeof("打印机硬件损坏"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"存储器读取数据失败",sizeof("存储器读取数据失败"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<27)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"打印机与主控板通信故障",sizeof("打印机与主控板通信故障"));
            }
            else if(err_type_index == 2)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"存储器已满",sizeof("存储器已满"));
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<28)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"打印机缺纸状态（新增）",sizeof("打印机缺纸状态（新增）"));
            }
            else if(err_type_index == 2)
            {
            }
            else
            {
            }
        }

        if( (error_state_flag & (1<<29)) )
        {
            if(err_type_index == 1)
            {
                memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"数据传输丢包-3级",sizeof("数据传输丢包-3级"));
            }
            else if(err_type_index == 2)
            {
            }
            else
            {
            }
        }

    }
    else  if(language_num == 2)
    {

        remote_tempadd_sub2 = 0;
        if( (error_state_flag & (1<<0)) || (error_state_flag &(1<<24)) || (error_state_flag & (1<<1))  || (error_state_flag & (1<<25)) )
        {
            memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"card reader error",sizeof("card reader error"));
        }
        if( (error_state_flag & (1<<20)) )
        {
            memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"meter error",sizeof("meter error"));
        }
        if( (error_state_flag & (1<<8)) )
        {
            memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"software in board error",sizeof("software in board error"));
        }
        if( (error_state_flag & (1<<21)) )
        {
            memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"emergency is pressed,please recover it",sizeof("emergency is pressed,please recover it"));
        }
        if( (error_state_flag & (1<<7)) )
        {
            memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"hardware in board error",sizeof("hardware in board error"));
        }
        if( (error_state_flag & (1<<4)) ||(error_state_flag & (1<<5)))
        {
            memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"ac contactor error",sizeof("ac contactor error"));
        }
        if( (error_state_flag & (1<<23)) )
        {
            memcpy(&remote_tempsub2_buf[remote_tempadd_sub2++],"net link error",sizeof("net link error"));
        }
    }
    else
    {

    }
    return remote_tempadd_sub2;
}


char* dialog_remote_err::itos(struct SYNCHRO_TIME  time)
{
    memset(remote_temperr_array,0,sizeof(remote_temperr_array));
    snprintf(remote_temperr_array,50,"%4d-%02d-%02d %02d:%02d:%02d",time.uwYear,time.ucMonth,time.ucDay,time.ucHour,time.ucMinute,time.ucSecond);
    char *temp = remote_temperr_array;
    return temp;
}

