/*
 * ModuleCtl.h
 *
 *  Created on: 2013-9-6
 *      Author: LIJB
 */

#ifndef MODULECTL_H_
#define MODULECTL_H_

#include<time.h>  
#include<sys/time.h>
#include "pubheader.h"


#define MODULECTL_REPLY_SUCCESS  (0)
#define MODULECTL_REPLY_FAILED  (1)

#define MODULECTL_TXMAXLEN	(512)
#define MODULECTL_RXMAXLEN	(1024)

#define MODULECTL_STARTCHARGE  (1)
#define MODULECTL_STOPCHARGE  (2)



#define ModuleCtl_Cmd0x01	(0x01)
#define ModuleCtl_Cmd0x02	(0x02)	
//#define ModuleCtl_Cmd0x03	(0x03)
//#define ModuleCtl_Cmd0x04	(0x04)
//#define ModuleCtl_Cmd0x05	(0x05)
//#define ModuleCtl_Cmd0x06	(0x06)

#define  DATALEN_CMD0X01   (0x01)
#define  DATALEN_CMD0X02   (0x0B)
#define  DATALEN_CMD0X0F   (0x0E)


#define ModuleCtl_Cmd0x81	(0x81)
#define ModuleCtl_Cmd0x82	(0x82)
#define ModuleCtl_Cmd0x83	(0x83)
#define ModuleCtl_Cmd0x84	(0x84)
#define ModuleCtl_Cmd0x85	(0x85)
#define ModuleCtl_Cmd0x86	(0x86)
#define ModuleCtl_Cmd0x87	(0x87)
#define ModuleCtl_Cmd0x88	(0x88)
#define ModuleCtl_Cmd0x89	(0x89)
#define ModuleCtl_Cmd0x8A	(0x8A)
#define ModuleCtl_Cmd0x8B	(0x8B)
#define ModuleCtl_Cmd0x8C	(0x8C)
#define ModuleCtl_Cmd0x8D	(0x8D)
#define ModuleCtl_Cmd0x8E	(0x8E)
#define ModuleCtl_Cmd0x0F	(0x0F)

#define COMM_MODULE_FRAME_START	(0x68)
#define COMM_MODULE_FRAME_END	(0x16)

#define COMM_SLAVE_MODULE_ADDR                    (0x80)

#define COMM_HOST_MACHINE_ADDR                   (0x00)

struct _ModuleCtl_SndCmdManager
{
	//int SndCmd_0x01;
	int SndCmd_ModuleStart;
	int GetModule_Start_response;
	int SndCmd_ModuleStop;
	int GetModule_Stop_response;
	int SndCmd_0x02;
	int SndCmd_0x03;
	int SndCmd_0x04;
	int SndCmd_0x05;
	int SndCmd_0x0F;
	
};

#pragma pack(push) //
#pragma pack(1)


struct _ModuleCtl_struct0x01
{
	short DataLen;
	unsigned char Data;
};

struct _ModuleCtl_struct0x81
{
	short DataLen;
	unsigned char Data;
};

struct _ModuleCtl_struct0x02
{
	short DataLen;
	short OutPt_Volt;
	short  OutPt_Current;
	short  OutPt_Power;
	short  AllowSingleLarestVolt;
	short  AllowSingleLarestTemp;
	unsigned char PamaType;
	
};

struct _ModuleCtl_struct0x82
{
	short DataLen;
	unsigned char Data;
};

struct _ModuleCtl_struct0x03
{
	short DataLen;
	
};
struct _ModuleCtl_struct0x83
{
	short DataLen;
	unsigned char ModuleTotalNUmber;
	unsigned char ModuleAddress;
	short ACDCModuleErrorState[20];
	
};
struct _ModuleCtl_struct0x04
{
	short DataLen;
	
};
struct _ModuleCtl_struct0x84
{
	short DataLen;
	unsigned char WaringByte;
	short ACDC_LargestOutVolt;
	short ACDC_LittestOutVolt;
	short ACDC_LargestOutCurrent;
	unsigned char ChargeGunLinkState;
	short ACDC_ChrVolt;
	short ACDC_ChrCurrent;
	unsigned char  AC_DC_State;
	short ACDC_OutPt_ValidPower;
	short ACDC_OutPt_InValidPower;
	short  ACDC_OutPt_Power;
	short  ACDC_AllowSingleLarestVolt;
	short  ACDC_AllowSingleLarestTemp; 
	unsigned char  Reserve;
};
struct _ModuleCtl_struct0x05
{
	short DataLen;
	
};
struct _ModuleCtl_struct0x85
{
	short DataLen;
	short BMS_SingleCellAllowbigestVolt;
	short BMS_AllowbigestCurrent;
	short BMS_CellRatedCapa;
	short  BMS_AllowbigestTotalVolt;
	unsigned char  BMS_CellAllowbigestTemp;
	short BMS_AllCellElecState;
	short BMS_AllCellTotalVolt;
	unsigned char BMS_Total_SOH;

	short BigestSingleVoltGroupId; //????
	
	unsigned char BigestSingleVoltIndex;
	unsigned char BigestTemp; ///????
	unsigned char BigestTempIndex;
	unsigned char LittestTemp;//????
	unsigned char LittestTempIndex;

	unsigned char  ErrCell_VoltSocCurrentTemp;
	unsigned char ErrCell_LinkAllowChr;
	unsigned char BmsCommunicationVersion[3];
	//short  BmsCommunicationVersion_high;
	//unsigned char  BmsCommunicationVersion_Low;

	
	unsigned char  CellType;
	short RatedCapa;
	short RatedVolt;
	unsigned char FactoryId[4];
	unsigned char CellSerail[4];
	unsigned char CellProducedate_year;
	unsigned char CellProducedate_month;
	unsigned char CellProducedate_day;
	unsigned char CellChr_times[3];
	unsigned char CellPoperty_Id;
	unsigned char Reserve;
	//unsigned char Car_VIN[17];
	unsigned char Car_Infor[17];
	unsigned char Cell_reserve[16];
	
	
	unsigned char BmsErr_Spn2560;
	unsigned char BmsErr_TmSynBiestOutVoltReady;
	unsigned char BmsErr_ChrStateStop_TimeOut;
	unsigned char BmsErr_Statics_Timeout;
	unsigned char BmsErr_CarIdentify_TimeOut;
	unsigned char BmsErr_CellChrPama_Timeout;
	unsigned char BmsErr_CellTotalStateChrneed_Timeout;//????
	unsigned char BmsErr_Statics_timeout;

	unsigned char BMS_AlreadyCharge;
	unsigned char Stub_AlreadyCharge;
	unsigned char CU_StubAreaCode[6];
};
struct _ModuleCtl_struct0x86
{
	short DataLen;
	short ChrVoltMesurValue;
	short ChrCurrentMesurValue;
	unsigned char Total_SOC;
	short ChrLeftTm;
	short ChrUsedTm;
	short BMS_VoltNeed;
	short BMS_CurrentNeed;
	unsigned char ChrMode;
};
struct _ModuleCtl_struct0x87
{
	short DataLen;
	unsigned char  Stop_Soc;
	short SingleLittesetVolt;//????
	short SingleBigesetVolt;

   	unsigned char  PowerCellLittestTemp;
	unsigned char  PowerCellBigestTemp;
	short ChrUsed_Power;
	unsigned char CU_index;
	unsigned char WhichDeviceFrtStopChrg;
	
	unsigned char Bms_StopChrReson;
	short    Bms_StopChrBreakDown_Reson;
	unsigned char Bms_StopChrErrrReson;
	
	unsigned char CU_StopChrReson;
	short    CU_StopChrBreakDown_Reson;
	unsigned char CU_StopChrErrrReson;
	
	short StopState;
	
	
};

struct _BMS_Volt_checkValue
{
	short  BMS_CellCheckValue;
	short  BMS_CellCheckValue_pos;
	
};

struct _BMS_Temp_checkValue
{
	unsigned char  BMS_CellCheckValue;
	short  BMS_CellCheckValue_pos;
	
};
struct _ModuleCtl_struct0x88
{
	short DataLen;
	
	unsigned char WorkStep; //0001 shake hand  0010 seting step .........
	unsigned char LifeValue;
	unsigned char  ChrGunLinkState;
	struct _BMS_Volt_checkValue  BMS_Volt_checkValue_high[2];
	struct _BMS_Volt_checkValue  BMS_Volt_checkValue_low[2];
	struct _BMS_Temp_checkValue BMS_Temp_checkValue_high[4];
	struct _BMS_Temp_checkValue BMS_Temp_checkValue_low[4];
	unsigned char PotevioCommunicationVersion[3];
	unsigned char Car_VIN[17];
	unsigned char CellBoxNumber;
	unsigned char CellSerialNumber;
	unsigned char CellParallelNumber; 
	unsigned char TempGetpoint;
	unsigned char  CellManagerSystem_ID[8];
	unsigned char   CellBoxSerailNumber[20][8];
};
struct _ModuleCtl_struct0x89
{
	short DataLen;
	unsigned char CellTotalNumber;
	short  SingleCellvolt[50];
};
struct _ModuleCtl_struct0x8A
{
	short DataLen;
	unsigned char CellTotalNumber;
	short  SingleCellvolt[50];
};
struct _ModuleCtl_struct0x8B
{
	short DataLen;
	unsigned char CellTotalNumber;
	short  SingleCellvolt[50];
};
struct _ModuleCtl_struct0x8C
{
	short DataLen;
	unsigned char CellTotalNumber;
	short  SingleCellvolt[50];
};
struct _ModuleCtl_struct0x8D
{
	short DataLen;
	unsigned char  CellTempCheckPointNum;
	unsigned char   CellTempValue[200];
};

struct _MdCellSystemErrorInfor
{
	unsigned char CellErrorGroup_ID;
	unsigned char CellErrorgrade;
	unsigned char CellErrorCode;
	unsigned char CellErrorPosTotal;
	short CellErrorPos[10];
	unsigned char CellErrorEnd;
	
};
struct _LowSingleVolt_Struct
{
	short  LowSingleVolt;
	short  LowSingleVolt_pos;
	
};
struct _ModuleCtl_struct0x8E
{
	short DataLen;
	
	struct _MdCellSystemErrorInfor CellErrorInfor;
	struct _MdCellSystemErrorInfor CellSysTemTotalErrorInfor;
	struct _MdCellSystemErrorInfor BmsErrorInfor;
	
	//unsigned char ErrorInfor[128];
	
};
struct _ModuleCtl_struct0x8F
{
	short DataLen;
	unsigned char TimeBuf[14];
};
typedef struct _ModuleCtl_DataStruct
{
	struct _ModuleCtl_struct0x01 ModuleCtl_struct0x01;
	struct _ModuleCtl_struct0x81 ModuleCtl_struct0x81;

	struct _ModuleCtl_struct0x02 ModuleCtl_struct0x02;
	struct _ModuleCtl_struct0x82 ModuleCtl_struct0x82;

	//struct _ModuleCtl_struct0x03 ModuleCtl_struct0x03;
	struct _ModuleCtl_struct0x83 ModuleCtl_struct0x83;

	//struct _ModuleCtl_struct0x04 ModuleCtl_struct0x04;
	struct _ModuleCtl_struct0x84 ModuleCtl_struct0x84;

	//struct _ModuleCtl_struct0x05 ModuleCtl_struct0x05;
	struct _ModuleCtl_struct0x85 ModuleCtl_struct0x85;
	struct _ModuleCtl_struct0x86 ModuleCtl_struct0x86;
	struct _ModuleCtl_struct0x87 ModuleCtl_struct0x87;
	struct _ModuleCtl_struct0x88 ModuleCtl_struct0x88;
	struct _ModuleCtl_struct0x89 ModuleCtl_struct0x89;
	struct _ModuleCtl_struct0x8A ModuleCtl_struct0x8A;
	struct _ModuleCtl_struct0x8B ModuleCtl_struct0x8B;
	struct _ModuleCtl_struct0x8C ModuleCtl_struct0x8C;
	struct _ModuleCtl_struct0x8D ModuleCtl_struct0x8D;
	struct _ModuleCtl_struct0x8E ModuleCtl_struct0x8E;
	struct _ModuleCtl_struct0x8F ModuleCtl_struct0x8F;
	
}	MODULECTLDATASTRUCT,*P_MODULECTLDATASTRUCT;
#pragma pack(pop)//

int PackHead(unsigned char *acSendBuf,unsigned int BufLen,unsigned int CmdCode);
unsigned int GetModuleInfo(unsigned char *RevModuleData, int DataLen,P_MODULECTLDATASTRUCT ModuleCtlDataIPt);
//static unsigned char Comm_CheckSum(unsigned char *pucCheckDate, unsigned char ucLength);
int PackModuleCtl_Cmd0x01(unsigned char *acSendBuf,unsigned int  BufLen,unsigned int ulCmd,P_MODULECTLDATASTRUCT ModuleCtlDataIPt);
int PackModuleCtl_Cmd0x02(unsigned char *acSendBuf,unsigned int  BufLen,unsigned int ulCmd,P_MODULECTLDATASTRUCT ModuleCtlDataIPt);
int PackModuleCtl_Cmd0x03(unsigned char *acSendBuf,unsigned int  BufLen,unsigned int ulCmd,P_MODULECTLDATASTRUCT ModuleCtlDataIPt);
int PackModuleCtl_Cmd0x04(unsigned char *acSendBuf,unsigned int  BufLen,unsigned int ulCmd,P_MODULECTLDATASTRUCT ModuleCtlDataIPt);
int PackModuleCtl_Cmd0x05(unsigned char *acSendBuf,unsigned int  BufLen,unsigned int ulCmd,P_MODULECTLDATASTRUCT ModuleCtlDataIPt);
int PackModuleCtl_Cmd0x8F(unsigned char *acSendBuf,unsigned int  BufLen,unsigned int ulCmd,P_MODULECTLDATASTRUCT ModuleCtlDataIPt);
unsigned int AnalisisModuleInfo(unsigned char *RevModuleData, int DataLen,P_MODULECTLDATASTRUCT ModuleCtlDataIPt);
void GetsysTime(SYNCHRO_TIME_S *OutStrctTm);
void CheckModulePackSnd();
#endif /* MODULECTL_H_ */
