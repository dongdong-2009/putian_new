#include "dialog_book.h"
#include "ui_dialog_book.h"
#include "globalhmi.h"
#include<QDateTime>

Dialog_book::Dialog_book(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_book)
{
    ui->setupUi(this);
}

Dialog_book::~Dialog_book()
{
    delete ui;
}

void Dialog_book::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

int down_time = 0;
int start_time = 0;
void Dialog_book::init_page_val()
{
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
     ui->label_piccode->setPixmap(QPixmap("/usr/APP/1.png"));
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));

    //API_Read_DB_Nbyte(PL_BOOKDOWN_TIME,(int *)(&down_time),sizeof(down_time));

}

void Dialog_book::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
}

void Dialog_book::timer_handle()
{
    update_page_info();
    update_hmi_page_index();
}
//
static int err_add = 0;
INT8 book_card_sn[17]={0};
INT8 guestname[20]={0};
static INT8 tempguest[32]={0};

void Dialog_book::update_page_info()
{
//    ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
//    ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));

   // API_Read_DB_Nbyte(PL_BOOKCARD_SN,(INT8 *)(&book_card_sn),sizeof(book_card_sn));
   // ui->label_card_sn->setText(book_card_sn);


    API_Read_DB_Nbyte(PL_BOOKSTART_TIME,(int *)(&start_time),sizeof(start_time));
    API_Read_DB_Nbyte(PL_BOOKDOWN_TIME,(int *)(&down_time),sizeof(down_time));
     API_Read_DB_Nbyte(PL_GUEST_NAME,(char *)(&guestname),sizeof(guestname));

    //printf("*************** guestname = %s\n",guestname);

     //snprintf(tempguest,sizeof(tempguest)," %s ",guestname);
     //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

    QTextCodec *codec=QTextCodec::codecForName("GB2312");

    QString str=codec->toUnicode(guestname,strlen(guestname));

    ui->label_book_sn->setText(str);

    //ui->label_book_sn->setText(QString::fromUtf8(guestname));

    //printf("!!!!!!!!!!!!!!!!!!!! %d %d\n",down_time,start_time);
    ui->label_down->setText(QDateTime::fromTime_t(start_time).toString("hh:mm"));
    ui->label_start->setText(QDateTime::fromTime_t(down_time).toString("hh:mm"));


    int carderr = 0;

        API_Read_DB_Nbyte(PL_BOOKCARD_ERR,(int *)(&carderr),sizeof(carderr));

        if(carderr)
        {
            ui->label_card_err->move(40,220);
            err_add++;
            if(err_add == 80) //4s return
            {
                err_add = 0;
                carderr = 0;
                API_Write_DB_Nbyte(PL_BOOKCARD_ERR,(int *)(&carderr),sizeof(carderr));
            }

            if(language_num == 1)
            {
                ui->label_card_err->setText(QString::fromUtf8("验证失败,请确认预约卡号"));
                ui->label_book->setText(QString::fromUtf8(""));
                ui->label_book_2->setText(QString::fromUtf8(""));
                ui->label_down->setText("");
                ui->label_start->setText("");
                ui->label_start_2->setText("");
            }
            else  if(language_num == 2)
            {
                ui->label_card_err->setText("Can not pass,please check the card");
                ui->label_book->setText("");
                ui->label_book_2->setText(QString::fromUtf8(""));
                ui->label_down->setText("");
                ui->label_start->setText("");
                ui->label_start_2->setText("");
            }
            else
            {

            }
        }
        else
        {
            ui->label_card_err->move(40,500);
            if(language_num == 1)
            {
                  //ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
                  ui->label_book->setText(QString::fromUtf8("已预约充电"));
                  ui->label_book_2->setText(QString::fromUtf8("自动解除预约"));
                   ui->label_start_2->setText(QString::fromUtf8("设备将在"));
             //ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
            }
            else  if(language_num == 2)
            {
                 // ui->label_logo->setText("AC charging pile");
                  ui->label_book->setText("has been ordered");
                  ui->label_book_2->setText("Automatic termination of appointment");
                  ui->label_stubnum->setText("Telephone :");
            }
            else
            {

            }
        }
}

void Dialog_book::update_hmi_page_index(void)
{
        API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
       if(hmi_page_index != PAGEINDEX_BOOKSERVICE)
       {
           exit_page_dlg();
       }
       else
       {

       }
}

void Dialog_book::exit_page_dlg()
{
    init_page_val();
    timer->stop();
    emit  signal_exit_bookdlg();
    //delete book_dlg;
    //book_dlg = NULL;
}
