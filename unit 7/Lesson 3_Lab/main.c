/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stm32f103x6.h>
#include <Stm32_F1103C6_gpio_driver.h>


void clock_init()
{
	//Enable clock GPIOA
	RCC_GPIOA_CLK_EN();
	//Enable clock GPIOB
	RCC_GPIOB_CLK_EN();

}

void GPIO_init()
{
	GPIO_PinConfig_t PinCfg;

	//PA1:floating input
	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	//PB1 : output push pull Mode 10MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	//PA13:floating input
	PinCfg.GPIO_PinNumber = GPIO_PIN_13;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	//PB13 : output push pull Mode 10MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_13;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);
}

void my_wait(int x)
{
	unsigned int i,j;
	for ( i =0 ; i < x ; i++)
		for ( j=0 ; j<x;j++);
}

int main(void)
{
	clock_init();
	GPIO_init();


	while(1)
	{
		//PA1 press (PUR)
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0) // pressed
		{
			MCAL_GPIO_TooglePin(GPIOB, GPIO_PIN_1);
			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0); // single press
		}

		//PA13 pressed (PDR)
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13)== 1)
		{
			MCAL_GPIO_TooglePin(GPIOB, GPIO_PIN_13);
		}
		my_wait(300);
	}
}
