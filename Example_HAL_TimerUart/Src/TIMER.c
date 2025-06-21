/** @file TIMER.c
*  @brief The implementation for HAL function of general TIMER module.
*/

#include "TIMER.h"

extern int bandera;

void TIMER6_InterrupFuntion(TIM_TypeDef *TIMERx_, TIMER_Config *TIMER_Config)
{
	TIMERx_->CNT = Init_DelayValue;
	CLEAR_BIT(TIMERx_->SR, (1<<TIMER_CLEAR_INTERRUPT));

#if ONE_SHOT
	if ( TIMER_Config->Follower_Delay != TIMER_Config->TIMERx_Delay )
	{
		TIMER_Config->Follower_Delay++;
		SET_BIT(TIMERx_->CR1, MODE_Period);

	}else
	{
		CLEAR_BIT(TIMERx_->DIER, (1<<TIMER_INT_ENABLE));

	}
#else //Period
	if ( TIMER_Config->Follower_Delay != TIMER_Config->TIMERx_Delay )
	{
		TIMER_Config->Follower_Delay++;

	}else
	{
		CLEAR_BIT(TIMERx_->CR1, MODE_Period);
		CLEAR_BIT(TIMERx_->DIER, (1<<TIMER_INT_ENABLE));

	}
#endif

}

void TIMERx_Delay(TIM_TypeDef *TIMERx_, TIMER_Config *TIMER_Config, uint32_t Delay_ms)
{
	if( Delay_ms <= Init_DelayValue )
	{
			return;

	}
	TIMER_Config->TIMERx_Delay = Delay_ms;

	SET_BIT(TIMERx_->PSC, (DELAY_BASE) );
	SET_BIT(TIMERx_->DIER, (1<<TIMER_INT_ENABLE));

#if ONE_SHOT
	SET_BIT(TIMERx_->CR1, MODE_OneShot|MODE_Period);
	while ( TIMERx_->CR1 & MODE_Period );

#else
	SET_BIT(TIMERx_->CR1, MODE_Period);
	SET_BIT(TIMERx_->ARR, ARR_INIT );

	while ( TIMERx_->CR1 & MODE_Period );

#endif

	TIMERx_->CNT = Init_DelayValue;
	TIMER_Config->TIMERx_Delay = Init_DelayValue;
	TIMER_Config->Follower_Delay = Init_DelayValue;

}

void TIMERx_Config(TIMER_Config TIMER_Config, TIM_TypeDef *TIMERx_)
{
	switch(TIMER_Config.TIMERx_Clk)
	{
	case TIMER6_CLK:

		SET_BIT(RCC->APB1ENR1, (1 << TIMER6_CLK));
		break;

	case TIMER15_CLK:

		SET_BIT(RCC->APB2ENR, (1<<TIMER15_CLK));
		CLEAR_BIT(TIMERx_->DIER, (1<<TIMER_INT_BREAK));
		break;

	case TIMER16_CLK:

		SET_BIT(RCC->APB2ENR, (1<<TIMER16_CLK));
		CLEAR_BIT(TIMERx_->DIER, (1<<TIMER_INT_BREAK));
		break;

	default:
		return;

	}

	InterruptFuntion_Config(TIMER_Config.TIMERx_IRQ[0], TIMER_Config.TIMERx_IRQ[1]);

	CLEAR_BIT(TIMERx_->CR1, (1<<TIMER_ENABLE));

	SET_BIT(TIMERx_->CR1, (1<<URS_BIT));
	SET_BIT(TIMERx_->CR1, (1<<ARR_BIT));

	TIMERx_->CNT = Init_DelayValue;

	TIMERx_->ARR = (ARR_INIT & 0xFFFF);

	if ( TIMER_Config.TIMERx_Clk == TIMER15_CLK || TIMER_Config.TIMERx_Clk == TIMER16_CLK )
	{
		CLEAR_BIT(TIMERx_->CR1, (3<<TIMER_NOT_DIV));
		CLEAR_BIT(TIMERx_->CR2, (1<<NOT_COMPARE));
		CLEAR_BIT(TIMERx_->SMCR, (1<<NOT_SLAVE));
		SET_BIT(TIMERx_->RCR, NOT_REP);

		if ( TIMER_Config.TIMx_Direc_Mode )
		{
			SET_BIT(TIMERx_->CR1, (1<<COUNTER_DIR));

		}else
		{
			CLEAR_BIT(TIMERx_->CR1, (1<<COUNTER_DIR));

		}

	}

}
