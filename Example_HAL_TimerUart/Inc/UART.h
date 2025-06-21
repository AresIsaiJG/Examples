/** @file USART.h
*  @brief The interface definition for the USART.
*
* This is the header file for the definition of the interface for a 
* USART peripheral on a STM32L452RE-P microcontroller.
*/

#ifndef UART_H_
#define UART_H_

/**********************************************************************
* Includes
**********************************************************************/

/**********************************************************************
* Preprocessor Constants
**********************************************************************/
/**********************************************************************
* Configuration Constants
**********************************************************************/
/**********************************************************************
* Macros
**********************************************************************/
/**********************************************************************
* Typedef
**********************************************************************/
typedef enum
{
	USART1_PRIO 		= 7,
	USART2_PRIO 		= 1,
	USART3_PRIO 		= 1,
	UART4_PRIO 			= 1,
	LPUART1_PRIO 		= 1
}USARTx_InterruptPriority;

/**
* Defines the structure of configuration of the USART in Asyncronous 
* mode.
*/
typedef struct
{
	uint16_t  	USARTx_Clk:7;		/**< USART Selector of Clock */
	uint16_t 	USARTx_Afsel:8;		/**< Altern Funtion Selector for USARTx */
	uint16_t 	USARTx_Over8:1;		/**< USART Oversampling mode */
	uint32_t 	USARTx_ClockBrr;	/**< USART CLock for Generate Baud Rate */
	uint32_t 	USARTx_Brr;			/**< USART Baud Rate */
	uint32_t	USARTx_Stop:1;		/**< USART Bit stop */
	uint32_t	USARTx_Parity:2;	/**< USART parity control */
	uint32_t	USARTx_WordLen:2;	/**< USART Word Length from 7 to 9 bits */
	uint32_t	USARTx_Swap:1;		/**< USART Swap Tx/Rx pins */
	uint32_t	USARTx_LevelInv:2;	/**< USART Level Inversion Tx/Rx */
	uint32_t	USARTx_Bi_DataInv:1;/**< USART Binary Data Inversion */
	uint32_t	USARTx_MSB_First:1;	/**< USART Most Significant Bit First */
	uint32_t 	Tx_Enable:1;		/**< USART Tx enable */
	uint32_t 	Rx_Enable:1;		/**< USART Rx enable */
	uint32_t 	USARTx_IRQ_IntPri:4;/**< USARTx_IRQ Interrupt Priority */
	uint32_t 	USARTx_IRQ_IntNum:8;/**< USARTx_IRQ Interrupt Number Priority */
	uint32_t 	Pinx_Tx:4; 			/**< Pin Tx */
	uint32_t 	Pinx_Rx:4; 			/**< Pin Rx */

}USART_Config;

/**
* Used to define pins with Alternal Funtions for USART1
*/
typedef enum
{
	USART1_PA9_Tx	= 9,	/**< Pin 9, GPIO A. Transmisor line */
	USART1_PA10_Rx  = 10,	/**< Pin 10, GPIO A. Receptor line */
	USART1_PB6_Tx	= 6,	/**< Pin 6, GPIO B. Transmisor line */
	USART1_PB7_Rx   = 7		/**< Pin 7, GPIO B. Receptor line */

}USART1_Pinout;

/**
* Used to define pins with Alternal Funtions for USART2
*/
typedef enum
{
	USART2_PA2_Tx 	= 2,	/**< Pin 2, GPIO A. Transmisor line */
	USART2_PA3_Rx 	= 3		/**< Pin 3, GPIO A. Receptor line */

}USART2_Pinout;

/**
* Used to define pins with Alternal Funtions for USART3
*/
typedef enum
{
	USART3_PB10_Tx 	= 10,	/**< Pin 10, GPIO B. Transmisor line */
	USART3_PB11_Rx 	= 11	/**< Pin 11, GPIO B. Receptor line */

}USART3_Pinout;

/**
* Used to define pins with Alternal Funtions for UART4
*/
typedef enum
{
	UART_PA0_Tx 	= 0,	/**< Pin 0, GPIO A. Transmisor line */
	UART_PA1_Rx 	= 1,	/**< Pin 1, GPIO A. Receptor line */
	UART_PC10_Tx 	= 10,	/**< Pin 10, GPIO C. Transmisor line */
	UART_PC11_Rx 	= 11	/**< Pin 11, GPIO C. Receptor line */

}UART4_Pinout;

/**
* Used to define pins with Alternal Funtions for LPUART1
*/
typedef enum
{
	UART_PA2_Tx 	= 2,	/**< Pin 2, GPIO A. Transmisor line */
	UART_PA3_Rx 	= 3		/**< Pin 3, GPIO A. Receptor line */

}LPUART1_Pinout;

/**
* Used to define the Alternal Funtion for All USARTs
*/
typedef enum
{
	USART1_AFSEL 		= 0x7,	/**< AFSEL 7, USART1 */
	USART2_AFSEL 		= 0x7,	/**< AFSEL 7, USART2 */
	USART3_AFSEL 		= 0x7,	/**< AFSEL 7, USART3 */
	UART4_AFSEL			= 0x8,	/**< AFSEL 8, UART4 */
	LPUART1_AFSEL 		= 0x8	/**< AFSEL 8, LPUART1 */

}USARTx_GpioAF;

/**
* Used to:
* - Give clock to the Peripheral on the specific bit of the register
* - In a Switch-case as an option
*/
typedef enum
{
	USART1_CLK 			= 14,	/**< USART1, bit 14 to give clock */
	USART2_CLK 			= 17,	/**< USART2, bit 17 to give clock */
	USART3_CLK 			= 18,	/**< USART3, bit 18 to give clock */
	UART4_CLK			= 19,	/**< UART4, bit 19 to give clock */
	LPUART1_CLK			= 0	 	/**< LPUART1, bit 0 to give clock */

}USARTx_ClockEnable;

/**
* Used to define the position of the STOP bit.
* The configuration is for 1 or 2 stop bits. 
*/
typedef enum
{
	STOP_BIT			= 13,	/**< Bit position to configure STOP bit */
	USARTx_STOP_1BIT	= 0,	/**< One bit stop */
	USARTx_STOP_2BIT	= 1		/**< Two bits stop */

}StopBit_Config;

/**
* Used to define the position of the PARITY bit.
* The configuration is for Even, Odd and not parity. 
*/
typedef enum
{
	PARITY_BIT			= 9,	/**< Bit position to configure PARITY bit */
	USARTx_NOT_PARITY	= 0,	/**< Not parity */
	USARTx_EVEN_PARITY  = 2,	/**< Even parity */
	USARTx_ODD_PARITY  	= 3		/**< Odd parity */

}Parity_Config;

/**
* Used to define the position of the M1-M0 bit.
* The configuration is for 7, 8 and 9 bits in Word Lengh 
* on bit M1 and M0. 
*/
typedef enum
{
	M1_BIT				= 28,	/**< Bit position to configure M1 bit */
	M0_BIT				= 12,	/**< Bit position to configure M0 bit */
	M1_MASK_BIT			= 0x02,	/**< Mask used to configure M1 bit on register CR1 */
	M0_MASK_BIT			= 0x01, /**< Mask used to configure M0 bit on register CR1 */
	USARTx_WL_7BITS		= 2,	/**< Configuration of 7 bits for Word Lengh */
	USARTx_WL_8BITS		= 0,	/**< Configuration of 8 bits for Word Lengh */
	USARTx_WL_9BITS		= 1		/**< Configuration of 9 bits for Word Lengh */

}DataWordLengh_Config;

/**
* Used to define the position of SWAP bit.
* The Swap will change the Transmisor and 
* Receptor pins on the target. 
*/
typedef enum
{
	SWAP_BIT			= 15,	/**< Bit position to configure SWAP bit */
	USARTx_SWAP			= 1,	/**< used to enable swap within Tx and Rx lines */
	USARTx_NOT_SWAP		= 0 	/**< used to disable swap within Tx and Rx lines */

}SwapTxRxPins_Config;

/**
* Used to define the Level Invertion Lines bit.
* Configurate for Level Invertion: Tx.
* Configurate for Level Invertion: Rx.
* Configurate for Level Invertion: Tx and Rx. 
* Configurate for Level Invertion: Not Inversion
*/
typedef enum
{
	INV_BIT				= 16,	/**< Bit position to configure LEVEL INVERTION LINES bit */
	USARTx_INV_BOTH		= 3,    /**< Used to invert both lines level */
	USARTx_INV_Tx		= 2, 	/**< Used to invert Transmisor line level */
	USARTx_INV_Rx		= 1, 	/**< Used to invert Receptor line level */
	USARTx_NOT_INV		= 0		/**< Used to not level inversion lines  */

}LevelInversionLines_Config;

/**
* Used to define the DATAINV bit.
* Configure for logical data from
* the data register are send/received
* in negative/inverse logic, with 1.
* Logical data from the data register 
* are send/received in positive/direct 
* logic, with 0.
*/
typedef enum
{
	DATAINV_BIT			= 18,	/**< Bit position to configure DATA INVERTION bit */
	USARTx_DirLogic		= 0, 	/**< Used to disable the data invertion */
	USARTx_InvLogic		= 1  	/**< Used to enable the data invertion */

}BinaryDataInversion_Config;

/**
* Used to define the position of MSBFIRST bit.
* This bit change the Low Significant Bit (Bit 0) 
* in the data for the Most Significant Bit 
* (Bit 7/8/9).
*/
typedef enum
{
	MSBFIRST_BIT		= 19,	/**< Bit position to configure MSB FIRST bit */
	USARTx_LSB			= 0,	/**< Used to configure the Least Significant Bit */
	USARTx_MSB			= 1 	/**< Used to configure the Most Significant Bit */
}SignificantBitFirst_Config;

/**
* Used to define the position of OVER8 bit.
* This bit change the Over sampling mode by
* 8 or 16.
*/
typedef enum
{
	OVER8_BIT			= 15,		/**< Bit position to configure OVER SAMPLING bit */
	OVER8_MASK_BIT		= 0x8000,	/**< Mask used to select the OVER8 bit */
	OVER8_MODE			= 1,		/**< Used to enable Over sampling of 8 */
	OVER16_MODE 		= 0			/**< Used to enable Over sampling of 16 */

}Oversampling_Config;

/**
* Used to define the position of TE, and RE bit.
* This bits are defined to enable or disable the
* Transmission and Reception.
*/
typedef enum
{
	TE_BIT				= 3,	/**< Bit position to configure TRANSMITION bit */
	RE_BIT				= 2,	/**< Bit position to configure RECEPTION bit */
	TE_MASK_BIT			= 0x08,	/**< Mask used to select TE bit */
	Tx_ENABLE			= 1,	/**< Used to enable the transmition */
	Tx_DESABLE			= 0,	/**< Used to disable the transmition */
	Rx_ENABLE			= 1,	/**< Used to enable the reception */
	Rx_DESABLE			= 0		/**< Used to disable the reception */

}TransmisorReceptor_Config;

/**
* Used to define the position of TXNEIE, and RXNEIE bit.
* This bits enable the interrupts for Transmission and
* Reception.
*/
typedef enum
{
	TXNEIE_FLAG 		= 0x80,	/**< Mask used to select the Transmition interrupt flag */
	RXNEIE_FLAG 		= 0x20	/**< Mask used to select the Reception interrupt flag */

}TeReInterrupt_Config;

/**
* Used to define the position of UE bit.
* This bit is used for enable Transmission and Reception.
*/
typedef enum
{
	UE_BIT		 		= 0,	/**< Bit position to configure UART ENABLE bit */
	USART_ENABLE		= 1,	/**< Used to enable USART */
	USART_DESABLE		= 0		/**< Used to disable USART */

}Enable_Config;

/**
* This enumeration is used to define the clock used in the
* Baud Rate Generation.
*/
typedef enum
{
	USART_Clock4MHZ		= 4000000,	/**< Clock of 4 MHz, with MSI */
	USART_Clock8MHZ		= 8000000,	/**< Clock of 8 MHz, with MSI */
	USART_Clock16MHZ	= 16000000	/**< Clock of 16 MHz, with MSI */

}USART_ClocksForUse;

/**
* This enumeration is used to define the Baud Rate.
*/
typedef enum
{
	USART_9600bps		= 9600,		/**< Baud Rate of 9600 bps */
	USART_115200bps		= 115200	/**< Baud Rate of 115200 bps*/

}USART_BaudRate;

/**********************************************************************
* Function Prototypes
**********************************************************************/
void Reset_PointerRx(void);
void Buffer_ResetInitValue(void);
void USARTx_InitTrans(USART_TypeDef *, bool, char *);
void USARTx_Start(USART_Config, USART_TypeDef *);
void USARTx_Stop(USART_TypeDef *);
void USARTx_AsynConfig(USART_Config, USART_TypeDef *, GPIO_TypeDef *);

#endif /* UART_H_ */

 /*** End of File ******************************************************/
