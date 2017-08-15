#include "globalhmi.h"

QTranslator *tor;
QProcess *mplayerProcess;




INT8        hmilev  = HMI_LOG_LEV;
UINT8       hmi_button_dn_num = 0;
UINT8       DataType;
void     (*API_DB_Initial)();
INT16    (*API_Read_DB_Nbyte)(UINT32 label,void* Data,UINT16 n);
INT16    (*API_Write_DB_Nbyte)(UINT32 label,void* Data,UINT16 n);


UINT8    hmi_page_index;
UINT8    hmi_page_index_cur;
INT8 main_card_sn[16+1] = {0};
INT8     main_card_sn_temp[16+1] = {0};

int history_setpage=0;
int  error_state_flag = 0;
char *config_path="/usr/config/syssetting.ini";
char *data_path="/usr/data/errorinfor.txt";
char * history_path="/usr/data/history.txt";
char* history_net_path="/usr/data/history_net.txt";

char Section_name[BUFFERLEN_32];
char Key_name[BUFFERLEN_32];
char Tempor_name[256];

char Set_paswd[17];
char phonenum[25];
char phonenum_2[25];
char code[25];
char websize[100];
char carnum_buf[50];
char carnum_back[50];
char qrencd_str_header[10] = "http://";
char qrencd_str_middle[5] = "/pl/";

// char *setvalue  -> const char *setvalue

int Inibuf_init(char *storebuf,int storebuf_len,const char *setvalue)
 {
        int minlen=0;
        int setvaluelen=0;
        if(storebuf==NULL||storebuf_len==0)
        {
                return FALSE;
        }
        memset(storebuf,0,storebuf_len);
        setvaluelen=strlen(setvalue);
        minlen=(storebuf_len<setvaluelen)?storebuf_len:setvaluelen;
        memcpy(storebuf,setvalue,minlen);
        return TRUE;
 }

void timedelay_msec(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}

int language_num = 1;

int handle_dlg_main;
int handle_dlg_p01;
int handle_dlg_p02;
int handle_dlg_p03;
//int handle_dlg_p04;
int handle_dlg_p05;
int handle_dlg_p06;
int handle_dlg_p07;
int handle_dlg_p08;
int handle_dlg_p09;
int handle_dlg_p10;
int handle_dlg_p11;
int handle_dlg_p12;
int handle_dlg_p13;
int handle_dlg_p14;
int handle_dlg_p15;
int handle_dlg_p16;
int handle_dlg_p17;
//int handle_dlg_p18;
int handle_dlg_p19;
int handle_dlg_p20;

class dialog_2                       *dlg_2;
class dialog_1                       *dlg_1;
class main_dialog                    *main_dlg;
class p01_passwd_dialog              *p01_dlg;
class p02_servchoose_dialog          *p02_dlg;
class p03_historyquery_dialog        *p03_dlg;
//class p04_alarmquery_dialog          *p04_dlg;
class p05_chargelink_dialog          *p05_dlg;
class p06_chargeconfigrm_dialog      *p06_dlg;
class p07_chargetypechoose_dialog    *p07_dlg;
class p08_chargebytime_dialog        *p08_dlg;
class p09_chargebyenergy_dialog      *p09_dlg;
class p10_chargebyauto_dialog        *p10_dlg;
class p11_charging_dialog            *p11_dlg;
class p12_payoff_dialog              *p12_dlg;
class p13_setpara_dialog             *p13_dlg;
class p14_setpara_sub1_dialog        *p14_dlg;
class p15_setpara_sub2_dialog        *p15_dlg;
class p16_setpara_sub3_dialog        *p16_dlg;
class p17_setpara_sub4_dialog        *p17_dlg;
class p18_setpara_sub5_dialog        *p18_dlg;
//class p18_choose_charge_type        *p18_dlg;
class p19_charging_dialog             *p19_dlg;
class p20_payoff_dialog               *p20_dlg;

//class p21_leftmoney_dialog           *p21_dlg;
//class p22_ElecPrice_dialog           *p22_dlg;
//class p23_chargebymoney              *p23_dlg;
class p24_setpara_sub6_dialog          *p24_dlg;
class p21_judge_continue               *p21_dlg;
class Dialog_error                     *err_dlg;
class Dialog_end                       *end_dlg;
class Dialog_book                      *book_dlg;
class Dialog_checkcaed                 *checkcard_dlg;
class Dialog_back                      *back_dlg;
class Dialog_link_err                  *link_err_dlg;
class Dialog_diff_card                 *diff_card_dlg;
class Dialog_pull_gun                  *pull_gun_dlg;
class Dialog_money_left                *money_left_dlg;
class Dialog_history_net               *history_dlg;
class Dialog_first_err                 *firsterr_dlg;
class Dialog_history_choose            *his_choose_dlg;
class Dialog_passwd_app                *passwd_app_dlg;
class Dialog_carnum                    *carnum_dlg;
class dialog_err_carconfirm            *err_carconfirm_dlg;
class dialog_not_putiancard            *not_putiancard_dlg;

class dialog_err_choose                *err_choose_dlg;
class dialog_local_err                 *local_err_dlg;
class dialog_remote_err                *remote_err_dlg;