/**************************************************************************//**
 * @file     main.c
 * @brief    test the driver of DIO and wwdt
 *
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include <time.h>

#include "NuMicro.h"
#include "watchdog.h"
#include "dio.h"

void UART16_Init()
{
    
	/* Unlock protected registers */
    SYS_UnlockReg();

	/* Enable UART clock */
    CLK_EnableModuleClock(UART16_MODULE);

    /* Select UART clock source from HXT */
    CLK_SetModuleClock(UART16_MODULE, CLK_CLKSEL3_UART16SEL_HXT, CLK_CLKDIV3_UART16(1));
	
	SystemCoreClockUpdate();

    /* Set multi-function pins for UART */
    SYS->GPK_MFPL &= ~(SYS_GPK_MFPL_PK2MFP_Msk | SYS_GPK_MFPL_PK3MFP_Msk);
    SYS->GPK_MFPL |= (SYS_GPK_MFPL_PK2MFP_UART16_RXD | SYS_GPK_MFPL_PK3MFP_UART16_TXD);
	
	/* Lock protected registers */
    SYS_LockReg();
	
	/* Init UART to 115200-8n1 for print message */
    UART_Open(UART16, 115200);
}

int32_t main(void)
{

    clock_t start_t,finish_t;
	double total_t = 0;
    
	start_t = clock();

    /* Init UART16 for printf */
    UART16_Init();
	
    printf("\n\nCPU @ %dHz\n", SystemCoreClock);
    printf("Test the driver of DIO and WWDG\n");
    
	/* Init WWDT to test */
	WWDT_init();

    printf("[WWDT_CTL: 0x%08X]\n\n", WWDT2->CTL);
	
	finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;//将时间转换为秒

    printf("main程序执行时间：%f\n", total_t);
	
	while(1);//直到看门狗复位

}
