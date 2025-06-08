/*
 * RCC.h
 *
 *  Created on: 15 nov 2022
 *      Author: jurl9
 */



#ifndef RCC_H_
#define RCC_H_

#include "stm32l452xx.h"

typedef enum{
	RTC_LSE = RCC_BDCR_RTCSEL_0,
	RTC_LSI = RCC_BDCR_RTCSEL_1,
	RTC_HSE = (RCC_BDCR_RTCSEL_0 | RCC_BDCR_RTCSEL_1),
	RTC_NULL = RCC_BDCR_RTCSEL_NULL
} RTCCLKSRC_TypeDef;

typedef enum{
	HSE = 8,
	HSI = 16,
	MIN_PLL = 24,
	MAX_PLL = 180
} SYSCLK_TypeDef;

typedef enum{
	MSI_100kHz = RCC_CR_MSIRANGE_0,
	MSI_200kHz = RCC_CR_MSIRANGE_1,
	MSI_400kHz = RCC_CR_MSIRANGE_2,
	MSI_800kHz = RCC_CR_MSIRANGE_3,
	MSI_1MHz   = RCC_CR_MSIRANGE_4,
	MSI_2MHz   = RCC_CR_MSIRANGE_5,
	MSI_4MHz   = RCC_CR_MSIRANGE_6,
	MSI_8MHz   = RCC_CR_MSIRANGE_7,
	MSI_16MHz  = RCC_CR_MSIRANGE_8,
	MSI_24MHz  = RCC_CR_MSIRANGE_9,
	MSI_32MHz  = RCC_CR_MSIRANGE_10,
	MSI_48MHz  = RCC_CR_MSIRANGE_11
} MSICLK_TypeDef;

bool SystClock_Init(SYSCLK_TypeDef sysCLK, uint8_t sourceSYS, uint8_t sourcePLL, uint8_t preAHB1, uint8_t preAPB1, uint8_t preAPB2);
void SystCLK_SetHSION();
void SystCLK_MSI16();
void SystCLK_SetHSEON();
void SystCLK_SetPLLON(uint8_t sourcePLL);
uint8_t Calculate_Pot2(uint8_t pot);
void SystCLK_SetPres(uint8_t usysCLK, uint8_t preAHB1, uint8_t preAPB1, uint8_t preAPB2);
void SystCLK_CalculatePLLCFGR(SYSCLK_TypeDef usysCLK, uint8_t sourceSYS, uint8_t PLLCLK,uint8_t preAHB1, uint8_t preAPB1, uint8_t preAPB2, uint8_t up);
uint8_t SystCLK_GetPLLMStart(uint32_t freq_100, uint8_t valueCLK, uint8_t PLLM, uint8_t up);
uint16_t SystCLK_GetPLLNStart(uint32_t freq_100, uint8_t valueCLK, uint8_t PLLM, uint16_t PLLN);
uint8_t SystCLK_CalculatePLL_P_R(uint32_t freq_100, uint8_t valueCLK, uint16_t SYSCLK, uint8_t PLLM, uint16_t PLLN, uint8_t PLL_P_R, uint8_t up);
void SystCLK_SetPLLPredet();
void RTCCLK_SetCLK(uint16_t RTC_CLK_SEL);
void SystCLK_SetMSI(uint8_t MSI_clkSel);

#endif /* RCC_H_ */
