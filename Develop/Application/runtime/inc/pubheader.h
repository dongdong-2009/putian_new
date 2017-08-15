/*
 * pubheader.h
 *
 *  Created on: 2013-9-16
 *      Author: lijb
 */

#ifndef PUBHEADER_H_
#define PUBHEADER_H_

#include <pthread.h>
#include<time.h>  
#include<sys/time.h>


#if 0
#define BMS_INTER_INIT	(0)
#define BMS_INTER_OK	(1)
#define ERR_CMD512		(2)
#define ERR_CMD1536		(3)
#define ERR_CMD2304		(4)
#define ERR_CMD4352		(5)
#define ERR_CMD4096		(6)
#define ERR_CM6400		(7)
#define ERR_CMD7168		(8)

#define ERR_CMD256_00		(9)
#define ERR_CMD256_AA		(10)
#define ERR_CMD1792_2048		(11)
#define ERR_CMD2560			(12)
#define ERR_CMD4608			(13)
#define ERR_CM6656			(14)
#define ERR_CMD7424			(15)
#define EMERGENCY_PRESSED		(16)
#define  MODLEREPLYSTARTCMD_FAILE (17)
#endif


#ifndef	TRUE
	#define  TRUE (1)
#endif

#ifndef	FALSE
	#define  FALSE (0)
#endif

#ifndef	NULL
	#define NULL 	(void*)0
#endif

//whether the stub work need networksupport
#define  WORK_WITHOUTNETWORK   (0)
#define  WORK_WITHNETWORK   (1)

#define BUFFERLEN_32   (32)
#define INIFILE_LININBUF_SIZE (256)
//five millisecond delay
#define  ONEMSC   (1000)
#define DELAYTM_BYMSEC_5 	(5)
//TEN millisecond delay
#define DELAYTM_BYMSEC_10 	(10)
//20 millisecond delay
#define DELAYTM_BYMSEC_20 	(20)

//30 millisecond delay
#define DELAYTM_BYMSEC_30 	(30)

//40 millisecond delay
#define DELAYTM_BYMSEC_40 	(40)

//50 millisecond delay
#define DELAYTM_BYMSEC_50 	(50)
//100 millisecond delay
#define DELAYTM_BYMSEC_200 	(200)

#pragma pack(push) //
#pragma pack(1)

union _type_int
{

	unsigned int int_value;
	unsigned char value_buff[4];
	
};

union _type_short
{

	short  short_value;
	unsigned char value_buff[2];
	
};

typedef struct SYNCHRO_TIME
{
	unsigned short uwYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned char ucReserve;
} SYNCHRO_TIME_S;



enum
{
	HIGH_1=0,
	PEAK_1,
	FLAT_1,
	LOW_1,
	HIGH_2,
	PEAK_2,
	FLAT_2,
	LOW_2,
	MAXPERIOD_NUM,
	
};

struct _ElecPriceSet_Struct
{
	float starttm_high_1;
	float stoptm_high_1;
	float per_high_1;
	float starttm_peak_1;
	float stoptm_peak_1;
	float per_peak_1;
	float starttm_flat_1;
	float stoptm_flat_1;
	float per_flat_1;
	float starttm_low_1;
	float stoptm_low_1;
	float per_low_1;
	float starttm_high_2;
	float stoptm_high_2;
	float per_high_2;
	float starttm_peak_2;
	float stoptm_peak_2;
	float per_peak_2;
	float starttm_flat_2;
	float stoptm_flat_2;
	float per_flat_2;
	float starttm_low_2;
	float stoptm_low_2;
	float per_low_2;
};


extern float  setstarttm[MAXPERIOD_NUM];
extern float  setstoptm[MAXPERIOD_NUM];
extern float  perprice[MAXPERIOD_NUM];
extern unsigned char  getstarttm_flag[MAXPERIOD_NUM];
//unsigned char  getstarttm_flag[MAXPERIOD_NUM];
//unsigned char  getstarttm_flag[MAXPERIOD_NUM];
struct _ElecPrice_Struct
{
	unsigned char flagGethighStartTm_1;
	struct timeval highstarttm_1;
	struct timeval highnowtm_1;
	unsigned char flaggethigh_startEnegy_1;
	float high_startEnegy_1;
	float high_nowEnegy_1;
	
	unsigned char flagGetpeakStartTm_1;
	struct timeval peakstarttm_1;
	struct timeval peaknowtm_1;
	unsigned char flaggetpeak_startEnegy_1;
	float peak_startEnegy_1;
	float peak_nowEnegy_1;

	unsigned char flagGetflatStartTm_1;
	struct timeval flatstarttm_1;
	struct timeval flatnowtm_1;
	unsigned char flaggetflat_startEnegy_1;
	float flat_startEnegy_1;
	float flat_nowEnegy_1;

	unsigned char flagGetlowStartTm_1;
	struct timeval lowstarttm_1;
	struct timeval lownowtm_1;
	unsigned char flaggetlow_startEnegy_1;
	float low_startEnegy_1;
	float low_nowEnegy_1;

	unsigned char flagGethighStartTm_2;
	struct timeval highstarttm_2;
	struct timeval highnowtm_2;
	unsigned char flaggethigh_startEnegy_2;
	float high_startEnegy_2;
	float high_nowEnegy_2;
	
	unsigned char flagGetpeakStartTm_2;
	struct timeval peakstarttm_2;
	struct timeval peaknowtm_2;
	unsigned char flaggetpeak_startEnegy_2;
	float peak_startEnegy_2;
	float peak_nowEnegy_2;

	unsigned char flagGetflatStartTm_2;
	struct timeval flatstarttm_2;
	struct timeval flatnowtm_2;
	unsigned char flaggetflat_startEnegy_2;
	float flat_startEnegy_2;
	float flat_nowEnegy_2;

	unsigned char flagGetlowStartTm_2;
	struct timeval lowstarttm_2;
	struct timeval lownowtm_2;
	unsigned char flaggetlow_startEnegy_2;
	float low_startEnegy_2;
	float low_nowEnegy_2;
};
#pragma pack(pop)//
/*
enum _event
{
	startup = 1,
	shut_down,//???
	checkself,//???
	rfidcard,
	charge_start,
	charge_stop,
	repair,//???
	update,//???
	parameter,//parameter changed by outorder ???
	data_patch,//0x78
	history_delete,//???
	history_output//???
}event;
*/
struct  _MYLOCK_STRUCT
{
	 unsigned char  ReadLock_EmergencyState;
	 unsigned char  ReadLock_ModuleInter;
	 unsigned char  ReadLock_NetWorkInter;
	 
};


extern struct _mutex_lock_struct mutex_lock_struct;
extern struct _devicesate_watch devicesate_watch;
#endif /* PUBHEADER_H_ */
