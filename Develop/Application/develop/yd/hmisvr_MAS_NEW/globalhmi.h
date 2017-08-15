#ifndef GLOBALHMI_H
#define GLOBALHMI_H

#include <QtGui>
#include "dialog_2.h"
#include "dialog_1.h"
#include "main_dialog.h"
#include "p01_passwd_dialog.h"
#include "p02_servchoose_dialog.h"
#include "p03_historyquery_dialog.h"
//#include "p04_alarmquery_dialog.h"
#include "p05_chargelink_dialog.h"
#include "p06_chargeconfigrm_dialog.h"
#include "p07_chargetypechoose_dialog.h"
#include "p08_chargebytime_dialog.h"
#include "p09_chargebyenergy_dialog.h"
#include "p10_chargebyauto_dialog.h"
#include "p11_charging_dialog.h"
#include "p12_payoff_dialog.h"
#include "p13_setpara_dialog.h"
#include "p14_setpara_sub1_dialog.h"
#include "p15_setpara_sub2_dialog.h"
#include "p16_setpara_sub3_dialog.h"
#include "p17_setpara_sub4_dialog.h"
#include "p18_setpara_sub5_dialog.h"
//#include "p18_choose_charge_type.h"
#include "p19_charging_dialog.h"
#include "p20_payoff_dialog.h"
//#include "p21_leftmoney_dialog.h"
//#include "p22_elecprice_dialog.h"
//#include "p23_chargebymoney.h"
#include "p24_setpara_sub6_dialog.h"
#include "p21_judge_continue.h"
#include "dialog_error.h"
#include "dialog_end.h"
#include "dialog_book.h"
#include "dialog_checkcaed.h"
#include "dialog_back.h"
#include "dialog_link_err.h"
#include "dialog_diff_card.h"
#include "dialog_pull_gun.h"
#include "dialog_money_left.h"
#include "dialog_history_net.h"
#include"dialog_first_err.h"
#include "dialog_history_choose.h"
#include "dialog_passwd_app.h"
#include "dialog_carnum.h"
#include "dialog_err_carconfirm.h"
#include "dialog_not_putiancard.h"

#include "dialog_err_choose.h"
#include "dialog_local_err.h"
#include "dialog_remote_err.h"

#include "globalhmi.h"
#include "DB_Unity.h"
#include <dlfcn.h>
#include "inifile.h"
#include "debug.h"
#include "gui.h"
#include "ioremap.h"
#include <time.h>
#include <string.h>

#include "NetWorkAnanisis.h"

//#define BUFFERLEN_32   32
//#define INIFILE_LININBUF_SIZE 256

#define     MAX_DEVWD_LEN  16
#define     MAX_COST_LEN  4
#define     MAX_SOFT_LEN  4
#define     MAX_SOURCE_LEN  20


#define     MAX_PASSWD_LEN  16
#define     HMI_LOG_LEV     4
#define     PAGE_FLUSH_TIMER    50//50
#define     SETPAGE_FLUSH_TIMER  50//20

#define     CUR_CHG_STAT_CHARGING   1
#define     CUR_CHG_STAT_STOP       0

#define     PIC_MAX_COUNT 17
#define     PIC_MIN_COUNT 4

#define     DEF_ADD_PAGE_P18_BETWEEN_P01_AND_P02

extern int history_setpage;
extern   int  error_state_flag;
extern char* config_path;
extern char* data_path;
extern char* history_path;
extern char* history_net_path;

extern  char Section_name[32];
extern  char Key_name[32];
extern  char Tempor_name[256];
extern  char qrencd_str_header[10];
extern  char qrencd_str_middle[5];

// char *setvalue  -> const char *setvalue
extern int Inibuf_init(char *storebuf,int storebuf_len,const char *setvalue);
extern void timedelay_msec(unsigned int msec);

extern char carnum_back[50];
extern char carnum_buf[50];
extern char Set_paswd[17];
extern char phonenum[25];
extern char phonenum_2[25];
extern char code[25];
extern char websize[100];
extern QTranslator *tor;
extern QProcess *mplayerProcess;

extern INT8 main_card_sn[16+1];
extern INT8 main_card_sn_temp[17];
extern INT8     hmilev;
extern UINT8    hmi_page_index;
extern UINT8    hmi_page_index_cur;
extern UINT8    hmi_button_dn_num;
extern UINT8    DataType;
extern void     (*API_DB_Initial)(void);
extern INT16    (*API_Read_DB_Nbyte)(UINT32 label,void* Data,UINT16 n);
extern INT16    (*API_Write_DB_Nbyte)(UINT32 label,void* Data,UINT16 n);

extern int language_num;

extern int handle_dlg_main;
extern int handle_dlg_p01;
extern int handle_dlg_p02;
extern int handle_dlg_p03;
//extern int handle_dlg_p04;
extern int handle_dlg_p05;
extern int handle_dlg_p06;
extern int handle_dlg_p07;
extern int handle_dlg_p08;
extern int handle_dlg_p09;
extern int handle_dlg_p10;
extern int handle_dlg_p11;
extern int handle_dlg_p12;
extern int handle_dlg_p13;
extern int handle_dlg_p14;
extern int handle_dlg_p15;
extern int handle_dlg_p16;
extern int handle_dlg_p17;
//extern int handle_dlg_p18;
extern int handle_dlg_p19;
extern int handle_dlg_p20;

extern class dialog_2                       *dlg_2;
extern class dialog_1                       *dlg_1;
extern class main_dialog                    *main_dlg;
extern class p01_passwd_dialog              *p01_dlg;
extern class p02_servchoose_dialog          *p02_dlg;
extern class p03_historyquery_dialog        *p03_dlg;
//extern class p04_alarmquery_dialog          *p04_dlg;
extern class p05_chargelink_dialog          *p05_dlg;
extern class p06_chargeconfigrm_dialog      *p06_dlg;
extern class p07_chargetypechoose_dialog    *p07_dlg;
extern class p08_chargebytime_dialog        *p08_dlg;
extern class p09_chargebyenergy_dialog      *p09_dlg;
extern class p10_chargebyauto_dialog        *p10_dlg;
extern class p11_charging_dialog            *p11_dlg;
extern class p12_payoff_dialog              *p12_dlg;
extern class p13_setpara_dialog             *p13_dlg;
extern class p14_setpara_sub1_dialog        *p14_dlg;
extern class p15_setpara_sub2_dialog        *p15_dlg;
extern class p16_setpara_sub3_dialog        *p16_dlg;
extern class p17_setpara_sub4_dialog        *p17_dlg;
extern class p18_setpara_sub5_dialog        *p18_dlg;
//extern class p18_choose_charge_type         *p18_dlg;
extern class p19_charging_dialog            *p19_dlg;
extern class p20_payoff_dialog              *p20_dlg;

//extern class p21_leftmoney_dialog              *p21_dlg;
//extern class p22_ElecPrice_dialog              *p22_dlg;
//extern class p23_chargebymoney             *p23_dlg;
extern class p24_setpara_sub6_dialog          *p24_dlg;
extern class p21_judge_continue               *p21_dlg;
extern class Dialog_error                     *err_dlg;
extern class Dialog_end                       *end_dlg;
extern class Dialog_book                      *book_dlg;
extern class Dialog_checkcaed                 *checkcard_dlg;
extern class Dialog_back                      *back_dlg;
extern class Dialog_link_err                  *link_err_dlg;
extern class Dialog_diff_card                 *diff_card_dlg;
extern class Dialog_pull_gun                  *pull_gun_dlg;
extern class Dialog_money_left                *money_left_dlg;
extern class Dialog_history_net               *history_dlg;
extern class Dialog_first_err                 *firsterr_dlg;
extern class Dialog_history_choose            *his_choose_dlg;
extern class Dialog_passwd_app                *passwd_app_dlg;
extern class Dialog_carnum                    *carnum_dlg;
extern class dialog_err_carconfirm            *err_carconfirm_dlg;
extern class dialog_not_putiancard            *not_putiancard_dlg;

extern class dialog_err_choose                *err_choose_dlg;
extern class dialog_local_err                 *local_err_dlg;
extern class dialog_remote_err                *remote_err_dlg;
#endif
