/**
 * @file can_fd.c
 * @brief
 * @author zk
 * @date 2023年08月14日
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

/**
 * @brief Change the CANFD  Data Baudrate
 *
 * @param[in] Controller
 *            baudrate
 *
 * @return STATUS_MEMORY_ERROR fail of the memory allocation
 *
 * @details Check if message finished (FIFO empty of debug port)
 */
 
Std_ReturnType Can_ChangeBaudrate(uint8_t Controller, const uint16_t baudrate)
{
	CANFD_FD_T sCANFD_Config;
	
	/*Get the CAN FD0 configuration value*/
    CANFD_GetDefaultConfig(&sCANFD_Config, CANFD_OP_CAN_FD_MODE);
    
	/*Change the CAN FD0 Baudrate/Bitrate*/
	sCANFD_Config.sBtConfig.sNormBitRate.u32BitRate = 1000000;
    sCANFD_Config.sBtConfig.sDataBitRate.u32BitRate = 4000000;
    /*Open the CAN FD0 feature*/
    CANFD_Open(CANFD0, &sCANFD_Config);
}

/**
 * @brief Get the CANFD Version Information
 *
 * @param[in] ConfigPtr
 *
 * @return STATUS_MEMORY_ERROR fail of the memory allocation
 *
 * @details Check if message finished (FIFO empty of debug port)
 */

void Can_GetVersionInfo(Std_VersionInfoType *version)
{
	
}
	
/**
 * @brief Init CAN_FD
 *
 * @param[in] ConfigPtr
 *
 * @return STATUS_MEMORY_ERROR fail of the memory allocation
 *
 * @details Check if message finished (FIFO empty of debug port)
 */

void Can_Init(const Can_ConfigType *Config)
{
	/* Unlock protected registers */
    SYS_UnlockReg();
	
	/* Enable IP clock */
    CLK_SetModuleClock(CANFD0_MODULE, CLK_CLKSEL4_CANFD0SEL_APLL, 0);
    CLK_EnableModuleClock(CANFD0_MODULE);
	
	/* Set PX multi-function pins for CANFD0 RXD and TXD 设置相应管脚作为CANFD收发端口*/
    SYS->GPI_MFPL &= ~(SYS_GPI_MFPL_PI2MFP_Msk | SYS_GPI_MFPL_PI3MFP_Msk);
    SYS->GPI_MFPL |= SYS_GPI_MFPL_PI2MFP_CAN0_RXD | SYS_GPI_MFPL_PI3MFP_CAN0_TXD;
	
	/* Lock protected registers */
    SYS_LockReg();
	
	Std_ReturnType Can_ChangeBaudrate(uint8_t Controller, const uint16_t baudrate);

    /* receive 0x110 in CAN FD0 rx message buffer 0 by setting mask 0 */
    CANFD_SetSIDFltr(CANFD0, 0, CANFD_RX_BUFFER_STD(0x111, 0));
    /* receive 0x220 in CAN FD0 rx message buffer 0 by setting mask 1 */
    CANFD_SetSIDFltr(CANFD0, 1, CANFD_RX_BUFFER_STD(0x22F, 0));
    /* receive 0x333 in CAN FD0 rx message buffer 0 by setting mask 2 */
    CANFD_SetSIDFltr(CANFD0, 2, CANFD_RX_BUFFER_STD(0x333, 0));

    /* receive 0x222 (29-bit id) in CAN FD0 rx message buffer 1 by setting mask 3 */
    CANFD_SetXIDFltr(CANFD0, 0, CANFD_RX_BUFFER_EXT_LOW(0x222, 1), CANFD_RX_BUFFER_EXT_HIGH(0x222, 1));
    /* receive 0x3333 (29-bit id) in CAN FD0 rx message buffer 1 by setting mask 3 */
    CANFD_SetXIDFltr(CANFD0, 1, CANFD_RX_BUFFER_EXT_LOW(0x3333, 1), CANFD_RX_BUFFER_EXT_HIGH(0x3333, 1));
    /* receive 0x44444 (29-bit id) in CAN FD0 rx message buffer 1 by setting mask 3 */
    CANFD_SetXIDFltr(CANFD0, 2, CANFD_RX_BUFFER_EXT_LOW(0x44444, 1), CANFD_RX_BUFFER_EXT_HIGH(0x44444, 1));
    /* CAN FD0 Run to Normal mode  */
    CANFD_RunToNormal(CANFD0, TRUE);
}

/**
 * @brief Read the message from CANFD
 *
 * @param[in] ConfigPtr
 *
 * @return STATUS_MEMORY_ERROR fail of the memory allocation
 *
 * @details Check if message finished (FIFO empty of debug port)
 */

Can_ReturnType Can_Read(uint8_t Controller, Can_PduType *PduInfo)
{
	CANFD_FD_MSG_T sRxMsgFrame;
	uint8_t u8ErrFlag = 0;
	
	/* check for any received messages on CAN FD0 message buffer Controller */
	if (CANFD_ReadRxBufMsg(CANFD0, Controller, &sRxMsgFrame) == 1)
	{
		printf("Rx buf 0: Received message 0x%08X\n", sRxMsgFrame.u32Id);
		printf("Message Data : ");

		for (uint8_t u8Cnt = 0; u8Cnt < sRxMsgFrame.u32DLC; u8Cnt++)
		{
			printf("%02d ,", sRxMsgFrame.au8Data[u8Cnt]);
		}

		printf(" \n\n");

		/* Check Standard ID number */
		if ((sRxMsgFrame.u32Id != 0x111) && (sRxMsgFrame.u32Id != 0x22F) && (sRxMsgFrame.u32Id != 0x333))
		{
			u8ErrFlag = 1;
		}

		/* Check Data lenght */
		if (sRxMsgFrame.eIdType != eCANFD_SID)
		{
			u8ErrFlag = 1;
		}

		if (u8ErrFlag == 1)
		{
			printf("CAN FD STD ID or Data Error \n");
			getchar();
		}
	}
	return u8ErrFlag;

}

/**
 * @brief Write the message to the CAN FD Message Struct
 *
 * @param[in] Controller
 *            PduInfo
 *
 * @return STATUS_MEMORY_ERROR fail of the memory allocation
 *
 * @details Check if message finished (FIFO empty of debug port)
 */

Can_ReturnType Can_Write(uint8_t Controller, const Can_PduType *PduInfo)
{
	CANFD_FD_MSG_T sTxMsgFrame;
    
    printf("Start to CAN FD Bus Transmitter :\n");

    /* Set the ID Number */        
    sTxMsgFrame.u32Id = 0x44444;
    
	/*Set the ID type*/
	sTxMsgFrame.eIdType = eCANFD_SID; //eCANFD_XID;
            
	/*Set the frame type*/
	sTxMsgFrame.eFrmType = eCANFD_DATA_FRM;
	/*Set CAN FD frame format */
	sTxMsgFrame.bFDFormat = 1;
	/*Set the bitrate switch */
	sTxMsgFrame.bBitRateSwitch = 1;

	/*Set the data lenght */
	sTxMsgFrame.u32DLC = 64;

          
    /*Set the data message */
	printf("Data Message : ");

	for (u8Cnt = 0; u8Cnt < sTxMsgFrame.u32DLC; u8Cnt++)
	{
		sTxMsgFrame.au8Data[u8Cnt] = u8Cnt + u8TxTestNum;
		printf("%02d,", sTxMsgFrame.au8Data[u8Cnt]);
	}

	return sTxMsgFrame;
}