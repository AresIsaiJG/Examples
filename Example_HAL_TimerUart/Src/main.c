#include "TIMER.h"
#include "UART.h"

USART_Config USARTx_Conf =
{
	USART1_CLK,
	USART1_AFSEL,
	OVER16_MODE,
	USART_Clock16MHZ,
	USART_9600bps,
	USARTx_STOP_1BIT,
	USARTx_NOT_PARITY,
	USARTx_WL_8BITS,
	USARTx_NOT_SWAP,
	USARTx_NOT_INV,
	USARTx_DirLogic,
	USARTx_LSB,
	Tx_ENABLE,
	Rx_DESABLE,
	USART1_PRIO,
	USART1_IRQn,
	USART1_PA9_Tx,
	USART1_PA10_Rx

};

TIMER_Config TIMER6_Conf =
{
	TIMER6_CLK,
	{TIM6_DAC_IRQn, TIMER6_PRIO},
	TIMER_GPIOB_9, 					//Pinx_ use for a probe
	UP,
	Init_DelayValue,					//Init value
	Init_DelayValue

};

void TIM6_Handler(void)
{
	TIMER6_InterrupFuntion(TIM6, &TIMER6_Conf);

}

int main(void)
{
	TIMERx_Config(TIMER6_Conf, TIM6);

	USARTx_AsynConfig(USARTx_Conf, USART1, GPIOA);
	USARTx_Start(USARTx_Conf, USART1);

	USARTx_InitTrans(USART1, true, "HOLA\0");
	//USARTx_Stop(USART1);

	while(1) //CICLO INFINITO
	{
		TIMERx_Delay(TIM6, &TIMER6_Conf, Delay_1000ms);
		GPIOx_LED(GPIOB);
		TIMERx_Delay(TIM6, &TIMER6_Conf, Delay_1000ms);
		GPIOx_LED(GPIOB);

		//USARTx_InitTrans(USART1, false, "HOLA\0");

	}
}
