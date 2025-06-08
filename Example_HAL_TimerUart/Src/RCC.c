/*
 * RCC.c
 *
 *  Created on: 15 nov 2022
 *      Author: jurl9
 */

#include "RCC.h"
#include "GPIOx.h"

/*RCC es 16MHz de manera predeterminada
//Configuración predeterminada RCC
//PLLM: 0.95MHz-2.1MHz
//PLLN:100MHz-432MHz
//PLLP_R: 24MHz-180MHz
//AHB1: 2MHz-180MHz
//APB1: 2MHz-45MHz
 * SYSCLOCK = ( (SOURCEPLL / PRE_PLLM) * MUL_PLLN ) / PRE_PLLP -> Seguir en este orden la configuración
 * para cumplir con el rango de valores mostrados arriba
 * APB1CLOCK = ( SYSCLOCK / PRE_AHB1 ) / APB1
 * APB1CLK in MHz
 */
bool SystClock_Init(SYSCLK_TypeDef sysCLK, uint8_t sourceSYS, uint8_t sourcePLL, uint8_t preAHB1, uint8_t preAPB1, uint8_t preAPB2){  //L45
	uint8_t systemClock = sysCLK;
	SET_BIT(RCC->APB1ENR1,RCC_APB1ENR1_PWREN); //L45
	CLEAR_BIT(PWR->CR1,(0x3 << PWR_CR1_VOS_Pos));//Limpiamos  //L45
	SET_BIT(PWR->CR1,(1 << PWR_CR1_VOS_Pos));//Selecciona modo 3 (120MHz Max) //L45
	//Se ignora sourcePLL y SYSCLK si se escoge directamente el valor de la fuente
	if(sysCLK == HSI){//HSI
		RCC->CFGR = RCC_CFGR_SW_HSI; //HSI como fuente del sistema
		SystCLK_SetPres(systemClock, preAHB1, preAPB1, preAPB2);
		SystCLK_SetHSION();
	}
	else if(sysCLK == HSE){//HSE
		RCC->CFGR = RCC_CFGR_SW_HSE; //HSE como fuente del sistema
		SystCLK_SetPres(systemClock, preAHB1, preAPB1, preAPB2);
		SystCLK_SetHSEON();
	}
	else{
		if((sysCLK >= MIN_PLL) && (sysCLK <= MAX_PLL)){//Min out CLK 24MHz, max 180MHz, puede ser PLLP o PLLR
			if(sourcePLL == 0){//Source PLL -> HSI = 16 MHz, se trabajan números enteros
				SystCLK_CalculatePLLCFGR(sysCLK, sourceSYS, HSI, preAHB1, preAPB1, preAPB2, 8);//Configura e inicializa
			}
			else{//Source PLL -> HSE
				RCC_EnPort(GPIOH);
				SystCLK_CalculatePLLCFGR(sysCLK, sourceSYS, HSE, preAHB1, preAPB1, preAPB2, 1);//Configura e inicializa
			}
		}
		else{//Configuración predeterminada en PLL
			SystCLK_SetPLLPredet();//SYS = 40MHz, APB1 = 10MHz
		}
	}
	return true;
}

//
uint8_t Calculate_Pot2(uint8_t pot){ //L45
	uint8_t value = 1;
	while(pot > 0){
		value *= 2;
		pot--;
	}
	return value;
}
//
void SystCLK_SetPres(uint8_t usysCLK, uint8_t preAHB1, uint8_t preAPB1, uint8_t preAPB2){ //L45
	uint8_t divAHB1 = (usysCLK) / (Calculate_Pot2(preAHB1));
	uint8_t divAPB1 = 0;//(SYSCLKCFG->SYSCLK) / (Calculate_Pot2(preAHB1+preAPB1));
	uint8_t divAPB2 = 0;//(SYSCLKCFG->SYSCLK) / (Calculate_Pot2(preAHB1+preAPB2));
	uint8_t i = 0;
	uint32_t decimal;
	uint8_t AHB1CLK;

	if((usysCLK) & 1){//Si es un número impar
		usysCLK++;//Lo hacemos Par
		divAHB1 = (usysCLK) / (Calculate_Pot2(preAHB1));
	}

	if(preAHB1 > 4){
		divAHB1 = (usysCLK) / (Calculate_Pot2(preAHB1 + 1));
	}

	if(divAHB1 >= 2){//Dentro del rango
		if(preAHB1 != 0){
			SET_BIT(RCC->CFGR,((7 + preAHB1) << RCC_CFGR_HPRE_Pos));
		}
		AHB1CLK = divAHB1;
	}
	else{
		SET_BIT(RCC->CFGR,(RCC_CFGR_HPRE_DIV1));//Dividir por 1 AHB1
		AHB1CLK = usysCLK;
		preAHB1 = 0;
	}

	//Calculamos nuevos valores
	divAPB1 = (usysCLK) / (Calculate_Pot2(preAHB1 + preAPB1));
	divAPB2 = (usysCLK) / (Calculate_Pot2(preAHB1 + preAPB2));

	if((divAPB1 >= 2) && (divAPB1 <= 45)){
	    if(preAPB1 != 0){
	    	SET_BIT(RCC->CFGR,((3 + preAPB1) << RCC_CFGR_PPRE1_Pos));
		}
	    decimal = (((uint32_t)(divAPB1)) * 100) - ((100 * (usysCLK)) / (Calculate_Pot2(preAHB1 + preAPB1)));
	}
	else{
		i = 0;
		while((divAPB1 <= 45) || (i >= 5)) {
			divAPB1 = (usysCLK) / (Calculate_Pot2(i + preAHB1));
		}
		if(i != 0){
			SET_BIT(RCC->CFGR,((3 + i) << RCC_CFGR_PPRE1_Pos));
		}
		decimal = (((uint32_t)(divAPB1)) * 100) - ((100 * (usysCLK)) / (Calculate_Pot2(preAHB1 + i)));
	}

	if((divAPB2 >= 2) && (divAPB2 <= 45)){
		if(preAPB2 != 0){
			SET_BIT(RCC->CFGR,((3 + preAPB2) << RCC_CFGR_PPRE2_Pos));
		}
		decimal = (((uint32_t)(divAPB2)) * 100) - ((100 * (usysCLK)) / (Calculate_Pot2(preAHB1 + preAPB2)));
	}
	else{
		i=0;
		while((divAPB2 <= 45) || (i >= 5)) {
			divAPB2 = (usysCLK) / (Calculate_Pot2(i + preAHB1));
		}
		if(i!=0){
			RCC->CFGR |= ((3 + i) << RCC_CFGR_PPRE2_Pos);
		}
		decimal = (((uint32_t)(divAPB2)) * 100) - ((100 * (usysCLK)) / (Calculate_Pot2(preAHB1 + i)));
	}

}
//L45

void SystCLK_SetHSION(){ //L45
	RCC->ICSCR = ((0x10 << RCC_ICSCR_HSITRIM_Pos) | (0x68 << RCC_ICSCR_HSICAL_Pos));//Configuración Para calibración
	SET_BIT(RCC->CR,RCC_CR_HSION);
	while((RCC->CR & RCC_CR_HSIRDY)==0);
	RCC->CFGR = 0x1UL;
}

void SystCLK_SetMSI(uint8_t MSI_clkSel){
	while((RCC->CR && RCC_CR_MSION) == 0);
	SET_BIT(RCC->CR,RCC_CR_MSIRGSEL);
	CLEAR_BIT(RCC->CR,RCC_CR_MSIRANGE);
	SET_BIT(RCC->CR,MSI_clkSel);
}

void SystCLK_SetPLLON(uint8_t sourcePLL){ //L45
	if(sourcePLL==1){
		RCC->CR = (RCC_CR_PLLON | RCC_CR_HSEON);//PLL ON, HSE ON, HSE-> Osc. PLL
	}
	else{
		RCC->ICSCR = ((0x10 << RCC_ICSCR_HSITRIM_Pos)|(0x68 << RCC_ICSCR_HSICAL_Pos));//Configuración Para calibración
		SET_BIT(RCC->CR,(RCC_CR_PLLON | RCC_CR_HSION));//PLL ON, HSI ON, HSI-> Osc. PLL
	}
	while((RCC->CR && RCC_CR_PLLRDY) == 0); //L45

}
//
void SystCLK_CalculatePLLCFGR(SYSCLK_TypeDef usysCLK, uint8_t sourceSYS, uint8_t PLLCLK,uint8_t preAHB1, uint8_t preAPB1, uint8_t preAPB2, uint8_t up){ //L45
	uint32_t auxClk = 0;
	uint16_t sysCLK_PLL = 100 * (usysCLK);
	uint8_t PLLM_ = 0, PLL_P_R_ = 2;
	uint16_t PLLN_ = 50;
	if(up != 8){
		PLLM_ = 2;
		auxClk =  ((100 * PLLCLK) / (PLLM_));
		PLLM_ = SystCLK_GetPLLMStart(auxClk, PLLCLK, PLLM_, 1);//Obtiene el valor de PLLM para iterar
	}
	else{
		PLLM_ = 8;
		auxClk =  ((100*PLLCLK) / (PLLM_));
	}
	while((PLLM_ <= PLLCLK) && (auxClk != sysCLK_PLL)){//Si las dos décimas son diferente de cero se itera
		PLLN_ = 50;
		auxClk =  ( (100 * PLLCLK) / (PLLM_)) * PLLN_ ;
		PLLN_ = SystCLK_GetPLLNStart(auxClk, PLLCLK, PLLM_, PLLN_);//Obtiene el valor de PLLN inicial
		while((PLLN_<= 432) && (auxClk != sysCLK_PLL) && (auxClk <= 43200)){
			if(((auxClk / 7) < sysCLK_PLL) || ((auxClk / 8) < sysCLK_PLL)){
				PLL_P_R_ = 2;//PLLP o PLLR
				auxClk /= PLL_P_R_;
				if(sourceSYS == 2){//PLLP values: 2, 4, 6, 8
					PLL_P_R_ = SystCLK_CalculatePLL_P_R(auxClk, PLLCLK, sysCLK_PLL, PLLM_, PLLN_, PLL_P_R_, 2);
				}
				else{//PLLR values: 2-7
					PLL_P_R_ = SystCLK_CalculatePLL_P_R(auxClk, PLLCLK, sysCLK_PLL, PLLM_, PLLN_, PLL_P_R_, 1);
				}
				if(PLL_P_R_ > 8){
					PLLN_++;
					auxClk = (100 * PLLCLK / PLLM_) * PLLN_;
				}
				else{
					auxClk = ((100 * PLLCLK / PLLM_) * PLLN_) / PLL_P_R_;//Se obtienen los valores esperados
				}
			}
			else{
				PLLN_ = 433;
			}
		}
		if(auxClk != sysCLK_PLL){
			PLLM_ += up;
		}
	}

	if((auxClk != sysCLK_PLL) && (PLL_P_R_ > 8) && (PLLM_ > PLLCLK) && (PLLN_ > 432)){//No se ecnontró un valor adecuado
		SystCLK_SetPLLPredet(); //SYS = 80MHz, APB1, APB2 = 40MHz
	}
	//L45
	else{//Se llenan los valores
		uint8_t sysCLK_PLLdiv = auxClk / 100;
		if(sourceSYS == 2){//PLLP como fuente del sistema
			PLL_P_R_= ((PLL_P_R_/2) - 1);//
			RCC->CFGR = RCC_CFGR_SW_PLL;
			SystCLK_SetPres(sysCLK_PLLdiv, preAHB1, preAPB1, preAPB2);
			RCC->PLLCFGR = ((PLLM_ << RCC_PLLCFGR_PLLM_Pos) | (PLLN_ << RCC_PLLCFGR_PLLN_Pos) | (PLL_P_R_ << RCC_PLLCFGR_PLLP_Pos) | RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLR_1);//Configurar antes de activar
		}
		if(PLLCLK == HSE){//HSE PLL SOURCE
			SET_BIT(RCC->PLLCFGR,RCC_PLLCFGR_PLLSRC_HSE);
			SystCLK_SetPLLON(1);
		}
		else{//HSI PLL SOURCE
			SET_BIT(RCC->PLLCFGR,RCC_PLLCFGR_PLLSRC_HSI);
			SystCLK_SetPLLON(0);
		}
	}
}

uint8_t SystCLK_GetPLLMStart(uint32_t freq_100, uint8_t valueCLK, uint8_t PLLM, uint8_t up){ //L45
	uint8_t PLLM_ = PLLM;
	while(freq_100 > 200){//Busca el valor de M desde el cuál se puede iterar
		PLLM_ += up;
		freq_100 = ((100 * valueCLK) / PLLM_);
	}
	return PLLM_;
}

uint16_t SystCLK_GetPLLNStart(uint32_t freq_100, uint8_t valueCLK, uint8_t PLLM, uint16_t PLLN){  //L45
	uint16_t PLLN_ = PLLN;
	while(freq_100 < 10000){//Busca el valor de N desde el cuál se puede iterar
		PLLN_++;
		freq_100 = ((100 * valueCLK) / PLLM) * PLLN;
	}
	return PLLN_;
}

uint8_t SystCLK_CalculatePLL_P_R(uint32_t freq_100, uint8_t valueCLK, uint16_t SYSCLK, uint8_t PLLM, uint16_t PLLN, uint8_t PLL_P_R, uint8_t up){ //L45
	uint8_t PLL_P_R_ = PLL_P_R;
	while(freq_100 > 18000){//Busca el valor desde el cuál se puede iterar
		PLL_P_R_ += up;
		freq_100 = (((100 * valueCLK) / PLLM) * PLLN) / PLL_P_R_;
	}
	if (freq_100 >= 2400){
		//freq_100=1;//aseguramos que etre al
		while((PLL_P_R_ <= 8) && (freq_100 != SYSCLK)){
			PLL_P_R_ += up;
			freq_100 = (((100 * valueCLK) / PLLM) * PLLN) / PLL_P_R_;
			if((freq_100 != SYSCLK) && ((PLL_P_R_ == 8) | (PLL_P_R_ == 7))){//Value >= 10
				PLL_P_R_ += 2;
			}
		}
	}
	else{
		PLL_P_R_ = 9;
	}
	return PLL_P_R_;
}
//
void SystCLK_SetPLLPredet(){
	RCC->CFGR = (RCC_CFGR_SW_PLL | RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV2) ;//SW = PLLP Source, AHB=1, APB1=2, APB2=2, APB1 Source 40MHz para I2C  //l45
	RCC->PLLCFGR = (RCC_PLLCFGR_PLLM_1 | (80 << RCC_PLLCFGR_PLLN_Pos) | (1 << RCC_PLLCFGR_PLLP_Pos) | RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLR_1);//PLL source = HSE, PLLM =80 , PLLN = 40, PLLP = 4. SYS = 80 MHz; configurar antes de activar
	SET_BIT(RCC->PLLCFGR,RCC_PLLCFGR_PLLSRC_HSE);
	SystCLK_SetPLLON(1);
}

void RTCCLK_SetCLK(uint16_t RTC_CLK_SEL){
	SET_BIT(RCC->APB1ENR1,RCC_APB1ENR1_PWREN); // Habilita Power Control
	SET_BIT(PWR->CR1,PWR_CR1_DBP); // Habilitar escritura en los registros de RTC
	while((PWR->CR1 & PWR_CR1_DBP) != PWR_CR1_DBP); // ¿Se puede proceder con la escritura en el registro?
	//RCC_BDCR = 0x0000; // Clear del reset del dominio de respaldo (Backup domain reset)
	if (RTC_CLK_SEL == RTC_LSE){
		SET_BIT(RCC->BDCR,RCC_BDCR_LSEON); // Habilitar reloj LSE
		while((RCC->BDCR & RCC_BDCR_LSERDY) != RCC_BDCR_LSERDY); // ¿Está listo el reloj LSE listo?
	}
	SET_BIT(RCC->BDCR,RTC_CLK_SEL); // Seleccionar reloj LSE como reloj del RTC
	SET_BIT(RCC->BDCR,RCC_BDCR_RTCEN); // Habilitar reloj del RTC
	CLEAR_BIT(PWR->CR1,PWR_CR1_DBP); // Deshabilitar escritura en el registro RCC_BDCR
}


