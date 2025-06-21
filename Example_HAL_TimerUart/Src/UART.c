/** @file USART.c
*  @brief The implementation for HAL function of general USART module.
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "USART.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
#define UARTx	1
/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/
/**********************************************************************
* Module Typedefs
**********************************************************************/
/**********************************************************************
* Module Variable Definitions
**********************************************************************/
char *Rx, *Tx;
char buffer[255];

/**********************************************************************
* Function Prototypes
**********************************************************************/
void USARTx_InterrupFuntion(USART_TypeDef *);
uint16_t USARTx_BaudRateGeneration(USART_TypeDef *, uint32_t, uint32_t);

/**********************************************************************
* Function Definitions
**********************************************************************/

/**********************************************************************
* Function : Name
*//**
* \b Description:
*
* This function...
*
* PRE-CONDITION:
*
* POST-CONDITION: 
*
* @param None
*
* @return None
*
* \b Example Example:
* @code
* @endcode
*
* This section is used to mention functions related with the funtion
*
* @see 
* 
**********************************************************************/

/**********************************************************************
* Function : USARTx_IRQHandler
*//**
* \b Description:
*
* This function is called when an interrupt is comming. It'll come from
* USART's interrupt flags. 
*
* PRE-CONDITION: A hardware/Software interrupt generation from 
* reception and/or transmition by USART. 
*
* POST-CONDITION: If it is a interrupt by transmition, the 
* characters will be transmitted by Tx's buffer. If it is a interrupt 
* by reception, the characters will be saved on Rx's buffer.
*
* @param USARTx_
*
* @return Null
*
* \b Example Example:
* @code
* void USART1_IRQHandler(void)
* {
*	USARTx_InterrupFuntion(USART1);
* }
* @endcode
*
* This section is used to mention functions related with the funtion
*
* @see USARTx_InitTrans
* @see USARTx_Config
* @see USARTx_Start
* @see USARTx_Stop
* 
**********************************************************************/
#if UARTx == 1
void USART1_Handler(void)
{
	USARTx_InterrupFuntion(USART1);

}
#elif UARTx == 2
void USART2_Handler(void)
{
	USARTx_InterrupFuntion(USART2);

}
#elif UARTx == 3
void USART3_Handler(void)
{
	USARTx_InterrupFuntion(USART3);

}
#elif UARTx == 4
void UART4_Handler(void)
{
	USARTx_InterrupFuntion(UART4);

}

#elif UARTx == 5
void LPUART1_Handler(void)
{
	USARTx_InterrupFuntion(LPUART1);

}
#endif

/**********************************************************************
* Function : USARTx_InterrupFuntion
*//**
* \b Description:
*
* This function is used to manage the interrupt service rutine (ISR) 
* by USART. It manages transmition and reception interrupt flags. By 
* transmition, it must be mask the interrupt flag first. Then it 
* must be desable when buffer ends. By reception, flag must be
* mask. Then it could be desable. You must use this funtion after 
* configure the ISR, the USART and the transmition and reception with 
* interrupts.
*
* PRE-CONDITION: A hardware/Software interrupt generation from 
* reception and/or transmition by USART. At the same time, 
* USARTx_IRQHandler must be called before this one.
*
* POST-CONDITION: If it is a interrupt by transmition, the 
* characters will be transmitted by Tx's buffer. If it is a interrupt 
* by reception, the characters will be saved on Rx's buffer.
*
* @param USARTx_
*
* @return Null
*
* \b Example Example:
* @code
* void USART1_IRQHandler(void)
* {
*	USARTx_InterrupFuntion(USART1);
* }
* @endcode
*
* This section is used to mention functions related with the funtion
*
* @see USARTx_InitTrans
* @see USARTx_Config
* @see USARTx_Start
* @see USARTx_Stop
* 
**********************************************************************/
void USARTx_InterrupFuntion(USART_TypeDef *USARTx_)
{
	if (USARTx_->ISR & RXNEIE_FLAG)
	{
		*Rx++ = USARTx_->RDR;

		CLEAR_BIT(USARTx_->RQR, RXNEIE_FLAG);

	}

	if (USARTx_->ISR & TXNEIE_FLAG && *Tx != '\0')
	{
		USARTx_->TDR = *Tx++;

	}else if (USARTx_->CR1 & TXNEIE_FLAG && *Tx == '\0')
	{
		CLEAR_BIT(USARTx_->CR1, TXNEIE_FLAG);

	}

}

/**********************************************************************
* Function : Reset_PointerRx
*//**
* \b Description:
*
* This function is used to redefine the Rx's pointer to the first 
* element of buffer.
*
* PRE-CONDITION: Rx should be used.
*
* POST-CONDITION: Rx moved to first element of buffer.
*
* @param None
*
* @return None
*
* \b Example Example:
* @code
* Rx = &buffer[5];
* Reset_PointerRx();
* @endcode
*
* This section is used to mention functions related with the funtion
*
* @see USARTx_AsynConfig
* @see Buffer_ResetInitValue
* 
**********************************************************************/
void Reset_PointerRx(void)
{
	Rx = buffer;
}

/**********************************************************************
* Function : Buffer_ResetInitValue
*//**
* \b Description:
*
* This function is used to re-write with null character the buffer. 
* Also the funtion will reset the Rx pointer to the first element of 
* Buffer.  
*
* PRE-CONDITION: Buffer should be write before.
*
* POST-CONDITION: Buffer will be write with null character in all the 
* elements.
*
* @param None
*
* @return None
*
* \b Example Example:
* @code
* Buffer[0] = 'A';
* Buffer[1] = 'B';
* Buffer_ResetInitValue();
* 
* @endcode
*
* This section is used to mention functions related with the funtion
*
* @see Reset_PointerRx
* 
**********************************************************************/
void Buffer_ResetInitValue(void)
{
	uint16_t x = 0;
	Reset_PointerRx();

	while(buffer[x] != '\0')
	{
		buffer[x++] = '\0';
	}

	Reset_PointerRx();
}

/**********************************************************************
* Function : USARTx_InitTrans
*//**
* \b Description:
*
* This function can transmit a buffer by USART, using polling or 
* a interrupt service. Before call it, it's neccessary to configure 
* and start the peripheral.
*
* PRE-CONDITION: Configure and start the Peripheral.
*
* POST-CONDITION: The transmit will be by polling or a interrupt service.
*
* @param USARTx_
* @param Tx_IntEnable
* @param msg
*
* @return None
*
* \b Example Example:
* @code
*	USARTx_Start(USART1_Conf, USART1);
* 	USARTx_InitTrans(USART1, false, "HOLA LIESE\0");
* @endcode
*
* This section is used to mention functions related with the funtion
*
* @see USARTx_AsynConfig
* @see USARTx_Start
* @see USARTx_Stop
* 
**********************************************************************/
void USARTx_InitTrans(USART_TypeDef *USARTx_, bool Tx_IntEnable, char *msg)
{
	if ( !(USARTx_->CR1 & TE_MASK_BIT) || !(USARTx_->CR1 & USART_ENABLE) )
	{
		return;

	}

	Tx = msg;

	if ( Tx_IntEnable )
	{
	    SET_BIT(USARTx_->CR1, TXNEIE_FLAG);

	}else
	{
		while( *Tx )
		{
			USARTx_->TDR = *Tx++;
			while( !(USARTx_->ISR & TXNEIE_FLAG) );

		}
	}

}

/**********************************************************************
* Function : USARTx_Start
*//**
* \b Description:
*
* This function is called when you want to start a receive and transmit. 
* It is used when you want to enable USART. After use this funtion, you 
* can send and receive data.
*
* PRE-CONDITION: Configure the Peripheral.
*
* POST-CONDITION: It'll Start the transmit and receive.
*
* @param USART_Config
* @param USARTx_
*
* @return None
*
* \b Example Example:
* @code
*	USARTx_Config(USART1_Conf, USART1, GPIOA);
*	USARTx_Start(USART1_Conf, USART1);
* @endcode
*
* This section is used to mention functions related with the funtion
*
* @see USARTx_AsynConfig
*
**********************************************************************/
void USARTx_Start(USART_Config USART_Config, USART_TypeDef *USARTx_)
{
	if( USART_Config.Rx_Enable )
	{
		SET_BIT(USARTx_->CR1, RXNEIE_FLAG);
	}

	SET_BIT(USARTx_->CR1, USART_ENABLE);

}

/**********************************************************************
* Function : USARTx_Stop
*//**
* \b Description:
*
* This function is called when you want to stop a receive and transmit. 
* It is used when you want to desable USART. After use this funtion, you 
* can't send and receive data. The configuration'll be saved.
*
* PRE-CONDITION: Configure the Peripheral and finished the transmit  
* and receive.
*
* POST-CONDITION: It'll finished the transmit and receive.
*
* @param USARTx_
*
* @return None
*
* \b Example Example:
* @code
*   USARTx_Start(USART1_Conf, USART1);
* 	USARTx_InitTrans(USART1, false, "HOLA LIESE\0");
*	USARTx_Stop(USART1);
* @endcode
*
* This section is used to mention functions related with the funtion
*
* @see USARTx_AsynConfig
*
**********************************************************************/
void USARTx_Stop(USART_TypeDef *USARTx_)
{
	if( (USARTx_->CR1 & RXNEIE_FLAG) )
	{
		CLEAR_BIT(USARTx_->CR1, RXNEIE_FLAG);

	}

	if ( (USARTx_->CR1 & TXNEIE_FLAG) )
	{
		CLEAR_BIT(USARTx_->CR1, TXNEIE_FLAG);

	}

	CLEAR_BIT(USARTx_->CR1, USART_ENABLE);

}

/**********************************************************************
* Function : USARTx_AsynConfig
*//**
* \b Description:
*
* This function is used to configure the Peripheral USART in 
* Asyncronous mode. 
*
* PRE-CONDITION: None.
*
* POST-CONDITION: The Peripheral USART'll be ready to start transmit
* and receive. 
*
* @param USARTx_
* @param USART_Config
* @param GPIOx_
* 
* @return Null
*
* \b Example Example:
* @code
* 	//Structure of configuration
*	USART_Config USART1_Conf =
*	{
*		USART1_CLK,
*		USART1_AFSEL,
*		OVER16_MODE,
*		USART_Clock16MHZ,
*		USART_9600bps,
*		USARTx_STOP_1BIT,
*		USARTx_NOT_PARITY,
*		USARTx_WL_8BITS,
*		USARTx_NOT_SWAP,
*		USARTx_NOT_INV,
*		USARTx_DirLogic,
*		USARTx_LSB,
*		Tx_ENABLE,
*		Rx_DESABLE,
*		USART1_PRIO,
*		USART1_IRQn,
*		USART1_PA9_Tx,
*		USART1_PA10_Rx
*
*	};
*	//...
*   int main()
*	{
*		RCC_EnPort(GPIOA);
*
*		USARTx_Config(USART1_Conf, USART1, GPIOA);
*		
*	}
* @endcode
*
* This section is used to mention functions related with the funtion
*
* @see USARTx_InitTrans
* @see USARTx_Start
* @see USARTx_Stop
* 
**********************************************************************/
void USARTx_AsynConfig(USART_Config USART_Config, USART_TypeDef *USARTx_, GPIO_TypeDef *GPIOx_)
{
	Reset_PointerRx();

	switch (USART_Config.USARTx_Clk)
	{

	case USART1_CLK:
		SET_BIT(RCC->APB2ENR, (1<<USART1_CLK) );
		break;

    case USART2_CLK:
		SET_BIT(RCC->APB1ENR1, (1<<USART2_CLK) );
		break;

    case USART3_CLK:
		SET_BIT(RCC->APB1ENR1, (1<<USART3_CLK) );
		break;

    case UART4_CLK:
		SET_BIT(RCC->APB1ENR1, (1<<UART4_CLK) );
		break;

    case LPUART1_CLK:
    		SET_BIT(RCC->APB1ENR2, (1<<LPUART1_CLK) );
    		break;

    default:
    	return;
	}

	GPIOx_InitAF(GPIOx_, USART_Config.Pinx_Tx, GPIO_OTYPER_PP, 0, USART_Config.USARTx_Afsel);
	GPIOx_InitAF(GPIOx_, USART_Config.Pinx_Rx, GPIO_OTYPER_PP, 0, USART_Config.USARTx_Afsel);

	CLEAR_BIT(USARTx_->CR1, (USART_ENABLE << UE_BIT) );
	CLEAR_BIT(USARTx_->CR1, TXNEIE_FLAG|RXNEIE_FLAG);

	InterruptFuntion_Config(USART_Config.USARTx_IRQ_IntNum, USART_Config.USARTx_IRQ_IntPri );

	SET_BIT(USARTx_->CR1, (USART_Config.USARTx_Over8 << OVER8_BIT) );

	SET_BIT(USARTx_->BRR, USARTx_BaudRateGeneration(USARTx_, 16000000, USART_Config.USARTx_Brr) );

	SET_BIT(USARTx_->CR2, (USART_Config.USARTx_Swap << SWAP_BIT) );

	SET_BIT(USARTx_->CR2, (USART_Config.USARTx_Stop << STOP_BIT) );

	SET_BIT(USARTx_->CR1, (USART_Config.USARTx_Parity << PARITY_BIT) );

	SET_BIT(USARTx_->CR1, ( (USART_Config.USARTx_WordLen & M1_MASK_BIT) << M1_BIT) );
	SET_BIT(USARTx_->CR1, ( (USART_Config.USARTx_WordLen & M0_MASK_BIT) << M0_BIT) );

	SET_BIT(USARTx_->CR2, (USART_Config.USARTx_LevelInv << INV_BIT) );

	SET_BIT(USARTx_->CR2, (USART_Config.USARTx_Bi_DataInv << DATAINV_BIT) );

	SET_BIT(USARTx_->CR2, (USART_Config.USARTx_MSB_First << MSBFIRST_BIT) );

	SET_BIT(USARTx_->CR1, (USART_Config.Tx_Enable << TE_BIT) );
	SET_BIT(USARTx_->CR1, (USART_Config.Rx_Enable << RE_BIT) );

}

/**********************************************************************
* Function : USARTx_BaudRateGeneration
*//**
* \b Description:
*
* This function is used to generate the Baud rate for 8 and 16 
* Oversampling.
*  
* PRE-CONDITION: The USARTx_AsynConfig funtion must be called 
* before this.
*
* POST-CONDITION: The baud rate is putting on the register.
*
* @param USARTx_
* @param USARTx_ClockFrec
* @param Bauds
* 
* @return The Baud rate data to put it on the register.
*
* \b Example Example:
* @code
*	//...
*	SET_BIT(USARTx_->BRR, USARTx_BaudRateGeneration(USARTx_, 16000000, 9600) );
*	//...
* @endcode
*
* This section is used to mention functions related with the funtion
*
* @see USARTx_AsynConfig
* 
**********************************************************************/
uint16_t USARTx_BaudRateGeneration(USART_TypeDef *USARTx_, uint32_t USARTx_ClockFrec, uint32_t Bauds)
{
	if ( (USARTx_->CR1 & OVER8_MASK_BIT) )
	{
		return (uint16_t)( 2*(USARTx_ClockFrec/Bauds) );
	}

	return (uint16_t)(USARTx_ClockFrec/Bauds);

}
/*************** END OF FUNCTIONS ********************************/
