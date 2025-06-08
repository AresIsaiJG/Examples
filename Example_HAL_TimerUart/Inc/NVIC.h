/*
 * NVIC.h
 *
 *  Created on: 15 nov 2022
 *      Author: jurl9
 */

#ifndef NVIC_H_
#define NVIC_H_

#include "stm32l452xx.h"

void NVIC_SetCFGR(uint8_t position, uint8_t priority);

#endif /* NVIC_H_ */
