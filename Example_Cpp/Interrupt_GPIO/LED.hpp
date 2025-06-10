/*
 * LED.hpp
 *
 *  Created on: Jun 8, 2025
 *      Author: aresi
 */

#ifndef LED_HPP_
#define LED_HPP_

#include <Periph.hpp>

namespace DRIVER_GPIO
{
	RCC_Conf::RCC_EnConfigStruct RCC_PeriphClk =
	{
			.GPIOB_En = RCC_Conf::AHB1_EnumClass::GPIOB_Clk,
			.GPIOC_En = RCC_Conf::AHB1_EnumClass::GPIOC_Clk,
			.SYSCFG_En = RCC_Conf::APB2_EnumClass::SYSCFG_Clk

	};

	GPIO_Conf::GPIO_ConfigStruct GPIOB14_Conf =
	{
			.Pin	= GPIO_Conf::Pin_EnumClass::Pin14,
			.AF		= GPIO_Conf::AF_EnumClass::NotUse,
			.Mode	= GPIO_Conf::Mode_EnumClass::Mode_Output,
			.OType	= GPIO_Conf::OType_EnumClass::Mode_PushPull,
			.Pull	= GPIO_Conf::UpDown_EnumClass::Mode_PullUp,
			.Speed	= GPIO_Conf::Speed_EnumClass::Mode_MedSpeed,
			.ptrGpioISR = nullptr
	};

	GPIO_Conf::GPIO_ConfigStruct GPIOB7_Conf =
	{
			.Pin	= GPIO_Conf::Pin_EnumClass::Pin7,
			.AF		= GPIO_Conf::AF_EnumClass::NotUse,
			.Mode	= GPIO_Conf::Mode_EnumClass::Mode_Output,
			.OType	= GPIO_Conf::OType_EnumClass::Mode_PushPull,
			.Pull	= GPIO_Conf::UpDown_EnumClass::Mode_PullUp,
			.Speed	= GPIO_Conf::Speed_EnumClass::Mode_MedSpeed,
			.ptrGpioISR = nullptr
	};

	GPIO_Conf::GPIO_ConfigStruct GPIOB0_Conf =
	{
			.Pin	= GPIO_Conf::Pin_EnumClass::Pin0,
			.AF		= GPIO_Conf::AF_EnumClass::NotUse,
			.Mode	= GPIO_Conf::Mode_EnumClass::Mode_Output,
			.OType	= GPIO_Conf::OType_EnumClass::Mode_PushPull,
			.Pull	= GPIO_Conf::UpDown_EnumClass::Mode_PullUp,
			.Speed	= GPIO_Conf::Speed_EnumClass::Mode_MedSpeed,
			.ptrGpioISR = nullptr
	};
	class LED
	{
	private:

		static constexpr std::uintptr_t RCC_BASE = 0x40023800;
		using RCC	= Peripheral::RCC<RCC_BASE>;

		static constexpr std::uintptr_t GPIOB_BASE = 0x40020400;
		using GPIOB = Peripheral::GPIO<GPIOB_BASE>;

		static constexpr std::uintptr_t SYSCFG_BASE = 0x40013800;
		using SYSCFG = Peripheral::SYSCFG<SYSCFG_BASE>;

		static constexpr std::uintptr_t EXTI_BASE =  0x40013C00;
		using EXTI = Peripheral::EXTI<EXTI_BASE>;

		static void LED_Delay1()
		{
			volatile uint32_t i = 100000;
			while (i--);

		}

		static void LED_Delay2()
		{
			volatile uint32_t i = 1000000;
			while (i--);

		}

	public:

		static void LED_ClockPeriph()
		{
			RCC::AHB1_ClockEnable( RCC_PeriphClk.GPIOB_En );
			RCC::APB2_ClockEnable( RCC_PeriphClk.SYSCFG_En );
			LED_Delay2();

		}

		static void LED_Config()
		{
			GPIOB::GPIO_Config(GPIOB0_Conf);
			GPIOB::GPIO_Config(GPIOB7_Conf);
			GPIOB::GPIO_Config(GPIOB14_Conf);

		}

		static void LED_InterruptConfig()
		{
			SYSCFG::SYSCFG_EXTICR2Config(GPIOB7_Conf, SYSCFG_Conf::EXTICR_EnumClass::EXTI_PB);
			EXTI::EXTI_ConfigSoftInterrupt(GPIOB7_Conf);
			NVIC_Namespace::NVIC::NVIC_InteConfig(NVIC_Conf::Possition_EnumClass::EXTI9_5_Pos, 4);
		}

		static void LED_LeftGetUp()
		{
			GPIOB::GPIO_WriteAtomic(GPIOB14_Conf);
			LED_Delay1();
			GPIOB::GPIO_WriteAtomic(GPIOB7_Conf);
			LED_Delay1();
			GPIOB::GPIO_WriteAtomic(GPIOB0_Conf);
			LED_Delay1();

		}

		static void LED_LeftGetDown()
		{
			GPIOB::GPIO_ClearAtomic(GPIOB14_Conf);
			LED_Delay1();
			GPIOB::GPIO_ClearAtomic(GPIOB7_Conf);
			LED_Delay1();
			GPIOB::GPIO_ClearAtomic(GPIOB0_Conf);
			LED_Delay1();

		}

		static void LED_RightGetUp()
		{
			GPIOB::GPIO_WriteAtomic(GPIOB14_Conf);
			LED_Delay2();
			GPIOB::GPIO_WriteAtomic(GPIOB7_Conf);
			LED_Delay2();
			EXTI::EXTI_SetSoftInterrupt(GPIOB7_Conf);
			GPIOB::GPIO_WriteAtomic(GPIOB0_Conf);
			LED_Delay2();

		}

		static void LED_RightGetDown()
		{
			GPIOB::GPIO_ClearAtomic(GPIOB14_Conf);
			LED_Delay2();
			GPIOB::GPIO_ClearAtomic(GPIOB7_Conf);
			LED_Delay2();
			EXTI::EXTI_SetSoftInterrupt(GPIOB7_Conf);
			GPIOB::GPIO_ClearAtomic(GPIOB0_Conf);
			LED_Delay2();

		}

		static void LED_ISR()
		{
			uint32_t PushBottomMemISR = GPIOB::GPIO_Read();
			GPIOB::GPIO_WriteOut(0x00);
			LED_Delay2();
			EXTI::EXTI_ClearInterrupt(GPIOB7_Conf);
			LED_LeftGetUp();
			LED_LeftGetDown();
			GPIOB::GPIO_WriteOut(PushBottomMemISR);
		}

	};

	GPIO_Conf::GPIO_ConfigStruct GPIOC13_Conf =
	{
			.Pin	= GPIO_Conf::Pin_EnumClass::Pin13,
			.AF		= GPIO_Conf::AF_EnumClass::NotUse,
			.Mode	= GPIO_Conf::Mode_EnumClass::Mode_Input,
			.OType	= GPIO_Conf::OType_EnumClass::Mode_PushPull,
			.Pull	= GPIO_Conf::UpDown_EnumClass::Mode_PullDown,
			.Speed	= GPIO_Conf::Speed_EnumClass::Mode_MedSpeed,
			.ptrGpioISR = nullptr
	};

	class PUSH_BOTTOM
	{
	private:

		bool WatchISR = 0;

		static constexpr std::uintptr_t RCC_BASE = 0x40023800;
		using RCC	= Peripheral::RCC<RCC_BASE>;

		static constexpr std::uintptr_t GPIOC_BASE = 0x40020800;
		using GPIOC = Peripheral::GPIO<GPIOC_BASE>;

		static constexpr std::uintptr_t SYSCFG_BASE = 0x40013800;
		using SYSCFG = Peripheral::SYSCFG<SYSCFG_BASE>;

		static constexpr std::uintptr_t EXTI_BASE =  0x40013C00;
		using EXTI = Peripheral::EXTI<EXTI_BASE>;

	public:
		static void PUSH_Config()
		{
			GPIOC::GPIO_Config( GPIOC13_Conf );
		}

		static void PUSH_ClockPeriph()
		{
			RCC::AHB1_ClockEnable( RCC_PeriphClk.GPIOC_En );
			volatile uint16_t i = 3;
			while(i) i--;

		}

		static void PUSH_InterruptConfig()
		{
			SYSCFG::SYSCFG_EXTICR4Config(GPIOC13_Conf, SYSCFG_Conf::EXTICR_EnumClass::EXTI_PC);
			EXTI::EXTI_ConfigHardInterrupt(GPIOC13_Conf, EXTI_Conf::Trigger_EnumClass::Mode_Falling);
			NVIC_Namespace::NVIC::NVIC_InteConfig(NVIC_Conf::Possition_EnumClass::EXTI15_9_Pos, 5);
		}

		static void PUSH_ISR()
		{
			EXTI::EXTI_ClearInterrupt(GPIOC13_Conf);
			LED::LED_RightGetUp();
			LED::LED_RightGetDown();
			LED::LED_RightGetUp();
			LED::LED_RightGetDown();

		}

	};
}

#endif /* LED_HPP_ */
