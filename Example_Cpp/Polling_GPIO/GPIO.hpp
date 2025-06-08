/*
 * GPIO.hpp
 *
 *  Created on: Jun 6, 2025
 *      Author: aresi
 */

#ifndef GPIO_HPP_
#define GPIO_HPP_

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

	typedef struct
	{
		uint8_t AHB1_En;
	}RCC_EnConfigStruct;
}
namespace AHB1Peripheral
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
		    using MODER 	= Reg32 < GPIO_BASE + 0x00 >; // 0x00
		    using OTYPER 	= Reg32 < GPIO_BASE + 0x04 >; // 0x04
		    using OSPEEDR 	= Reg32 < GPIO_BASE + 0x08 >; // 0x08
		    using PUPDR 	= Reg32 < GPIO_BASE + 0x0C >; // 0x0C
		    using IDR 		= Reg32 < GPIO_BASE + 0x10 >; // 0x10
		    using ODR 		= Reg32 < GPIO_BASE + 0x14 >; // 0x14
		    using BSRR 		= Reg32 < GPIO_BASE + 0x18 >; // 0x18
		    using LCKR 		= Reg32 < GPIO_BASE + 0x1C >; // 0x1C
		    using AFRL 		= Reg32 < GPIO_BASE + 0x20 >; // 0x20
		    using AFRH 		= Reg32 < GPIO_BASE + 0x24 >; // 0x24
		};

	public:

		static void GPIO_Config(GPIO_Conf::GPIO_ConfigStruct GPIOx)
		{
			GPIO_Reg::MODER::setBits( static_cast< uint8_t >(GPIOx.Mode), 2*static_cast< uint8_t >(GPIOx.Pin) );
			GPIO_Reg::OTYPER::setBits( static_cast< bool >(GPIOx.OType), static_cast< uint8_t >(GPIOx.Pin) );
			GPIO_Reg::PUPDR::setBits( static_cast< uint8_t >(GPIOx.Pull), 2*static_cast< uint8_t >(GPIOx.Pin) );
			GPIO_Reg::OSPEEDR::setBits( static_cast< uint8_t >(GPIOx.Speed), 2*static_cast< uint8_t >(GPIOx.Pin) );

			if ( (static_cast< uint8_t >(GPIOx.Mode) != static_cast<uint8_t>(GPIO_Conf::Mode_EnumClass::Mode_AltFun)) )
				return;

			if ( (static_cast< uint8_t >(GPIOx.AF) <= static_cast< uint8_t >(GPIO_Conf::AF_EnumClass::AF7)) )
				GPIO_Reg::AFRL::setBits( static_cast< uint8_t >(GPIOx.AF), static_cast< uint8_t >(GPIOx.Pin) );
			else
				GPIO_Reg::AFRL::setBits( static_cast< uint8_t >(GPIOx.AF), (static_cast< uint8_t >(GPIOx.Pin) - static_cast< uint8_t >(GPIO_Conf::Pin_EnumClass::Pin8)) );

		}

		static void GPIO_WriteOut(const uint16_t Data)
		{
			GPIO_Reg::ODR::write( Data );
		}

		static void GPIO_ClearOut(const uint16_t Data)
		{
			GPIO_Reg::ODR::write( Data );
		}

		static void GPIO_WriteAtomic(GPIO_Conf::GPIO_ConfigStruct GPIOx)
		{
			GPIO_Reg::BSRR::setBits( 1, static_cast< uint8_t >(GPIOx.Pin) );
		}

		static void GPIO_ClearAtomic(GPIO_Conf::GPIO_ConfigStruct GPIOx)
		{
			GPIO_Reg::BSRR::setBits( 1, 2*static_cast< uint8_t >(GPIOx.Pin) );
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
			static void AHB1_ClockEnable(RCC_Conf::RCC_EnConfigStruct AHB1x)
			{
					RCC_Reg::AHB1ENR::setBits( 1, AHB1x.AHB1_En );
			}
	};
}

#endif /* GPIO_HPP_ */
