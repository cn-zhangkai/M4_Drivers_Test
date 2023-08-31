/**
 * @file    watchdog.h
 * @brief   driver of the window watchdog
 * @author  zk
 * @date    2023年08月09日
 * @version
 * @copyright (c) Copyright 2020-2040, Wanbang New Energy Investment Co.,LTD.
 *                       All Rights Reserved
 ***********************************************************************************
 * @attention
 * @par 修改日志:
 * <table>
 * <tr><th>Date            <th>Version         <th>Author         <th>Description
 * <tr><th>2023.08.09      <th>V1.0            <th>zk             <th>初版 
 *</table>
 ***********************************************************************************
 */

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__	 

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdio.h>
#include "NuMicro.h"

void WWDT_init(void);
void KickDog(void);

#ifdef __cplusplus
}
#endif

#endif //__WATCHDOG_H__
