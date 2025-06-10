/*
 * GPIO.hpp
 *
 *  Created on: Jun 6, 2025
 *      Author: aresi
 */

#ifndef PERIPH_HPP_
#define PERIPH_HPP_

#include "Reg32.hpp"

namespace GPIO_Conf
{
enum class Pin_EnumClass : uint8_t
{
	Pin0	= 0,
	Pin1	= 1,
	Pin2	= 2,
	Pin3	= 3,
	Pin4	= 4,
	Pin5	= 5,
	Pin6	= 6,
	Pin7	= 7,
	Pin8	= 8,
	Pin9	= 9,
	Pin10	= 10,
	Pin11	= 11,
	Pin12	= 12,
	Pin13	= 13,
	Pin14	= 14,
	Pin15	= 15,
	NotUse	= 16
};

enum class AF_EnumClass : uint8_t
{
	AF0		= 0,
	AF1		= 1,
	AF2		= 2,
	AF3		= 3,
	AF4		= 4,
	AF5		= 5,
	AF6		= 6,
	AF7		= 7,
	AF8		= 8,
	AF9		= 9,
	AF10	= 10,
	AF11	= 11,
	AF12	= 12,
	AF13	= 13,
	AF14	= 14,
	AF15	= 15,
	NotUse	= 16
};

enum class Mode_EnumClass : uint8_t
{
	Mode_Input	= 0,
	Mode_Output = 1,
	Mode_AltFun = 2,
	Mode_Analog = 3,
	NotUse	= 4
};

enum class OType_EnumClass : uint8_t
{
	Mode_PushPull  = 0,
	Mode_OpenDrain = 1,
	NotUse	= 2
};

enum class UpDown_EnumClass : uint8_t
{
	Mode_NotPull	= 0,
	Mode_PullUp	  	= 1,
	Mode_PullDown 	= 2,
	NotUse	= 4
};

enum class Speed_EnumClass : uint8_t
{
	Mode_LowSpeed		= 0,
	Mode_MedSpeed		= 1,
	Mode_HighSpeed		= 2,
	Mode_VeryHighSpeed 	= 3,
	NotUse	= 4
};

typedef struct
{
	GPIO_Conf::Pin_EnumClass 	Pin;
	GPIO_Conf::AF_EnumClass 	AF;
	GPIO_Conf::Mode_EnumClass 	Mode;
	GPIO_Conf::OType_EnumClass 	OType;
	GPIO_Conf::UpDown_EnumClass Pull;
	GPIO_Conf::Speed_EnumClass	Speed;
	void (* ptrGpioISR)();
}GPIO_ConfigStruct;
}

namespace RCC_Conf
{
enum class AHB1_EnumClass : uint8_t
{
	GPIOA_Clk 	= 0,
	GPIOB_Clk 	= 1,
	GPIOC_Clk 	= 2,
	GPIOD_Clk 	= 3,
	GPIOE_Clk 	= 4,
	GPIOF_Clk 	= 5,
	GPIOG_Clk 	= 6,
	GPIOH_Clk	= 7,
	GPIOI_Clk 	= 8,
	CRC_Clk   	= 12,
	DMA1_Clk   	= 21,
	DMA2_Clk   	= 22,
	ETHMAC_Clk	= 25,
	OTGHS_Clk	= 29
};

enum class APB2_EnumClass : uint8_t
{
	TIM1_Clk 	= 0,
	TIM8_Clk 	= 1,
	USART1_Clk 	= 4,
	USART6_Clk 	= 5,
	ADC1_Clk 	= 8,
	ADC2_Clk 	= 9,
	ADC3_Clk 	= 10,
	SDIO_Clk	= 11,
	SPI1_Clk 	= 12,
	SYSCFG_Clk  = 14,
	TIM9_Clk   	= 16,
	TIM10_Clk   = 17,
	TIM11_Clk	= 18
};

typedef struct
{
	RCC_Conf::AHB1_EnumClass GPIOB_En;
	RCC_Conf::AHB1_EnumClass GPIOC_En;
	RCC_Conf::APB2_EnumClass SYSCFG_En;
}RCC_EnConfigStruct;
}

namespace SYSCFG_Conf
{
enum class EXTICR_EnumClass : uint8_t
{
	EXTI_PA	= 0,
	EXTI_PB	= 1,
	EXTI_PC	= 2,
	EXTI_PD	= 3,
	EXTI_PE	= 4,
	EXTI_PF	= 5,
	EXTI_PG	= 6,
	EXTI_PH	= 7,
	EXTI_PI	= 8,
	EXTI_PJ	= 9,
	EXTI_PK	= 10
};
}

namespace EXTI_Conf
{
enum class Trigger_EnumClass : uint8_t
{
	Mode_Rising		= 0,
	Mode_Falling	= 1,
	Mode_BothTrig	= 2
};

}

namespace NVIC_Conf
{
enum class Possition_EnumClass : uint8_t
{
	WWDG_Pos		= 0,
	PVD_Pos			= 1,
	TAMP_STAMP_Pos	= 2,
	RTC_WKUP_Pos	= 3,
	FLASH_Pos		= 4,
	RCC_Pos			= 5,
	EXTI0_Pos		= 6,
	EXTI1_Pos		= 7,
	EXTI2_Pos		= 8,
	EXTI3_Pos		= 9,
	EXTI4_Pos		= 10,
	DMA1_Str0_Pos	= 11,
	DMA1_Str1_Pos	= 12,
	DMA1_Str2_Pos	= 13,
	DMA1_Str3_Pos	= 14,
	DMA1_Str4_Pos	= 15,
	DMA1_Str5_Pos	= 16,
	DMA1_Str6_Pos	= 17,
	ADC_Pos			= 18,
	CAN1_Tx_Pos		= 19,
	CAN1_Rx0_Pos	= 20,
	CAN1_Rx1_Pos	= 21,
	CAN1_SCE_Pos	= 22,
	EXTI9_5_Pos		= 23,
	TIM1_Brk_TIM9_Pos		= 24,
	IM1_Up_TIM10_Pos		= 25,
	TIM1_Trg_Com_TIM11_Pos	= 26,
	TIM1_Cc_Pos		= 27,
	TIM2_Pos		= 28,
	TIM3_Pos		= 29,
	TIM4_Pos		= 30,
	I2C1_EV_Pos		= 31,
	I2C1_ER_Pos		= 32,
	I2C2_EV_Pos		= 33,
	I2C2_ER_Pos		= 34,
	SPI1_Pos		= 35,
	SPI2_Pos		= 36,
	USART1_Pos		= 37,
	USART2_Pos		= 38,
	USART3_Pos		= 39,
	EXTI15_9_Pos	= 40
};
}

namespace Peripheral
{

	template<std::uintptr_t GPIO_BASE>
	class GPIO
	{
	private:
		/*
		 * using se utiliza para crear alias de tipos de datos.
		 * Ideal para usar con templates.
		 * */
		struct GPIO_Reg {
		    using MODER 	= Reg32 < GPIO_BASE + 0x00 >;
		    using OTYPER 	= Reg32 < GPIO_BASE + 0x04 >;
		    using OSPEEDR 	= Reg32 < GPIO_BASE + 0x08 >;
		    using PUPDR 	= Reg32 < GPIO_BASE + 0x0C >;
		    using IDR 		= Reg32 < GPIO_BASE + 0x10 >;
		    using ODR 		= Reg32 < GPIO_BASE + 0x14 >;
		    using BSRR 		= Reg32 < GPIO_BASE + 0x18 >;
		    using LCKR 		= Reg32 < GPIO_BASE + 0x1C >;
		    using AFRL 		= Reg32 < GPIO_BASE + 0x20 >;
		    using AFRH 		= Reg32 < GPIO_BASE + 0x24 >;
		};

	public:

		static void GPIO_Config(GPIO_Conf::GPIO_ConfigStruct GPIO)
		{
			GPIO_Reg::MODER::setBits( static_cast< uint8_t >(GPIO.Mode), 2*static_cast< uint8_t >(GPIO.Pin) );
			GPIO_Reg::OTYPER::setBits( static_cast< bool >(GPIO.OType), static_cast< uint8_t >(GPIO.Pin) );
			GPIO_Reg::PUPDR::setBits( static_cast< uint8_t >(GPIO.Pull), 2*static_cast< uint8_t >(GPIO.Pin) );
			GPIO_Reg::OSPEEDR::setBits( static_cast< uint8_t >(GPIO.Speed), 2*static_cast< uint8_t >(GPIO.Pin) );

			if ( (static_cast< uint8_t >(GPIO.Mode) != static_cast<uint8_t>(GPIO_Conf::Mode_EnumClass::Mode_AltFun)) )
				return;

			if ( (static_cast< uint8_t >(GPIO.AF) <= static_cast< uint8_t >(GPIO_Conf::AF_EnumClass::AF7)) )
				GPIO_Reg::AFRL::setBits( static_cast< uint8_t >(GPIO.AF), static_cast< uint8_t >(GPIO.Pin) );
			else
				GPIO_Reg::AFRL::setBits( static_cast< uint8_t >(GPIO.AF), (static_cast< uint8_t >(GPIO.Pin) - static_cast< uint8_t >(GPIO_Conf::Pin_EnumClass::Pin8)) );

		}

		static void GPIO_WriteOut(const uint16_t Data)
		{
			GPIO_Reg::ODR::write( Data );
		}

		static void GPIO_ClearOut(const uint16_t Data)
		{
			GPIO_Reg::ODR::write( Data );
		}

		static void GPIO_WriteAtomic(GPIO_Conf::GPIO_ConfigStruct GPIO)
		{
			GPIO_Reg::BSRR::setBits( 1, static_cast< uint8_t >(GPIO.Pin) );
		}

		static void GPIO_ClearAtomic(GPIO_Conf::GPIO_ConfigStruct GPIO)
		{
			GPIO_Reg::BSRR::setBits( 1, (static_cast< uint8_t >(GPIO.Pin) + 16) );
		}

		static uint32_t GPIO_Read()
		{
			return GPIO_Reg::ODR::read();
		}

	};

	template<std::uintptr_t RCC_BASE>
	class RCC
	{
	private:
		struct RCC_Reg {
			using CR       	= Reg32 < RCC_BASE + 0x00 > ; // 0x00
	        using PLLCFGR	= Reg32 < RCC_BASE + 0x04 > ; // 0x04
	        using CFGR		= Reg32 < RCC_BASE + 0x08 > ; // 0x08
	        using CIR		= Reg32 < RCC_BASE + 0x0C > ; // 0x0C
	        using AHB1RSTR	= Reg32 < RCC_BASE + 0x10 > ; // 0x10
	        using AHB2RSTR	= Reg32 < RCC_BASE + 0x14 > ; // 0x14
	        using AHB3RSTR	= Reg32 < RCC_BASE + 0x18 > ; // 0x18
	        //uint32_t const RESERVED0; 					  // 0x1C
	        using APB1RSTR	= Reg32 < RCC_BASE + 0x20 > ; // 0x20
	        using APB2RSTR 	= Reg32 < RCC_BASE + 0x24 > ; // 0x24
	        //uint32_t const RESERVED1[2];				  // 0x28-0x2C
	        using AHB1ENR  	= Reg32 < RCC_BASE + 0x30 > ; // 0x30
	        using AHB2ENR	= Reg32 < RCC_BASE + 0x34 > ; // 0x34
	        using AHB3ENR	= Reg32 < RCC_BASE + 0x38 > ; // 0x38
	        //uint32_t const RESERVED2; 					  // 0x3C
	        using APB1ENR	= Reg32 < RCC_BASE + 0x40 > ; // 0x40
	        using APB2ENR	= Reg32 < RCC_BASE + 0x44 > ; // 0x44
	        //uint32_t const RESERVED3[2];				  // 0x48-0x4C
	        using AHB1LPENR = Reg32 < RCC_BASE + 0x50 > ; // 0x50
	        using AHB2LPENR	= Reg32 < RCC_BASE + 0x54 > ; // 0x54
	        using AHB3LPENR	= Reg32 < RCC_BASE + 0x58 > ; // 0x58
	        //uint32_t const RESERVED4; 					  // 0x5C
	        using APB1LPENR	= Reg32 < RCC_BASE + 0x60 > ; // 0x60
	        using APB2LPENR	= Reg32 < RCC_BASE + 0x64 > ; // 0x64
	        //uint32_t const RESERVED5[2];				  // 0x68-0x6C
	        using BDCR		= Reg32 < RCC_BASE + 0x70 > ; // 0x70
	        using CSR		= Reg32 < RCC_BASE + 0x74 > ; // 0x74
	        //uint32_t const RESERVED6[2];				  // 0x78-0x7C
	        using SSCGR		= Reg32 < RCC_BASE + 0x80 > ; // 0x80
	        using PLLI2SCFGR= Reg32 < RCC_BASE + 0x84 > ; // 0x84

		};

	public:
			static void AHB1_ClockEnable(RCC_Conf::AHB1_EnumClass AHB1x_Clk)
			{
					RCC_Reg::AHB1ENR::setBits( 1, static_cast< uint8_t >(AHB1x_Clk) );

			}

			static void APB2_ClockEnable(RCC_Conf::APB2_EnumClass APB2x_Clk)
			{
					RCC_Reg::APB2ENR::setBits( 1, static_cast< uint8_t >(APB2x_Clk) );

			}
	};

	template<std::uintptr_t SYSCFG_BASE>
	class SYSCFG
	{
	private:
		struct SYSCFG_Reg
		{
			using MEMRMP	= Reg32<SYSCFG_BASE + 0x00>;
			using PMC		= Reg32<SYSCFG_BASE + 0x04>;
			using EXTICR1	= Reg32<SYSCFG_BASE + 0x08>;
			using EXTICR2	= Reg32<SYSCFG_BASE + 0x0C>;
			using EXTICR3	= Reg32<SYSCFG_BASE + 0x10>;
			using EXTICR4	= Reg32<SYSCFG_BASE + 0x14>;
			using CMPCR		= Reg32<SYSCFG_BASE + 0x18>;
		};

		static uint8_t ShiftCalculate(GPIO_Conf::Pin_EnumClass Pin, const uint8_t Subtract)
		{
			volatile uint8_t Shift = static_cast< uint8_t >(Pin);

			while (Shift > Subtract - 1 )
				Shift -=Subtract;

			return Shift;
		}

	public:
		static void SYSCFG_EXTICR1Config(GPIO_Conf::GPIO_ConfigStruct GPIO, SYSCFG_Conf::EXTICR_EnumClass EXTICR_Port)
		{
			if ( GPIO.Pin > GPIO_Conf::Pin_EnumClass::Pin3 )
			{
				return;
			}

			uint8_t const Shift = ShiftCalculate(GPIO.Pin, 4);

			SYSCFG_Reg::EXTICR1::clearBits(15, 4*Shift);
			SYSCFG_Reg::EXTICR1::setBits(static_cast< uint8_t >(EXTICR_Port), 4*Shift);
		}

		static void SYSCFG_EXTICR2Config(GPIO_Conf::GPIO_ConfigStruct GPIO, SYSCFG_Conf::EXTICR_EnumClass EXTICR_Port)
		{
			if ( GPIO.Pin <= GPIO_Conf::Pin_EnumClass::Pin3 || (GPIO.Pin) > GPIO_Conf::Pin_EnumClass::Pin7 )
			{
				return;
			}

			uint8_t const Shift = ShiftCalculate(GPIO.Pin, 4);

			SYSCFG_Reg::EXTICR2::clearBits(15, 4*Shift);
			SYSCFG_Reg::EXTICR2::setBits(static_cast< uint8_t >(EXTICR_Port), 4*Shift);
		}

		static void SYSCFG_EXTICR3Config(GPIO_Conf::GPIO_ConfigStruct GPIO, SYSCFG_Conf::EXTICR_EnumClass EXTICR_Port)
		{
			if ( GPIO.Pin <= GPIO_Conf::Pin_EnumClass::Pin7 || GPIO.Pin > GPIO_Conf::Pin_EnumClass::Pin11 )
			{
				return;
			}

			uint8_t const Shift = ShiftCalculate(GPIO.Pin, 4);

			SYSCFG_Reg::EXTICR3::clearBits(15, 4*Shift);
			SYSCFG_Reg::EXTICR3::setBits(static_cast< uint8_t >(EXTICR_Port), 4*Shift);
		}

		static void SYSCFG_EXTICR4Config(GPIO_Conf::GPIO_ConfigStruct GPIO, SYSCFG_Conf::EXTICR_EnumClass EXTICR_Port)
		{
			if ( GPIO.Pin <= GPIO_Conf::Pin_EnumClass::Pin11 )
			{
				return;
			}
			uint8_t const Shift = ShiftCalculate(GPIO.Pin, 4);

			SYSCFG_Reg::EXTICR4::clearBits(15, 4*Shift);
			SYSCFG_Reg::EXTICR4::setBits(static_cast< uint8_t >(EXTICR_Port), 4*Shift);
		}
	};

	template<std::uintptr_t EXTI_BASE>
	class EXTI
	{
	private:
		struct EXTI_Reg
		{
			using IMR	= Reg32<EXTI_BASE + 0x00>;
			using EMR	= Reg32<EXTI_BASE + 0x04>;
			using RTSR	= Reg32<EXTI_BASE + 0x08>;
			using FRSR	= Reg32<EXTI_BASE + 0x0C>;
			using SWIER	= Reg32<EXTI_BASE + 0x10>;
			using PR	= Reg32<EXTI_BASE + 0x14>;
		};

	public:

		static void EXTI_ConfigHardInterrupt(GPIO_Conf::GPIO_ConfigStruct GPIO, EXTI_Conf::Trigger_EnumClass Mode)
		{
			EXTI_Reg::PR::clearBits(1, static_cast< uint8_t >(GPIO.Pin));
			EXTI_Reg::IMR::clearBits(1, static_cast< uint8_t >(GPIO.Pin));

			if ( Mode == EXTI_Conf::Trigger_EnumClass::Mode_Rising )
				EXTI_Reg::RTSR::setBits(1, static_cast< uint8_t >(GPIO.Pin));

			else if ( Mode == EXTI_Conf::Trigger_EnumClass::Mode_Falling )
				EXTI_Reg::FRSR::setBits(1, static_cast< uint8_t >(GPIO.Pin));

			else if ( Mode == EXTI_Conf::Trigger_EnumClass::Mode_BothTrig )
			{
				EXTI_Reg::RTSR::setBits(1, static_cast< uint8_t >(GPIO.Pin));
				EXTI_Reg::FRSR::setBits(1, static_cast< uint8_t >(GPIO.Pin));

			}

			EXTI_Reg::IMR::setBits(1, static_cast< uint8_t >(GPIO.Pin));

		}

		static void EXTI_ConfigSoftInterrupt(GPIO_Conf::GPIO_ConfigStruct GPIO)
		{
			EXTI_Reg::PR::clearBits(1, static_cast< uint8_t >(GPIO.Pin));
			EXTI_Reg::IMR::clearBits(1, static_cast< uint8_t >(GPIO.Pin));
			EXTI_Reg::IMR::setBits(1, static_cast< uint8_t >(GPIO.Pin));

		}

		static void EXTI_SetSoftInterrupt(GPIO_Conf::GPIO_ConfigStruct GPIO)
		{
			EXTI_Reg::PR::clearBits(1, static_cast< uint8_t >(GPIO.Pin));
			EXTI_Reg::SWIER::setBits(1, static_cast< uint8_t >(GPIO.Pin));

		}

		static void EXTI_ConfigEvent(GPIO_Conf::GPIO_ConfigStruct GPIO, EXTI_Conf::Trigger_EnumClass Mode)
		{
			EXTI_Reg::IMR::clearBits(1, static_cast< uint8_t >(GPIO.Pin));
			EXTI_Reg::EMR::setBits(1, static_cast< uint8_t >(GPIO.Pin));

			if ( Mode == EXTI_Conf::Trigger_EnumClass::Mode_Rising )
				EXTI_Reg::RTSR::setBits(1, static_cast< uint8_t >(GPIO.Pin));

			else if ( Mode == EXTI_Conf::Trigger_EnumClass::Mode_Falling )
				EXTI_Reg::FRSR::setBits(1, static_cast< uint8_t >(GPIO.Pin));

			else if ( Mode == EXTI_Conf::Trigger_EnumClass::Mode_BothTrig )
			{
				EXTI_Reg::RTSR::setBits(1, static_cast< uint8_t >(GPIO.Pin));
				EXTI_Reg::FRSR::setBits(1, static_cast< uint8_t >(GPIO.Pin));

			}

		}

		static void EXTI_ClearInterrupt(GPIO_Conf::GPIO_ConfigStruct GPIO)
		{
			EXTI_Reg::PR::setBits(1, static_cast< uint8_t >(GPIO.Pin));
		}
	};

}

namespace NVIC_Namespace
{
class NVIC
{
private:
	typedef volatile uint32_t TypeDefRegister;

public:
	static void NVIC_InteConfig(NVIC_Conf::Possition_EnumClass Pos, const uint8_t Prio)
	{
		constexpr std::uintptr_t NVIC_ISER0 = 0xE000E100;
		TypeDefRegister * NVIC_ISERx = reinterpret_cast<TypeDefRegister *>(NVIC_ISER0 + (static_cast< uint8_t >(Pos)/32) * 4 );

		constexpr std::uintptr_t NVIC_IP0 = 0xE000E400;
		TypeDefRegister *NVIC_IPx = reinterpret_cast<TypeDefRegister *>(NVIC_IP0 + (static_cast< uint8_t >(Pos)/4) * 4 );

		*NVIC_ISERx |= ( 1 << static_cast< uint8_t >(Pos) % 32);
		*NVIC_IPx |= ( static_cast< uint8_t >(Prio) << (8*(static_cast< uint8_t >(Pos) % 4) + 4) );
	}
};

}
#endif /* PERIPH_HPP_ */
