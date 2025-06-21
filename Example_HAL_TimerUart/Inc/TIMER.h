#ifndef TIMER_H_
#define TIMER_H_

#define ONE_SHOT false

typedef struct
{
	uint8_t	TIMERx_Clk;
	uint16_t TIMERx_IRQ[2]; //USARTx_IRQ[] = {Interrupt Number, Priority}
	uint8_t Pinx_; 			//Pinx_ use for a probe
	bool TIMx_Direc_Mode;
	uint32_t TIMERx_Delay;	//Fixed TIMER interrupt count number
	uint32_t Follower_Delay;//Counting variable. It should be equal to Fixed TIMERx_Delay to reboot TIMER
}TIMER_Config;

typedef enum
{
	//Priority Interrupt
	TIMER6_PRIO 			= 6,

	//TIMER MODE COUNTER
	UP						= 0,
	DOWM					= 1,
	COUNTER_DIR				= 4,
	MODE_OneShot			= 0x08,
	MODE_Period				= 0X01,

	//TIMER CLK
	TIMER6_CLK 				= 4,
	TIMER15_CLK				= 16,
	TIMER16_CLK				= 17,

	//TIMER_GPIO_Probe
	TIMER_GPIOB_9			= 9,

	//TIMER Config
	TIMER_NOT_DIV			= 8,
	NOT_COMPARE				= 0,
	NOT_SLAVE				= 0x7,
	NOT_REP					= 0,
	//DELAY_BASE				= 0xFFFF-0X0018,
	DELAY_BASE				= 0,
	ARR_BIT					= 7,
	URS_BIT					= 2,
	UDIS_BIT				= 0x02,
	ARR_INIT				= 0x1F00,


	//TIMER Int Enable
	TIMER_INT_ENABLE		= 0,
	TIMER_CLEAR_INTERRUPT 	= 0x0,
	TIMER_INT_BREAK			= 7,
	FOLLOWER_INIT			= 1,
	TIMER_ENABLE			= 0
}TIMER_ConfigConst;

/*
 * Prescaladores para la función de Delay_Timer()
 * */

typedef enum
{
	Init_DelayValue	= 0,

	Delay_1ms		= 1,
	Delay_2ms		= 3,
	Delay_5ms		= 9,

	Delay_10ms		= 19,
	Delay_20ms		= 39,
	Delay_50ms		= 100,

	Delay_100ms		= 200,
	Delay_200ms		= 400,
	Delay_500ms		= 1000,
	Delay_1000ms	= 2000,
	Delay_2000ms	= 4000,
	Delay_5000ms	= 10000,
	Delay_10000ms	= 20000,
	Delay_20000ms	= 40000,
	Delay_50000ms	= 100000,
	Delay_60000ms	= 120000
	/*	Delay_60000ms	= 618*/
}Delay_ms;


/*
 * Prescaladores para minutos, función TIMER_TimeOut()
 * */
#define TimeOut_1min	1
#define TimeOut_2min	2
#define TimeOut_3min	3
#define TimeOut_4min	4
#define TimeOut_5min	5

//TIMER Delay funtion
void TIMER6_InterrupFuntion(TIM_TypeDef *, TIMER_Config *);
void TIMERx_Delay(TIM_TypeDef *, TIMER_Config *, uint32_t);

//TIMER Configurate Funtion
void TIMERx_Config(TIMER_Config, TIM_TypeDef *);