/*
 * GPIOx.h
 *
 *  Created on: 15 nov 2022
 *      Author: jurl9
 */

#ifndef GPIOX_H_
#define GPIOX_H_

#include "stm32l452xx.h"

void GPIOx_InitAF(GPIO_TypeDef *Port_, uint8_t Pin_, uint8_t OTYPER_, uint8_t OSPEEDR_, uint8_t AFR_ );
void GPIOx_InitIO(GPIO_TypeDef *Port_, uint8_t Pin_, uint8_t IO, bool PUR);
void RCC_EnPort(GPIO_TypeDef *port);
void RESETME(GPIO_TypeDef *Port_);

void GPIOx_LED(GPIO_TypeDef *Port_);

#endif /* GPIOX_H_ */
