/**
 * @file can_fd.h
 * @brief
 * @author zk
 * @date 2023��08��14��
 * @version
 * @copyright (c) Copyright 2020-2040, Wanbang New Energy Investment Co.,LTD.
 *                       All Rights Reserved
 ***********************************************************************************
 * @attention
 * @par �޸���־:
 * <table>
 * <tr><th>Date        <th>Version         <th>Author         <th>Description
 * </table>
 ***********************************************************************************
 */

#ifndef __CAN_FD_H__
#define __CAN_FD_H__	 

#ifdef __cplusplus
extern "C" {
#endif
	
#include "sys.h"
#include "stdio.h"
#include "NuMicro.h"



/********************************************************************************
*                                   Function Declaration
********************************************************************************/
Std_ReturnType Can_ChangeBaudrate(uint8_t Controller, const uint16_t baudrate);
void Can_GetVersionInfo(Std_VersionInfoType *version);
void Can_Init(const Can_ConfigType *Config);
Can_ReturnType Can_Read(uint8_t Controller, Can_PduType *PduInfo);
Can_ReturnType Can_Write(uint8_t Controller, const Can_PduType *PduInfo);

#ifdef __cplusplus
}
#endif

#endif /*__CAN_FD_H__*/
