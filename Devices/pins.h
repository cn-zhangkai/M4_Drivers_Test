/**
 * @file pins.h
 * @brief 
 * @author zk
 * @date 2023年08月24日
 * @version
 * @copyright (c) Copyright 2023-2040, Wanbang New Energy Investment Co.,LTD.
 *                       All Rights Reserved
 ***********************************************************************************
 * @attension
 * Environment:
 * @par 修改日志:
 * <table>
 * <tr><th>Date            <th>Version                 <th>Author       <th>Description
 * <tr><td>2022.08.24      <td>V1.0                     <td>zk          <td>初版
 * </table>
 ***********************************************************************************
 */
#ifndef __PINS_H__

#define __PINS_H__
#ifdef __cplusplus

extern "C" {
#endif


/********************************************************************************
*                                    Include files
********************************************************************************/
#include "NuMicro.h"



/********************************************************************************
*                                    Struct   Union  Declaration
********************************************************************************/
/* 根据原理图定义分配给M4引脚对应的信号 */
#define JOUT1_Pin                 BIT8
#define JOUT1_GPIO_Port           PB

#define JOUT2_Pin                 BIT9
#define JOUT2_GPIO_Port           PB

#define EN_DISCHARGE_Pin          BIT10
#define EN_DISCHARGE_GPIO_Port    PB

#define EN_DC_AUX_Pin             BIT11
#define EN_DC_AUX_GPIO_Port       PB

#define ACJOUT_Pin                BIT12
#define ACJOUT_GPIO_Port          PB

#define ACJOUT_F_Pin              BIT0
#define ACJOUT_F_GPIO_Port        PM

#define LED_DOUT_Pin              BIT13
#define LED_DOUT_GPIO_Port        PB

#define LED_DOUT1_Pin             BIT14
#define LED_DOUT1_GPIO_Port       PB

#define FAN_FAULT1_Pin            BIT1
#define FAN_FAULT1_GPIO_Port      PM

#define FAN_FAULT2_Pin            BIT2
#define FAN_FAULT2_GPIO_Port      PM

#define FAN_FAULT3_Pin            BIT3
#define FAN_FAULT3_GPIO_Port      PM

#define FAN_FAULT4_Pin            BIT4
#define FAN_FAULT4_GPIO_Port      PM

#define FAN_FAULT5_Pin            BIT5
#define FAN_FAULT5_GPIO_Port      PM

#define DSP_FAULT_O_Pin           BIT6
#define DSP_FAULT_O_GPIO_Port     PM

#define ARM_FAULT_Pin             BIT7
#define ARM_FAULT_GPIO_Port       PM

#define DIG1_Pin                  BIT8
#define DIG1_GPIO_Port            PM

#define FF_Pin                    BIT9
#define FF_GPIO_Port              PM

#define DO1_Pin                   BIT15
#define DO1_GPIO_Port             PB

#define JD0_DET_Pin               BIT10
#define JD0_DET_GPIO_Port         PM

#define JD1_DET_Pin               BIT11
#define JD1_DET_GPIO_Port         PM

#define CAL_Pin                   BIT12
#define CAL_GPIO_Port             PM

#define TRIP_Pin                  BIT13
#define TRIP_GPIO_Port            PM

#define TEST_Pin                  BIT14
#define TEST_GPIO_Port            PM

#define nTRST_Pin                 BIT15
#define nTRST_GPIO_Port           PG

#define SWCLK_Pin                 BIT12
#define SWCLK_GPIO_Port           PG

#define SWDIO_Pin                 BIT13
#define SWDIO_GPIO_Port           PG

#define CAN1_RXD_Pin              BIT6
#define CAN1_GPIO_Port            PG

#define CAN1_TXD_Pin              BIT7
#define CAN1_GPIO_Port            PG

#define CAN0_RXD_Pin              BIT2
#define CAN0_GPIO_Port            PG

#define CAN0_TXD_Pin              BIT3
#define CAN0_GPIO_Port            PG

#define FAN_PWM_Pin               BIT8
#define FAN_PWM_GPIO_Port         PD
/********************************************************************************
*                                   Global data Declaration
********************************************************************************/





/********************************************************************************
*                                   Function Declaration
********************************************************************************/





#ifdef __cplusplus
}
#endif

#endif  // __PINS_H__
/********************************************************************************
 * Copyright (c) 2020-2040 Star Charge. * All rights reserved.
 ********************************************************************************
 * End of this File (EOF):
 * !!!!!!Do not put anything after this part!!!!!!!!!!! ************************/

