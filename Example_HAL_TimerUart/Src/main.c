#include "RCC.h"
#include "TIMER.h"
#include "UART.h"
#include "GPIOx.h"

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

void TIM6_DACUNDER_IRQHandler(void)
{
	TIMER6_InterrupFuntion(TIM6, &TIMER6_Conf);

}

int main(void)
{

	SystCLK_SetMSI(MSI_16MHz); // selección del reloj de 16Mhz

/********************CONFIGURACIÓN DE  TIMER6**********************/
/*Se hacen pruebas de TIMER6 para uso de Delay en envio de datos*/
	TIMERx_Config(TIMER6_Conf, TIM6);

/********************CONFIGURACIÓN DE  USART3**********************/
	GPIO_EnPort(GPIOB);//configura reloj en puerto B
	GPIO_EnPort(GPIOA);
	GPIOx_InitIO(GPIOB, TIMER6_Conf.Pinx_, GPIO_MODER_OUTPUT, false);
	GPIOx_InitIO(GPIOB, 13, GPIO_MODER_OUTPUT, false);	//Puerto PB13 configurado como salida (LED)

	USARTx_AsynConfig(USARTx_Conf, USART1, GPIOA);
	USARTx_Start(USARTx_Conf, USART1);

	USARTx_InitTrans(USART1, true, "HOLA LIESE\0");
	//USARTx_Stop(USART1);

	while(1) //CICLO INFINITO
	{
		TIMERx_Delay(TIM6, &TIMER6_Conf, Delay_1000ms);
		GPIOx_LED(GPIOB);
		TIMERx_Delay(TIM6, &TIMER6_Conf, Delay_1000ms);
		GPIOx_LED(GPIOB);

		//USARTx_InitTrans(USART1, false, "HOLA\0");
		//USARTx_InitTrans(USART1, false, " LIESE\0");

	}
}
