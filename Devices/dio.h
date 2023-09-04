/**
 * @file dio.h
 * @brief  driver of the dio
 * @author zk
 * @date 2023年08月07日
 * @version
 * @copyright (c) Copyright 2023-2040, Wanbang New Energy Investment Co.,LTD.
 *                       All Rights Reserved
 ***********************************************************************************
 * @attention
 * @par 修改日志:
 * <table>
 * <tr><th>Date            <th>Version         <th>Author         <th>Description
 * <tr><th>2023.08.07      <th>V1.0            <th>zk             <th>初版
 *</table>
 ***********************************************************************************
 */

#ifndef __DIO_H__
#define __DIO_H__	 

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdio.h>
//#include <vector>
#include "NuMicro.h"

typedef enum
{
    LOW_LEVEL = 0U,
    HIGH_LEVEL,
}Dio_LevelType;

typedef struct
{
	char      *ProductName;
	char      SampleName;
	uint8_t   MajorVerNum;
	uint8_t   MinorVerNum;
	char      *Date;
}Std_VersionInfoType;//{"7.kKW",'A', 1, 1, "2023.08.07"};

typedef struct
{
    uint32_t      u32ModuleIdx;
	GPIO_T        *Port;
	uint32_t      u32PinMask;
	uint32_t      u32Mode;
	Dio_LevelType DioSta;
}Dio_ConfigType;

typedef struct
{
	GPIO_T        *Port;
	uint32_t      u32PinMask;
}Dio_ChannelType;

/********************************************************************************
*                                   Function Declaration
********************************************************************************/
void Dio_GetVersionInfo(Std_VersionInfoType* version);
void Dio_Init(const Dio_ConfigType* ConfigPtr);
Dio_LevelType Dio_ReadChannel(Dio_ChannelType channnel);
void Dio_WriteChannel(Dio_ChannelType channnel, Dio_LevelType level);

#ifdef __cplusplus
}
#endif

#endif /*__DIO_H__*/
