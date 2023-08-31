/********************************************************************************
*                                    Include files
********************************************************************************/
#include "watchdog.h"

/**
 * @brief WWDT2�жϷ������
 *
 * @param[in] void
 *
 * @return void
 *
 * @details ���ƥ���жϣ�����ж�λ��ι����ֹ��λ
 */

void WWDT2_IRQHandler(void)
{
    if(WWDT_GET_INT_FLAG() == 1)
    {
        /* Clear WWDT compare match interrupt flag */
        WWDT_CLEAR_INT_FLAG();
		
        /* To reload the WWDT counter value to 0x3F */
        KickDog();

        printf("WWDT compare match interrupt occurred and kick the dog.");
    }
}

/**
 * @brief Init the WWDT
 *
 * @param[in] void
 *
 * @return void
 *
 * @details �����Ĵ���д��������ʼ��ʱ�ӡ���ʼ�����Ź��жϷ���������ö�ʱʱ�俪WWDT
 */

void WWDT_init(void)
{
    /* Unlock protected registers */
	SYS_UnlockReg();
	
	/* Select WWDT clock source */
	CLK_SetModuleClock(WDT2_MODULE, CLK_CLKSEL3_WWDT2SEL_LIRC, 0);
	
	/* To update the variable SystemCoreClock */
    SystemCoreClockUpdate();
	
	/* Lock protected registers */
	SYS_LockReg();
	
	/* To check if system has been reset by WWDT time-out reset or not */
	if(WWDT_GET_RESET_FLAG() == 1)
    {
        printf("*** System has been reset by WWDT time-out reset event. [WWDT_CTL: 0x%08X] ***\n\n", WWDT2->CTL);
        WWDT_CLEAR_RESET_FLAG();
        while(1);
    }
	
	/* Enable WWDT NVIC */
	NVIC_EnableIRQ(WDT2_IRQn);
	
	/*
        Max time-out period is 1024*(64*WWDT_CLK);
        ���������ʱ�䣬set WWDT compare value;
        Enable WWDT compare match interrupt;
    */
	WWDT_Open(WWDT_PRESCALER_1024, 32, TRUE);
}

/**
 * @brief kick the wwdt
 *
 * @param[in] void
 *
 * @return void
 *
 * @details set RLDCNT = 0x5AA5
 */

void KickDog(void)
{
    WWDT_RELOAD_COUNTER();
}
