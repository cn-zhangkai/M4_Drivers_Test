/**
 * @file dio.c
 * @brief
 * @author zk
 * @date 2023年08月07日
 * @version
 * @copyright (c) Copyright 2020-2040, Wanbang New Energy Investment Co.,LTD.
 *                       All Rights Reserved
 ***********************************************************************************
 * @attention
 * @par 修改日志:
 * <table>
 * <tr><th>Date        <th>Version         <th>Author         <th>Description
 * </table>
 ***********************************************************************************
 */
 
/********************************************************************************
*                                    Include files
********************************************************************************/
#include "dio.h"
#include "NuMicro.h"
#include "pins.h"

/**
 * @brief Get the version information of DIO drivers
 *
 * @param[in] version
 *
 * @return void
 *
 * @details 
 */
 
void Dio_GetVersionInfo(Std_VersionInfoType* version)
{
    printf("# Get the version information of DIO drivers: \n");
    printf("    - The current application product is %s \n",version -> ProductName);
    printf("    - The current sample stage is %c sample \n", version -> SampleName);
    printf("        and the driver version now is %d.%d \n", version -> MajorVerNum, version -> MinorVerNum);
    printf("    - Last modified date:%s \n", version -> Date);  
}

/**
 * @brief Init DIO
 *
 * @param[in] ConfigPtr
 *
 * @return void 
 *
 * @details 根据Dio_ConfigType设置相应的DIO或者多功能模式（CAN, SWD）？
 *          u32ModuleIdx
 *          模块的寄存器偏移
 *          所属端口
 *          端口位
 *          多功能模式
 */

void Dio_Init(const Dio_ConfigType* ConfigPtr)
{
	/* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable IP clock */
    CLK_EnableModuleClock(GPB_MODULE);
    CLK_EnableModuleClock(GPD_MODULE);
    CLK_EnableModuleClock(GPG_MODULE);
	CLK_EnableModuleClock(GPM_MODULE);
    
	//无需再使能对应GPIO的时钟
	//CLK_EnableModuleClock(TMR0_MODULE);
	//CLK_SetModuleClock(CANFD0_MODULE, CLK_CLKSEL4_CANFD0SEL_APLL, 0);
    //CLK_EnableModuleClock(CANFD0_MODULE);
	
    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set multi-function pins */
	SYS->GPB_MFPH = SYS_GPB_MFPH_PB15MFP_GPIO | SYS_GPB_MFPH_PB14MFP_GPIO | 
	                SYS_GPB_MFPH_PB13MFP_GPIO | SYS_GPB_MFPH_PB12MFP_GPIO | 
	                SYS_GPB_MFPH_PB11MFP_GPIO | SYS_GPB_MFPH_PB10MFP_GPIO | 
	                SYS_GPB_MFPH_PB9MFP_GPIO | SYS_GPB_MFPH_PB8MFP_GPIO;
    
	SYS->GPD_MFPH = SYS_GPD_MFPH_PD8MFP_TM0;
	
    SYS->GPG_MFPH = SYS_GPG_MFPH_PG15MFP_JTAG_nTRST | SYS_GPG_MFPH_PG13MFP_SW_DIO | 
	                SYS_GPG_MFPH_PG12MFP_SW_CLK;
    SYS->GPG_MFPL = SYS_GPG_MFPL_PG7MFP_CAN1_TXD | SYS_GPG_MFPL_PG6MFP_CAN1_RXD | 
	                SYS_GPG_MFPL_PG3MFP_CAN0_TXD | SYS_GPG_MFPL_PG2MFP_CAN0_RXD;
	
	SYS->GPM_MFPH = SYS_GPM_MFPH_PM14MFP_GPIO | SYS_GPM_MFPH_PM13MFP_GPIO | 
	                SYS_GPM_MFPH_PM12MFP_GPIO | SYS_GPM_MFPH_PM11MFP_GPIO | 
					SYS_GPM_MFPH_PM10MFP_GPIO | SYS_GPM_MFPH_PM9MFP_GPIO | 
					SYS_GPM_MFPH_PM8MFP_GPIO;
    SYS->GPM_MFPL = SYS_GPM_MFPL_PM7MFP_GPIO | SYS_GPM_MFPL_PM6MFP_GPIO | 
	                SYS_GPM_MFPL_PM5MFP_GPIO | SYS_GPM_MFPL_PM4MFP_GPIO | 
					SYS_GPM_MFPL_PM3MFP_GPIO | SYS_GPM_MFPL_PM2MFP_GPIO | 
					SYS_GPM_MFPL_PM1MFP_GPIO | SYS_GPM_MFPL_PM0MFP_GPIO;
					
    /* Lock protected registers */
    SYS_LockReg();
	
	/* 设置DIO输入输出模式 */
    GPIO_SetMode(ACJOUT_F_GPIO_Port, ACJOUT_F_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(FAN_FAULT1_GPIO_Port, FAN_FAULT1_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(FAN_FAULT2_GPIO_Port, FAN_FAULT2_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(FAN_FAULT3_GPIO_Port, FAN_FAULT3_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(FAN_FAULT4_GPIO_Port, FAN_FAULT4_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(FAN_FAULT5_GPIO_Port, FAN_FAULT5_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(DSP_FAULT_O_GPIO_Port, DSP_FAULT_O_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(ARM_FAULT_GPIO_Port, ARM_FAULT_Pin, GPIO_MODE_INPUT);
    GPIO_SetMode(DIG1_GPIO_Port, DIG1_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(FF_GPIO_Port, FF_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(JD0_DET_GPIO_Port, JD0_DET_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(JD1_DET_GPIO_Port, JD1_DET_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(CAL_GPIO_Port, CAL_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(TRIP_GPIO_Port, TRIP_Pin, GPIO_MODE_INPUT);
	GPIO_SetMode(TEST_GPIO_Port, TEST_Pin, GPIO_MODE_INPUT);
	
	GPIO_SetMode(JOUT1_GPIO_Port, JOUT1_Pin, GPIO_MODE_OUTPUT);
	GPIO_SetMode(JOUT2_GPIO_Port, JOUT2_Pin, GPIO_MODE_OUTPUT);
	GPIO_SetMode(EN_DISCHARGE_GPIO_Port, EN_DISCHARGE_Pin, GPIO_MODE_OUTPUT);
	GPIO_SetMode(EN_DC_AUX_GPIO_Port, EN_DC_AUX_Pin, GPIO_MODE_OUTPUT);
	GPIO_SetMode(ACJOUT_GPIO_Port, ACJOUT_Pin, GPIO_MODE_OUTPUT);
	GPIO_SetMode(LED_DOUT_GPIO_Port, LED_DOUT_Pin, GPIO_MODE_OUTPUT);
	GPIO_SetMode(LED_DOUT1_GPIO_Port, LED_DOUT1_Pin, GPIO_MODE_OUTPUT);
	GPIO_SetMode(DO1_GPIO_Port, DO1_Pin, GPIO_MODE_OUTPUT);
}
	
/**
 * @brief Read level of DIO
 *
 * @param[in] channnel
 *
 * @return STATUS_MEMORY_ERROR fail of the memory allocation
 *
 * @details 读取某个管脚，而非PX所有的电平数据
 */

Dio_LevelType Dio_ReadChannel(Dio_ChannelType channnel)
{
	return (Dio_LevelType) GPIO_PIN_DATA(channnel.Port-PA, channnel.u32PinMask-BIT0);
}

/**
 * @brief Get the version information of DIO
 *
 * @param[in] ConfigPtr
 *
 * @return STATUS_MEMORY_ERROR fail of the memory allocation
 *
 * @details Check if message finished (FIFO empty of debug port)
 */

void Dio_WriteChannel(Dio_ChannelType channnel, Dio_LevelType level)
{
	GPIO_PIN_DATA(channnel.Port-PA, channnel.u32PinMask-BIT0) = level;
}
