#ifndef TIMER_H_
#define TIMER_H_

#include "stm32l452xx.h"


#define ONE_SHOT false

typedef struct
{
  __IO uint32_t CR1;         /*!< TIM control register 1,                   Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM control register 2,                   Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< TIM slave mode control register,          Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM DMA/interrupt enable register,        Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM status register,                      Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< TIM event generation register,            Address offset: 0x14 */
  __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1,      Address offset: 0x18 */
  __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2,      Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< TIM capture/compare enable register,      Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM counter register,                     Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< TIM prescaler,                            Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,                 Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< TIM repetition counter register,          Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,           Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,           Address offset: 0x38 */
  __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,           Address offset: 0x3C */
  __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,           Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< TIM break and dead-time register,         Address offset: 0x44 */
  __IO uint32_t DCR;         /*!< TIM DMA control register,                 Address offset: 0x48 */
  __IO uint32_t DMAR;        /*!< TIM DMA address for full transfer,        Address offset: 0x4C */
  __IO uint32_t OR1;         /*!< TIM option register 1,                    Address offset: 0x50 */
  __IO uint32_t CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x54 */
  __IO uint32_t CCR5;        /*!< TIM capture/compare register5,            Address offset: 0x58 */
  __IO uint32_t CCR6;        /*!< TIM capture/compare register6,            Address offset: 0x5C */
  __IO uint32_t OR2;         /*!< TIM option register 2,                    Address offset: 0x60 */
  __IO uint32_t OR3;         /*!< TIM option register 3,                    Address offset: 0x64 */
} TIM_TypeDef;

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



/* POR REVISAR*/
void Timer_TimeOut(void);
#endif /* TIMER_H_ */

/* Verifica si se acabo el tiempo
 * 1 se acabo
 * 0 continua
 * */
int getTimeOut1(void);
