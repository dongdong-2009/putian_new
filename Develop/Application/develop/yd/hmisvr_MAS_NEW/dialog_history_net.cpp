#include "dialog_history_net.h"
#include "ui_dialog_history_net.h"
#include "globalhmi.h"
#include <string.h>

Dialog_history_net::Dialog_history_net ( QWidget* parent ) :
	QDialog ( parent ),
	ui ( new Ui::Dialog_history_net )
{
	ui->setupUi ( this );

}

Dialog_history_net::~Dialog_history_net()
{
	delete ui;
}

struct _historyinfor_net
{
	short  UerID;                           //BYTE=2
	short  CMD_Serail;                      //BYTE=2
	//unsigned char  HistoryCheckCount;
	unsigned int  RecordIndex;
	unsigned char StubIndex[8];
	unsigned char  CardNumber[16];
	unsigned char Car_VIN[17];              //if no,fill it with space
	unsigned char Car_plate[8];
	unsigned char Start_Soc;
	unsigned char Stop_Soc;
	short UseCapa;                          //I*Time 安培*时间
	short Use_kwh;
	unsigned int chargecontinuetm;          //sec
	unsigned char DealType;
	unsigned char Stop_Reason;
	SYNCHRO_TIME_S Startcharge_TM;
	SYNCHRO_TIME_S Stopcharge_TM;
	//SYNCHRO_TIME_S DealTime;
	unsigned int   Start_KWH;
	unsigned int   Stop_KWH;
};

int remote_lblnum_flag,remote_lblnum_flag_2,remote_lblnum_flag_3,remote_lblnum_flag_4,remote_lblnum_flag_5;
int remote_lblnum_temp,remote_lblnum_temp_2,remote_lblnum_temp_3,remote_lblnum_temp_4,remote_lblnum_temp_5;

struct _historyinfor_net history_net_buf[1001];
int remote_sum=0;

int HistoryAnanisisnet_show ( const char* file_name, struct _historyinfor_net*  p_cmd_code_0x92OutPt,int maxindex );

void Dialog_history_net::init_page_dlg()
{
	initialize_info_flag = 1;

	timer = new QTimer ( this );
	connect ( timer,SIGNAL ( timeout() ),this,SLOT ( timer_handle() ) );

	printf ( "***************************** init_page_dlg: initialize_info_flag = %d \n",initialize_info_flag );

	timer->start ( PAGE_FLUSH_TIMER );
	init_page_val();
	ui->label_stubnum->setText ( QString::fromUtf8 ( "桩编号：" ) );
	ui->label_phone->setText ( QString::fromUtf8 ( "客服热线：" ) );
	ui->label_code->setText ( code );
	ui->label_num1->setText ( phonenum );
	ui->label_num2->setText ( phonenum_2 );
	if ( language_num == 1 )
	{

	}
	else  if ( language_num == 2 )
	{
		//ui->label_logo->setText("DC charging pile");
		ui->label_stubnum->setText ( "Telephone :" );
		ui->pbtn_enter->setText ( "Back" );
		ui->pbtn_up->setText ( "Page Up" );
		ui->pbtn_down->setText ( "Page Down" );
		ui->label_title->setText ( "History" );
		ui->lbl_num->setText ( "Num" );
		ui->lbl_card->setText ( "CardNum" );
		ui->lbl_start_soc->setText ( "StartSoc" );
		ui->lbl_end_soc->setText ( "EndSoc" );
		ui->lbl_kwh->setText ( "UsedEnergy" );
		ui->lbl_time->setText ( "UsedTime" );
	}

}

void Dialog_history_net::init_page_val()
{
	UINT8 data = NO_BUTTON;
	API_Write_DB_Nbyte ( PL_HMI_BUTTON_DOWN, ( INT8* ) ( &data ),sizeof ( data ) );

	memset ( lbl_txt,0,sizeof ( lbl_txt ) );
	memset ( lbl_txt_2,0,sizeof ( lbl_txt_2 ) );
	memset ( lbl_txt_3,0,sizeof ( lbl_txt_3 ) );
	memset ( lbl_txt_4,0,sizeof ( lbl_txt_4 ) );
	memset ( lbl_txt_5,0,sizeof ( lbl_txt_5 ) );

    lbl_num = 0;
    lbl_num_2 = 0;
    lbl_num_3 = 0;
    lbl_num_4 = 0;
    lbl_num_5 = 0;
}

void Dialog_history_net::start_timer()
{
	timer->start ( PAGE_FLUSH_TIMER );
}

void Dialog_history_net::timer_handle()
{
	update_page_info();
	update_hmi_page_index();
}

char* itoa_net ( unsigned int num,char* str )
{
	memset ( str,0,sizeof ( str ) );
	if ( num==0 )
	{
		// memset(str,0,sizeof(str));
	}
	else
	{
		sprintf ( str,"%d",num );
	}
	return str;
}

char* itob_net ( float num,char* str )
{
	memset ( str,0,sizeof ( str ) );
	if ( num==0 )
	{
		// memset(str,0,sizeof(str));
	}
	else
	{
		sprintf ( str,"%.2f",num );
	}
	return str;
}

void Dialog_history_net::update_page_info()
{

#if 1
	char history_temp = 0;
	API_Read_DB_Nbyte ( PL_HISTORY_CHECK, ( INT8* ) ( &history_temp ),sizeof ( history_temp ) );
	//history_temp = 1;
	if ( history_temp == 0 )
	{
		ui->label_state->setText ( QString::fromUtf8 ( "查询中..." ) );
	}
	else if ( history_temp == 1 )
	{
		ui->label_state->setText ( QString::fromUtf8 ( "查询成功!" ) );

		if ( initialize_info_flag == 1 )
		{
			memset ( history_net_buf,0,sizeof ( history_net_buf ) );


#if 1
          printf("===========================%s(%d)\n",__FILE__,__LINE__);
            FILE * fd_file_p = fopen(history_net_path, "rb");
            if(fd_file_p == NULL)
            {
                printf("--ERROR--fopen or create history_net.txt FAILED\n");
            }

            char buf[150] = {0};
            while(fgets(buf, 100, fd_file_p) != NULL)
            {
                printf("====#####$$$$$$$$$$$$$The buf is %s\n", buf);
            }

            fclose(fd_file_p);
            printf("===========================%s(%d)\n",__FILE__,__LINE__);
#endif

			remote_sum = HistoryAnanisisnet_show ( history_net_path, history_net_buf,1001 );
			//remote_sum = HistoryAnanisisnet_show(history_path, history_net_buf,1001);

			printf ( "***********************  remote_sum = %d \n",remote_sum );

			if ( remote_sum >= 5 )
			{
				lbl_num  =remote_sum ;
				lbl_num_2=remote_sum - 1;
				lbl_num_3=remote_sum - 2;
				lbl_num_4=remote_sum - 3;
				lbl_num_5=remote_sum - 4;
			}
			else if ( remote_sum == 4 )
			{
				lbl_num  =remote_sum ;
				lbl_num_2=remote_sum - 1;
				lbl_num_3=remote_sum - 2;
				lbl_num_4=remote_sum - 3;
			}
			else if ( remote_sum == 3 )
			{
				lbl_num  =remote_sum ;
				lbl_num_2=remote_sum - 1;
				lbl_num_3=remote_sum - 2;
			}
			else if ( remote_sum == 2 )
			{
				lbl_num  =remote_sum ;
				lbl_num_2=remote_sum - 1;
			}
			else if ( remote_sum == 1 )
			{
				lbl_num  =remote_sum ;
			}
			else
			{
			}

			initialize_info_flag = 2;

		}
		else
		{

		}

		if ( 0 < remote_sum )
		{
			memcpy ( lbl_txt, history_net_buf[0].CardNumber,sizeof ( history_net_buf[0].CardNumber ) );
			memcpy ( lbl_txt_2, history_net_buf[1].CardNumber,sizeof ( history_net_buf[1].CardNumber ) );
			memcpy ( lbl_txt_3, history_net_buf[2].CardNumber,sizeof ( history_net_buf[2].CardNumber ) );
			memcpy ( lbl_txt_4, history_net_buf[3].CardNumber,sizeof ( history_net_buf[3].CardNumber ) );
			memcpy ( lbl_txt_5, history_net_buf[4].CardNumber,sizeof ( history_net_buf[4].CardNumber ) );

			start   = history_net_buf[0].Start_Soc;
			start_2 = history_net_buf[1].Start_Soc;
			start_3 = history_net_buf[2].Start_Soc;
			start_4 = history_net_buf[3].Start_Soc;
			start_5 = history_net_buf[4].Start_Soc;

			end   = history_net_buf[0].Stop_Soc;
			end_2 = history_net_buf[1].Stop_Soc;
			end_3 = history_net_buf[2].Stop_Soc;
			end_4 = history_net_buf[3].Stop_Soc;
			end_5 = history_net_buf[4].Stop_Soc;

			meter  = ( float ) history_net_buf[0].Use_kwh/100;
			meter_2= ( float ) history_net_buf[1].Use_kwh/100;
			meter_3= ( float ) history_net_buf[2].Use_kwh/100;
			meter_4= ( float ) history_net_buf[3].Use_kwh/100;
			meter_5= ( float ) history_net_buf[4].Use_kwh/100;

			chtime  = history_net_buf[0].chargecontinuetm/60;
			chtime_2= history_net_buf[1].chargecontinuetm/60;
			chtime_3= history_net_buf[2].chargecontinuetm/60;
			chtime_4= history_net_buf[3].chargecontinuetm/60;
			chtime_5= history_net_buf[4].chargecontinuetm/60;

			ui->label_txt->setText ( QString::fromUtf8 ( lbl_txt ) );
			ui->label_txt_2->setText ( QString::fromUtf8 ( lbl_txt_2 ) );
			ui->label_txt_3->setText ( QString::fromUtf8 ( lbl_txt_3 ) );
			ui->label_txt_4->setText ( QString::fromUtf8 ( lbl_txt_4 ) );
			ui->label_txt_5->setText ( QString::fromUtf8 ( lbl_txt_5 ) );

			char ttemp[50]= {};

			ui->label_end->setText ( itoa_net ( end,ttemp ) );
			ui->label_end_2->setText ( itoa_net ( end_2,ttemp ) );
			ui->label_end_3->setText ( itoa_net ( end_3,ttemp ) );
			ui->label_end_4->setText ( itoa_net ( end_4,ttemp ) );
			ui->label_end_5->setText ( itoa_net ( end_5,ttemp ) );

			ui->label_start->setText ( itoa_net ( start,ttemp ) );
			ui->label_start_2->setText ( itoa_net ( start_2,ttemp ) );
			ui->label_start_3->setText ( itoa_net ( start_3,ttemp ) );
			ui->label_start_4->setText ( itoa_net ( start_4,ttemp ) );
			ui->label_start_5->setText ( itoa_net ( start_5,ttemp ) );

			if ( chtime==0&&lbl_txt[0] )
			{
				ui->label_time->setNum ( 0 );
			}
			else
			{
				ui->label_time->setText ( itoa_net ( chtime,ttemp ) );
			}

			if ( chtime_2==0&&lbl_txt_2[0] )
			{
				ui->label_time_2->setNum ( 0 );
			}
			else
			{
				ui->label_time_2->setText ( itoa_net ( chtime_2,ttemp ) );
			}

			if ( chtime_3==0&&lbl_txt_3[0] )
			{
				ui->label_time_3->setNum ( 0 );
			}
			else
			{
				ui->label_time_3->setText ( itoa_net ( chtime_3,ttemp ) );
			}

			if ( chtime_4==0&&lbl_txt_4[0] )
			{
				ui->label_time_4->setNum ( 0 );
			}
			else
			{
				ui->label_time_4->setText ( itoa_net ( chtime_4,ttemp ) );
			}

			if ( chtime_5==0&&lbl_txt_5[0] )
			{
				ui->label_time_5->setNum ( 0 );
			}
			else
			{
				ui->label_time_5->setText ( itoa_net ( chtime_5,ttemp ) );
			}

			if ( meter==0&&lbl_txt[0] )
			{
				ui->label_meter->setNum ( 0 );
			}
			else
			{
				ui->label_meter->setText ( itob_net ( meter,ttemp ) );
			}

			if ( meter_2==0&&lbl_txt_2[0] )
			{
				ui->label_meter_2->setNum ( 0 );
			}
			else
			{
				ui->label_meter_2->setText ( itob_net ( meter_2,ttemp ) );
			}

			if ( meter_3==0&&lbl_txt_3[0] )
			{
				ui->label_meter_3->setNum ( 0 );
			}
			else
			{
				ui->label_meter_3->setText ( itob_net ( meter_3,ttemp ) );
			}

			if ( meter_4==0&&lbl_txt_4[0] )
			{
				ui->label_meter_4->setNum ( 0 );
			}
			else
			{
				ui->label_meter_4->setText ( itob_net ( meter_4,ttemp ) );
			}

			if ( meter_5==0&&lbl_txt_5[0] )
			{
				ui->label_meter_5->setNum ( 0 );
			}
			else
			{
				ui->label_meter_5->setText ( itob_net ( meter_5,ttemp ) );
			}

			//充电序号显示
			if ( lbl_txt[0] )
			{
				ui->label_num->setNum ( lbl_num );
			}
			else
			{
				ui->label_num->setText ( NULL );
			}

			if ( lbl_txt_2[0] )
			{
				ui->label_num_2->setNum ( lbl_num_2 );
			}
			else
			{
				ui->label_num_2->setText ( NULL );
			}

			if ( lbl_txt_3[0] )
			{
				ui->label_num_3->setNum ( lbl_num_3 );
			}
			else
			{
				ui->label_num_3->setText ( NULL );
			}

			if ( lbl_txt_4[0] )
			{
				ui->label_num_4->setNum ( lbl_num_4 );
			}
			else
			{
				ui->label_num_4->setText ( NULL );
			}

			if ( lbl_txt_5[0] )
			{
				ui->label_num_5->setNum ( lbl_num_5 );
			}
			else
			{
				ui->label_num_5->setText ( NULL );
			}

		}
/*
		printf ( "*********************** 2: lbl_num   = %d \n",lbl_num );
		printf ( "*********************** 2: lbl_num_2 = %d \n",lbl_num_2 );
		printf ( "*********************** 2: lbl_num_3 = %d \n",lbl_num_3 );
		printf ( "*********************** 2: lbl_num_4 = %d \n",lbl_num_4 );
		printf ( "*********************** 2: lbl_num_5 = %d \n",lbl_num_5 );
*/
	}
	else
	{
		ui->label_state->setText ( QString::fromUtf8 ( "查询失败!" ) );
	}
#endif

}

void Dialog_history_net::update_hmi_page_index()
{
	API_Read_DB_Nbyte ( PL_HMI_PAGE_INDEX, ( INT8* ) ( &hmi_page_index ),sizeof ( hmi_page_index ) );

	if ( hmi_page_index != PAGEINDEX_HISTORY_NET )
	{
		exit_page_dlg();
	}
	else
	{

	}
}

void Dialog_history_net::exit_page_dlg()
{
	//DebugMsg(hmilev,8,"exit_page_dlg\n");

	UINT8 data = NO_BUTTON;
	API_Write_DB_Nbyte ( PL_HMI_BUTTON_DOWN, ( INT8* ) ( &data ),sizeof ( data ) );

	//ErrMsg("$$$ leave history page $$$\n");

	timer->stop();
	emit signal_exit_historydlg();
	delete p03_dlg;
	p03_dlg = NULL;
}

void Dialog_history_net::on_pbtn_up_clicked()
{
	hmi_button_dn_num=PAGEUP_BUTTON;
	API_Write_DB_Nbyte ( PL_HMI_BUTTON_DOWN, ( INT8* ) ( &hmi_button_dn_num ),sizeof ( hmi_button_dn_num ) );

	if ( remote_sum - lbl_num >= 5 ) // 11 - 6
	{
		lbl_num=lbl_num+5;  // 11 - 11
		lbl_num_2=lbl_num_2+5;
		lbl_num_3=lbl_num_3+5;
		lbl_num_4=lbl_num_4+5;
		lbl_num_5=lbl_num_5+5;
		//11 - 11
		start=history_net_buf[remote_sum - lbl_num].Start_Soc;
		start_2= history_net_buf[remote_sum - lbl_num_2].Start_Soc;
		start_3= history_net_buf[remote_sum - lbl_num_3].Start_Soc;
		start_4= history_net_buf[remote_sum - lbl_num_4].Start_Soc;
		start_5= history_net_buf[remote_sum - lbl_num_5].Start_Soc;

		end= history_net_buf[remote_sum - lbl_num].Stop_Soc;
		end_2= history_net_buf[remote_sum - lbl_num_2].Stop_Soc;
		end_3= history_net_buf[remote_sum - lbl_num_3].Stop_Soc;
		end_4= history_net_buf[remote_sum - lbl_num_4].Stop_Soc;
		end_5= history_net_buf[remote_sum - lbl_num_5].Stop_Soc;

		meter= ( float ) history_net_buf[remote_sum - lbl_num].Use_kwh/100;
		meter_2= ( float ) history_net_buf[remote_sum - lbl_num_2].Use_kwh/100;
		meter_3= ( float ) history_net_buf[remote_sum - lbl_num_3].Use_kwh/100;
		meter_4= ( float ) history_net_buf[remote_sum - lbl_num_4].Use_kwh/100;
		meter_5= ( float ) history_net_buf[remote_sum - lbl_num_5].Use_kwh/100;

		chtime= history_net_buf[remote_sum - lbl_num].chargecontinuetm/60;
		chtime_2= history_net_buf[remote_sum - lbl_num_2].chargecontinuetm/60;
		chtime_3= history_net_buf[remote_sum - lbl_num_3].chargecontinuetm/60;
		chtime_4= history_net_buf[remote_sum - lbl_num_4].chargecontinuetm/60;
		chtime_5= history_net_buf[remote_sum - lbl_num_5].chargecontinuetm/60;


		memcpy ( lbl_txt, history_net_buf[remote_sum - lbl_num].CardNumber,sizeof ( history_net_buf[remote_sum - lbl_num].CardNumber ) );
		memcpy ( lbl_txt_2, history_net_buf[remote_sum - lbl_num_2].CardNumber,sizeof ( history_net_buf[remote_sum - lbl_num_2].CardNumber ) );
		memcpy ( lbl_txt_3, history_net_buf[remote_sum - lbl_num_3].CardNumber,sizeof ( history_net_buf[remote_sum - lbl_num_3].CardNumber ) );
		memcpy ( lbl_txt_4, history_net_buf[remote_sum - lbl_num_4].CardNumber,sizeof ( history_net_buf[remote_sum - lbl_num_4].CardNumber ) );
		memcpy ( lbl_txt_5, history_net_buf[remote_sum - lbl_num_5].CardNumber,sizeof ( history_net_buf[remote_sum - lbl_num_5].CardNumber ) );
	}
	else
	{

	}
}


void Dialog_history_net::on_pbtn_down_clicked()
{
	// ErrMsg("hmi_page_index error[%d]\n",remote_sum);

	hmi_button_dn_num=PAGEDOWN_BUTTON;
	API_Write_DB_Nbyte ( PL_HMI_BUTTON_DOWN, ( INT8* ) ( &hmi_button_dn_num ),sizeof ( hmi_button_dn_num ) );

	if ( lbl_num > 5 )
	{
		if ( lbl_num - 5 > 0 )
		{
			lbl_num  =lbl_num - 5 ;
		}
		else if ( lbl_num > 0 )
		{
			remote_lblnum_flag = 1;
			remote_lblnum_temp = lbl_num - 5;
			lbl_num =remote_sum + 1;

		}
		else
		{
		}

		if ( lbl_num_2 - 5 > 0 )
		{
			lbl_num_2  =lbl_num_2 - 5 ;
		}
		else if ( lbl_num_2 > 0 )
		{
			remote_lblnum_flag_2 = 1;
			remote_lblnum_temp_2= lbl_num_2 - 5;
			lbl_num_2  =remote_sum + 1;

		}
		else
		{
		}

		if ( lbl_num_3 - 5 > 0 )
		{
			lbl_num_3  =lbl_num_3 - 5 ;
		}
		else if ( lbl_num_3 > 0 )
		{
			remote_lblnum_flag_3 = 1;
			remote_lblnum_temp_3= lbl_num_3 - 5;
			lbl_num_3  =remote_sum + 1;

		}
		else
		{
		}

		if ( lbl_num_4 - 5 > 0 )
		{
			lbl_num_4  =lbl_num_4 - 5 ;
		}
		else if ( lbl_num_4 > 0 )
		{
			remote_lblnum_flag_4 = 1;
			remote_lblnum_temp_4= lbl_num_4 - 5;
			lbl_num_4  =remote_sum + 1;

		}
		else
		{
		}

		if ( lbl_num_5 - 5 > 0 )
		{
			lbl_num_5  =lbl_num_5 - 5 ;
		}
		else if ( lbl_num_5 > 0 )
		{
			remote_lblnum_flag_5 = 1;
			remote_lblnum_temp_5 = lbl_num_5 - 5;
			lbl_num_5  =remote_sum + 1;

		}
		else
		{
		}


		start=history_net_buf[remote_sum - lbl_num].Start_Soc;
		start_2= history_net_buf[remote_sum - lbl_num_2].Start_Soc;
		start_3= history_net_buf[remote_sum - lbl_num_3].Start_Soc;
		start_4= history_net_buf[remote_sum - lbl_num_4].Start_Soc;
		start_5= history_net_buf[remote_sum - lbl_num_5].Start_Soc;

		end= history_net_buf[remote_sum - lbl_num].Stop_Soc;
		end_2= history_net_buf[remote_sum - lbl_num_2].Stop_Soc;
		end_3= history_net_buf[remote_sum - lbl_num_3].Stop_Soc;
		end_4= history_net_buf[remote_sum - lbl_num_4].Stop_Soc;
		end_5= history_net_buf[remote_sum - lbl_num_5].Stop_Soc;

		meter= ( float ) history_net_buf[remote_sum - lbl_num].Use_kwh/100;
		meter_2= ( float ) history_net_buf[remote_sum - lbl_num_2].Use_kwh/100;
		meter_3= ( float ) history_net_buf[remote_sum - lbl_num_3].Use_kwh/100;
		meter_4= ( float ) history_net_buf[remote_sum - lbl_num_4].Use_kwh/100;
		meter_5= ( float ) history_net_buf[remote_sum - lbl_num_5].Use_kwh/100;

		chtime= history_net_buf[remote_sum - lbl_num].chargecontinuetm/60;
		chtime_2= history_net_buf[remote_sum - lbl_num_2].chargecontinuetm/60;
		chtime_3= history_net_buf[remote_sum - lbl_num_3].chargecontinuetm/60;
		chtime_4= history_net_buf[remote_sum - lbl_num_4].chargecontinuetm/60;
		chtime_5= history_net_buf[remote_sum - lbl_num_5].chargecontinuetm/60;

		memcpy ( lbl_txt, history_net_buf[remote_sum - lbl_num].CardNumber,sizeof ( history_net_buf[remote_sum - lbl_num].CardNumber ) );
		memcpy ( lbl_txt_2, history_net_buf[remote_sum - lbl_num_2].CardNumber,sizeof ( history_net_buf[remote_sum - lbl_num_2].CardNumber ) );
		memcpy ( lbl_txt_3, history_net_buf[remote_sum - lbl_num_3].CardNumber,sizeof ( history_net_buf[remote_sum - lbl_num_3].CardNumber ) );
		memcpy ( lbl_txt_4, history_net_buf[remote_sum - lbl_num_4].CardNumber,sizeof ( history_net_buf[remote_sum - lbl_num_4].CardNumber ) );
		memcpy ( lbl_txt_5, history_net_buf[remote_sum - lbl_num_5].CardNumber,sizeof ( history_net_buf[remote_sum - lbl_num_5].CardNumber ) );


		if ( remote_lblnum_flag == 1 )
		{
			lbl_num = remote_lblnum_temp;
			remote_lblnum_temp = 0;
			remote_lblnum_flag = 0;
		}

		if ( remote_lblnum_flag_2 == 1 )
		{
			lbl_num_2 = remote_lblnum_temp_2;
			remote_lblnum_temp_2 = 0;
			remote_lblnum_flag_2 = 0;
		}
		if ( remote_lblnum_flag_3 == 1 )
		{
			lbl_num_3 = remote_lblnum_temp_3;
			remote_lblnum_temp_3 = 0;
			remote_lblnum_flag_3 = 0;
		}
		if ( remote_lblnum_flag_4 == 1 )
		{
			lbl_num_4 = remote_lblnum_temp_4;
			remote_lblnum_temp_4 = 0;
			remote_lblnum_flag_4 = 0;
		}
		if ( remote_lblnum_flag_5 == 1 )
		{
			lbl_num_5 = remote_lblnum_temp_5;
			remote_lblnum_temp_5 = 0;
			remote_lblnum_flag_5 = 0;
		}

	}
	else
	{
	}

}

void Dialog_history_net::on_pbtn_enter_clicked()
{
	hmi_button_dn_num=CANCEL_BUTTON;
	API_Write_DB_Nbyte ( PL_HMI_BUTTON_DOWN, ( INT8* ) ( &hmi_button_dn_num ),sizeof ( hmi_button_dn_num ) );

	if ( 0 == strncmp ( main_card_sn_temp,main_card_sn,sizeof ( main_card_sn ) ) )
	{
		history_setpage = 1;
	}
	//hmi_page_index=PAGEINDEX_MAIN;
	//API_Write_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

}

static int fgets_count_num = 0;

int HistoryAnanisisnet_show ( const char* file_name, struct _historyinfor_net* p_cmd_code_0x92OutPt, int maxindex )
{
  printf("++++++++++++++++++%s(%d)\n",__FILE__,__LINE__);
	//store the history of one line
	unsigned char linedatabuf[MAXCHAROFPERONELINE];
	FILE* fp_file;
	//char *file_name="/home/Development/Application/develop/test_hislog.txt";
	//char *file_name="/usr/data/history.txt";
	//total pos for each line
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
	//unsigned  int  startInsertFlag=0;
	//insert history count
	unsigned  int  TempHistoryInsertCount=0;
	struct _historyinfor_net tempHistoryRecord ;
	//int tempcount=0;
    printf("+++++++++++++++file_name=%s+++%s(%d)\n",file_name,__FILE__,__LINE__);

	//recode the line number of history
	int linetotal=0;
	fp_file = fopen ( file_name, "rb" );
	if ( fp_file ==0 ) //open file error
	{
		printf ( "open historyfile error\r\n" );
		return 0;
	}
	else
	{
		printf ( "open historyfileshow success\r\n" );
	}


	//judge whether the history of struct is NULL
	if ( p_cmd_code_0x92OutPt==NULL )
	{
		fclose ( fp_file );
        printf("++++++++++++++++++%s(%d)\n",__FILE__,__LINE__);
		return 0;
	}
	memset ( linedatabuf,0,MAXCHAROFPERONELINE );
	TempHistoryInsertCount=0;

    fseek(fp_file,0,SEEK_END);
    long file_size = ftell(fp_file);
    printf("####################1file_size=%d\n",file_size);
    fseek(fp_file,0,SEEK_SET);

    sleep(5);

    fseek(fp_file,0,SEEK_END);
    file_size = ftell(fp_file);
    printf("####################2file_size=%d\n",file_size);
    fseek(fp_file,0,SEEK_SET);

	//while (fgets((char *)linedatabuf, sizeof(linedatabuf), fp_file))

	//move the pointer to get the info of the file
	while ( !feof ( fp_file ) )
	{
		//move the history of one line to linedatabuf
		//and move the file pointer to the end at the current line

        if( fgets ( ( char* ) linedatabuf, sizeof ( linedatabuf ), fp_file ) != NULL)
        {
             printf("*************** linedatabuf = %s\n",linedatabuf);
        }

        //fgets ( ( char* ) linedatabuf, sizeof ( linedatabuf ), fp_file );         // *********

        if ( feof ( fp_file ) )
		{
			//at the end of file ,stopping get historyrecord
			break;
		}

		//recode the char number of one line at current position
		readLen=strlen ( ( char* ) linedatabuf );
		if ( readLen<=3 )
		{
			continue;
		}

		//please tar the string buf for your struct
		//tile of the text
		if ( linedatabuf[startpos]=='i'&& linedatabuf[startpos+1]=='d'&&linedatabuf[startpos+2]=='x' )
		{
			continue;
		}
		if ( linedatabuf[startpos]=='#'&& linedatabuf[startpos+1]=='#'&&linedatabuf[startpos+2]=='#' )
		{
			continue;
		}
		linetotal++;

		memset ( SectionBuf,0,50 );
		Sectionindex=0;
		SectiondataPos=0;

		//starting circling(循环) to recode the char string at one line
		//such as the stubcode number and so on

		for ( startpos=0; startpos<readLen; startpos++ )
		{
			//0x0d 回车键
			//0x0a 换行键
			//equlas to '\n'(13) or '\r'(10) , go to next position
			if ( linedatabuf[startpos]==0x0d||linedatabuf[startpos]==0x0a )
			{
				//break;
				continue;
			}

			if ( linedatabuf[startpos]==0x7c ) //"|"
			{
				//use tempHistoryRecord(struct) to recode the info of one line
				// printf("1111111111111\r\n");
				if ( Sectionindex==0 ) //record index
				{

				}//end of if(Sectionindex==0)//record index
				else if ( Sectionindex==1 ) //stub code
				{
					memcpy ( &tempHistoryRecord.StubIndex,SectionBuf,sizeof ( tempHistoryRecord.StubIndex ) );
				}
				else if ( Sectionindex==2 ) //card number
				{
					memcpy ( &tempHistoryRecord.CardNumber,SectionBuf,sizeof ( tempHistoryRecord.CardNumber ) );
				}
				else if ( Sectionindex==3 ) //Car_VIN
				{
					memcpy ( &tempHistoryRecord.Car_VIN,SectionBuf,sizeof ( tempHistoryRecord.Car_VIN ) );
				}
				else if ( Sectionindex==4 ) //Car_plate
				{
					memcpy ( &tempHistoryRecord.Car_plate,SectionBuf,sizeof ( tempHistoryRecord.Car_plate ) );
				}
				else if ( Sectionindex==5 ) //Start_Soc
				{
					tempHistoryRecord.Start_Soc=atoi ( ( char* ) SectionBuf );
				}
				else if ( Sectionindex==6 ) //Stop_Soc
				{
					tempHistoryRecord.Stop_Soc=atoi ( ( char* ) SectionBuf );
				}
				else if ( Sectionindex==7 ) //UseCapa
				{
					tempHistoryRecord.UseCapa=atoi ( ( char* ) SectionBuf );
				}
				else if ( Sectionindex==8 ) //Use_kwh
				{
					tempHistoryRecord.Use_kwh=atoi ( ( char* ) SectionBuf );
				}
				else if ( Sectionindex==9 ) //chargecontinuetm
				{
					tempHistoryRecord.chargecontinuetm=atoi ( ( char* ) SectionBuf );
				}
				else if ( Sectionindex==10 ) //DealType
				{
					tempHistoryRecord.DealType=atoi ( ( char* ) SectionBuf );
				}
				else if ( Sectionindex==11 ) //Stop_Reason
				{
					tempHistoryRecord.Stop_Reason=atoi ( ( char* ) SectionBuf );
				}
				else if ( Sectionindex==12 ) //Startcharge_TM
				{
					strcat ( ( char* ) SectionBuf,"-" );
					TimeAnanisis ( &tempHistoryRecord.Startcharge_TM,SectionBuf );
				}
				else if ( Sectionindex==13 ) //Stopcharge_TM
				{
					strcat ( ( char* ) SectionBuf,"-" );
					TimeAnanisis ( &tempHistoryRecord.Stopcharge_TM,SectionBuf );
				}
				else if ( Sectionindex==14 ) //Start_KWH
				{
					tempHistoryRecord.Start_KWH=atoi ( ( char* ) SectionBuf );
				}
				else if ( Sectionindex==15 ) //Stop_KWH
				{
					tempHistoryRecord.Stop_KWH=atoi ( ( char* ) SectionBuf );
				}

				//delete the sectionBuf and conntinue to store
				memset ( SectionBuf,0,50 );
				SectiondataPos=0;

				//index plus to moving recoding the next section
				Sectionindex++;

				//continue to judge next section by '|'
				continue;
			}//end of if(linedatabuf[startpos]==0x7c)//"|"
			else
			{
				if ( SectiondataPos<50 )
				{
					SectionBuf[SectiondataPos++]=linedatabuf[startpos];
				}
			}
		}//end of for(startpos=0;startpos<readLen;startpos++)

		Sectionindex = 0;
		memset ( linedatabuf,0,MAXCHAROFPERONELINE );
		//if(startInsertFlag == 1&&tempHistoryRecord.RecordIndex!=0&&HistoryInsertCount<MAXHISTORYRETURNCOUNT)//start insert history
		if ( TempHistoryInsertCount < maxindex ) //start insert history
		{
#if 1
			if ( history_setpage )
			{
				memcpy ( &p_cmd_code_0x92OutPt[TempHistoryInsertCount],&tempHistoryRecord,sizeof ( struct _historyinfor_net ) );
				p_cmd_code_0x92OutPt[TempHistoryInsertCount].RecordIndex=linetotal;
				TempHistoryInsertCount++;
				//printf ( "******** 1- TempHistoryInsertCount = %d *******\n",TempHistoryInsertCount );
			}
			else
			{
				//printf ( "******** 2 - TempHistoryInsertCount = %d *******\n",TempHistoryInsertCount );
				if ( strncmp ( ( char* ) ( tempHistoryRecord.CardNumber ),main_card_sn,16 ) ==0 )
				{
					//ErrMsg("$$$$$$$$$$$$$$$$$$\n");
					memcpy ( &p_cmd_code_0x92OutPt[TempHistoryInsertCount],&tempHistoryRecord,sizeof ( struct _historyinfor_net ) );
					p_cmd_code_0x92OutPt[TempHistoryInsertCount].RecordIndex=linetotal;
					TempHistoryInsertCount++;
					//printf ( "******** 3 - TempHistoryInsertCount = %d *******\n",TempHistoryInsertCount );
				}
			}
#endif

		}// end of  if(startInsertFlag==1)//start insert history
		else
		{
			break;
		}
		memset ( &tempHistoryRecord,0,sizeof ( struct _historyinfor_net ) );

	}// end of  while (fgets(linedatabuf, sizeof(linedatabuf), fp_file))

	// close th file,prevent the pointer
	fclose ( fp_file );

	printf ( "**************** p_cmd_code_0x92OutPt[0].Use_kwh = %d\n",p_cmd_code_0x92OutPt[0].Use_kwh );
	printf ( "**************** p_cmd_code_0x92OutPt[1].Use_kwh = %d\n",p_cmd_code_0x92OutPt[1].Use_kwh );
	printf ( "**************** p_cmd_code_0x92OutPt[2].Use_kwh = %d\n",p_cmd_code_0x92OutPt[2].Use_kwh );
	printf ( "**************** p_cmd_code_0x92OutPt[3].Use_kwh = %d\n",p_cmd_code_0x92OutPt[3].Use_kwh );
	printf ( "**************** p_cmd_code_0x92OutPt[4].Use_kwh = %d\n",p_cmd_code_0x92OutPt[4].Use_kwh );

    //printf("************************* the num of recode : fgets_count_num = %d",fgets_count_num);

	// total number of history in the historyfile
	return TempHistoryInsertCount;

}



