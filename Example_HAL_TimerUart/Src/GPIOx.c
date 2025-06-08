/*
 * GPIOx.c
 *
 *  Created on: 15 nov 2022
 *      Author: jurl9
 */
#include "GPIOx.h"

void GPIOx_LED(GPIO_TypeDef *Port_){
	Port_->ODR ^= 0x02200; //bit 9 & bit 13
}

void GPIOx_InitAF(GPIO_TypeDef *Port_, uint8_t Pin_, uint8_t OTYPER_, uint8_t OSPEEDR_, uint8_t AFR_ ){ //L45
	CLEAR_BIT(Port_->MODER,(3 << (Pin_ * 2)));//Alternate Function on Pin x=1,...,15 /L45
	SET_BIT(Port_->MODER,(GPIO_MODER_MODE_AF << (Pin_ * 2)));//Alternate Function on Pin x=1,...,15 /L45
	SET_BIT(Port_->OTYPER,((OTYPER_ & 1) << (Pin_)));//Opend Drain or push pull
	SET_BIT(Port_->OSPEEDR,(OSPEEDR_ << (Pin_ * 2)));//High Speed
	if(Pin_ > 7){
		SET_BIT(Port_->AFR[1],(AFR_ <<((Pin_ - 8) * 4)));
	}
	else{
		SET_BIT(Port_->AFR[0],(AFR_ << (Pin_ * 4)));
	}
	//Veificar IDR? Debe estar en 1 los puertos
}

void GPIOx_InitIO(GPIO_TypeDef *Port_, uint8_t Pin_, uint8_t IO, bool PUR){ //l45
	if(IO == GPIO_MODER_OUTPUT){
		CLEAR_BIT(Port_->MODER,(3 << (Pin_ * 2)));
		SET_BIT(Port_->MODER,(GPIO_MODER_OUTPUT << (Pin_ * 2))); // Salida
	}
	else{
		Port_->IDR &= 0;
		CLEAR_BIT(Port_->MODER,(0x3 << (Pin_ * 2))); // Entrada
	}
	if(PUR){
		SET_BIT(Port_->PUPDR,(GPIO_PUPDR_PUPD0_0 << (Pin_ * 2)));//Resistencias Pull UP
	}
	else{
		CLEAR_BIT(Port_->PUPDR,(GPIO_PUPDR_PUPD0) << (Pin_ * 2));//Desactiva
	}
}

void GPIO_EnPort(GPIO_TypeDef *port){//L45
	if(port == GPIOA){
		SET_BIT(RCC->AHB2ENR,RCC_AHB2ENR_GPIOAEN);
	}
	else if(port == GPIOB){
		SET_BIT(RCC->AHB2ENR,RCC_AHB2ENR_GPIOBEN);
	}
	else if(port == GPIOC){
		SET_BIT(RCC->AHB2ENR,RCC_AHB2ENR_GPIOCEN);
	}
	else if(port == GPIOD){
		SET_BIT(RCC->AHB2ENR,RCC_AHB2ENR_GPIODEN);
	}
	else if(port == GPIOE){
		SET_BIT(RCC->AHB2ENR,RCC_AHB2ENR_GPIOEEN);
	}
	else if(port == GPIOH){
		SET_BIT(RCC->AHB2ENR,RCC_AHB2ENR_GPIOHEN);
	}
}
