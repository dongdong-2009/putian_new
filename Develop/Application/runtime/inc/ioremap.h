/* filename.c(.cpp)/.h(.hpp)
** 文件功能简述
**
** 错误反馈：andy2003du1984@163.com
**
** 作者：
**	杜鹏(Andrew)	07/06/2013
**	商业软件，保留一切权利
** 修改：
**
** http://www.andrew-sh.com
*/


#ifndef IOREMAP_H_
#define IOREMAP_H_


/*
 *  < BOOL REMAP SECTION >
 */
#define     PL_DATABASE_BOOL_START              DATABASE_BOOL_000
#define     PL_GETMAINCARD_FLAG                 DATABASE_BOOL_000
#define     PL_CHRGUNLINKERR_FLAG               DATABASE_BOOL_001
#define     PL_NETWORKLINKSTATE_FLAG            DATABASE_BOOL_002
#define     PL_NEEDNETWORK_FLAG                 DATABASE_BOOL_003
//#define   PL_CHRPASSWRDERR_FLAG               DATABASE_BOOL_004
//#define   PL_SETPASSWRDERR_FLAG               DATABASE_BOOL_005
#define     PL_CHRGUNLINK_FLAG                  DATABASE_BOOL_004
#define     PL_APPOINT_FLAG                     DATABASE_BOOL_005
#define     PL_BACK_FLAG                        DATABASE_BOOL_006
#define     PL_CONNECT_ERR_FLAG                 DATABASE_BOOL_007
#define     PL_MONEY_LEFT_FLAG                  DATABASE_BOOL_008
#define     PL_APP_FLAG                         DATABASE_BOOL_009
#define     PL_DATABASE_BOOL_STOP               DATABASE_BOOL_009


/*
 *  < UINT8 REMAP SECTION >
 */
#define     PL_DATABASE_UINT8_START             DATABASE_UINT8_000
#define     PL_HMI_PAGE_INDEX                   DATABASE_UINT8_000
#define     PL_HMI_BUTTON_DOWN                  DATABASE_UINT8_001
#define     PL_HMI_CHARG_BY_TIME_TYPE           DATABASE_UINT8_002
#define     PL_HMI_CHARG_BY_ENERGY_TYPE         DATABASE_UINT8_003
#define     PL_HMI_PAGE_INDEX_CUR               DATABASE_UINT8_004
#define     PL_CHRERROR_STATE                   DATABASE_UINT8_005
#define     PL_CHRPASSWRDERR_FLAG               DATABASE_UINT8_006
#define     PL_SETPASSWRDERR_FLAG               DATABASE_UINT8_007
#define     PL_CELLTYPE_FLAG                    DATABASE_UINT8_008
#define     PL_CHRPROCESSCHECK_FLAG             DATABASE_UINT8_009
#define     PL_LITTLEWINDOWFUC_FLAG             DATABASE_UINT8_010
#define     PL_CARDPROMPT_FLAG                  DATABASE_UINT8_011
#define     PL_CHRGUNLINKSTATE_FLAG             DATABASE_UINT8_012
#define     PL_HMI_CHARG_BY_MONEY_TYPE          DATABASE_UINT8_013
#define     PL_HMI_CHARG_TYPE                   DATABASE_UINT8_014
#define     PL_HISTORY_CHECK                    DATABASE_UINT8_015
#define     PL_MAIN_GUNNUM                      DATABASE_UINT8_016

#define     PL_AC_STATE_1                       DATABASE_UINT8_017
#define     PL_AC_STATE_2                       DATABASE_UINT8_018
#define     PL_TitleWaring_FLAG                 DATABASE_UINT8_019
#define     PL_GunWaring_FLAG                   DATABASE_UINT8_020
#define     PL_ERROR_TXT_FLAG                   DATABASE_UINT8_021
#define     PL_Account_Money_use_FLAG           DATABASE_UINT8_022
#define     PL_TYPE_ERROR_TXT_FLAG              DATABASE_UINT8_023
#define     PL_SERVICE_OPEN_FLAG                DATABASE_UINT8_024

#define     PL_WARING_VALUE                     DATABASE_UINT8_025
#define     PL_SWIPECARD_MENTIONVALUE           DATABASE_UINT8_026

#define     PL_DATABASE_UINT8_STOP              DATABASE_UINT8_026

/*
 *  < UINT16 REMAP SECTION >
 */
#define     PL_DATABASE_UINT16_START            DATABASE_UINT16_000
#define     PL_CHRTOTALUSE_TIME                 DATABASE_UINT16_000
#define     PL_CHR_STATE                        DATABASE_UINT16_001
#define     PL_CHR_STATRTSOC                    DATABASE_UINT16_002
#define     PL_CHR_CURRENTSOC                   DATABASE_UINT16_003
#define     PL_CHR_STOPSOC                      DATABASE_UINT16_004
#define     PL_CHR_LFTTIME                      DATABASE_UINT16_005
#define     PL_GETNEEDCHARGUNNUM                DATABASE_UINT16_006

#define     PL_AC_CHR_TIME_1                    DATABASE_UINT16_007
#define     PL_AC_CHR_TIME_2                    DATABASE_UINT16_008
#define     PL_GETNEEDSTOPGUNNUM                DATABASE_UINT16_009

#define     PL_DATABASE_UINT16_STOP             DATABASE_UINT16_009

/*
 *  < FLOAT32  REMAP SECTION >
 */
#define     PL_DATABASE_FLOAT32_START           DATABASE_FLOAT32_000
#define     PL_MAINCARD_LEFTMONEY               DATABASE_FLOAT32_000
#define     PL_CHRUSED_TOTALMONEY               DATABASE_FLOAT32_001
#define     PL_CHROUTPT_VOLT                    DATABASE_FLOAT32_002
#define     PL_CHROUTPT_CURRENT                 DATABASE_FLOAT32_003
#define     PL_CHRSTART_KWH                     DATABASE_FLOAT32_004
#define     PL_CHRCURRRENT_KWH                  DATABASE_FLOAT32_005
#define     PL_CHRUSED_KWH                      DATABASE_FLOAT32_006
#define     PL_LOWESTCELL_TEMP                  DATABASE_FLOAT32_007
#define     PL_HIGESTCELL_TEMP                  DATABASE_FLOAT32_008
#define     PL_OUTPUT_POWER                     DATABASE_FLOAT32_009
#define     PL_CHARGESEVICE_MONEY               DATABASE_FLOAT32_010
#define     PL_ELECTRIC_MONEY                   DATABASE_FLOAT32_011
#define     PL_SINGLE_HIGHVOLT                  DATABASE_FLOAT32_012
#define     PL_SINGLE_LOWVOLT                   DATABASE_FLOAT32_013
#define     PL_MODULE_HIGH_TEMP                 DATABASE_FLOAT32_014
#define     PL_TOP1_ELECPRICE                   DATABASE_FLOAT32_015
#define     PL_TOP1_STARTTM                     DATABASE_FLOAT32_016
#define     PL_TOP1_STOPTM                      DATABASE_FLOAT32_017
#define     PL_PEAK1_ELECPRICE                  DATABASE_FLOAT32_018
#define     PL_PEAK1_STARTTM                    DATABASE_FLOAT32_019
#define     PL_PEAK1_STOPTM                     DATABASE_FLOAT32_020
#define     PL_FLAT1_ELECPRICE                  DATABASE_FLOAT32_021
#define     PL_FLAT1_STARTTM                    DATABASE_FLOAT32_022
#define     PL_FLAT1_STOPTM                     DATABASE_FLOAT32_023
#define     PL_VALLEY1_ELECPRICE                DATABASE_FLOAT32_024
#define     PL_VALLEY1_STARTTM                  DATABASE_FLOAT32_025
#define     PL_VALLEY1_STOPTM                   DATABASE_FLOAT32_026
#define     PL_TOP2_ELECPRICE                   DATABASE_FLOAT32_027
#define     PL_TOP2_STARTTM                     DATABASE_FLOAT32_028
#define     PL_TOP2_STOPTM                      DATABASE_FLOAT32_029
#define     PL_PEAK2_ELECPRICE                  DATABASE_FLOAT32_030
#define     PL_PEAK2_STARTTM                    DATABASE_FLOAT32_031
#define     PL_PEAK2_STOPTM                     DATABASE_FLOAT32_032
#define     PL_FLAT2_ELECPRICE                  DATABASE_FLOAT32_033
#define     PL_FLAT2_STARTTM                    DATABASE_FLOAT32_034
#define     PL_FLAT2_STOPTM                     DATABASE_FLOAT32_035
#define     PL_VALLEY2_ELECPRICE                DATABASE_FLOAT32_036
#define     PL_VALLEY2_STARTTM                  DATABASE_FLOAT32_037
#define     PL_VALLEY2_STOPTM                   DATABASE_FLOAT32_038

#define     PL_AC_VOLT_1                        DATABASE_FLOAT32_039
#define     PL_AC_VOLT_2                        DATABASE_FLOAT32_040
#define     PL_AC_CURRENT_1                     DATABASE_FLOAT32_041
#define     PL_AC_CURRENT_2                     DATABASE_FLOAT32_042
#define     PL_AC_KWH_1                         DATABASE_FLOAT32_043
#define     PL_AC_KWH_2                         DATABASE_FLOAT32_044

#define     PL_DATABASE_FLOAT32_STOP            DATABASE_FLOAT32_044


//[ARRAY]
#define     PL_DATABASE_ARRAY_START             DATABASE_ARRAY_000
#define     PL_MAINCARD_SN                      DATABASE_ARRAY_000
#define     PL_CHR_STARTTIME                    DATABASE_ARRAY_001
#define     PL_CHR_STOPTIME                     DATABASE_ARRAY_002
#define     PL_HMI_CARD_PASSWD                  DATABASE_ARRAY_003
#define     PL_CHRTOTALUSE_TIME_ARRAY           DATABASE_ARRAY_004
#define     PL_SETPAGE_PASSWD                   DATABASE_ARRAY_005
#define     PL_BOOKCARD_SN                      DATABASE_ARRAY_006
#define     PL_GUEST_NAME                       DATABASE_ARRAY_007
#define     PL_SOFT_TIME                        DATABASE_ARRAY_008
#define     PL_HMI_CAR_NUM                      DATABASE_ARRAY_009
#define     PL_0x69_NAME                        DATABASE_ARRAY_010
#define     PL_DATABASE_ARRAY_STOP              DATABASE_ARRAY_010

//銆恥32銆慳dd by mj_1_29
#define     PL_DATABASE_U32_START               DATABASE_UINT32_000

#define     PL_STUBERRSTATE_FLAG                DATABASE_UINT32_000
#define     PL_BOOKDOWN_TIME                    DATABASE_UINT32_001
#define     PL_BOOKSTART_TIME                   DATABASE_UINT32_002
#define     PL_BOOKCARD_ERR                     DATABASE_UINT32_003

#define     PL_DATABASE_U32_STOP                DATABASE_UINT32_003
/*
 *  <OHTERS REMAP>
 */
#define     DB_ARRARY_TYPE_BUFFER_LEN           150
#define     DEV_MAX_DEVICE_NUMBER               6
#define     DEV_MAX_SLOT_NUMBER                 6
#define     SOFTWARE_MAX_SLOT_NUMBER            (DEV_MAX_DEVICE_NUMBER*DEV_MAX_SLOT_NUMBER)


#endif /* IOREMAP_H_ */











