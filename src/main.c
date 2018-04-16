/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include <tm_stm32f4_mfrc522.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RGB();
void SetSERWO();

uint8_t CardID[5];

uint8_t CardID_a, CardID_b, CardID_c, CardID_d, CardID_e;

int a = 0;

int main(void) {
	/////////////////////////////////////////////////////////////////////
/* Inicjalizacja timerów dla diody */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM4);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM4);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM4);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(GPIOA, &GPIO_InitStructure);

			///timer
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);

			TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
			TIM_TimeBaseStructure.TIM_Period = 16799;
			TIM_TimeBaseStructure.TIM_Prescaler = 9;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
			TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

			TIM_Cmd(TIM1, ENABLE); //uruchomienie

			TIM_OCInitTypeDef TIM_OCInitStructure;
			/* PWM1 Mode configuration: */
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_Pulse = 0;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

			TIM_OC1Init(TIM1, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

			TIM_OC2Init(TIM1, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

			TIM_OC3Init(TIM1, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);


			TIM1->CCR1 = 8400;
			TIM1->CCR2 = 8400;
			TIM1->CCR3 = 8400;
			///////////////////////////////////////////
			/* PWM dla Serwa */
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

				GPIO_InitTypeDef GPIO_InitStructure;
						GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
						GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
						GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
						GPIO_Init(GPIOA, &GPIO_InitStructure);

						///timer
						RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

						TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
						TIM_TimeBaseStructure.TIM_Period = 8399;
						TIM_TimeBaseStructure.TIM_Prescaler = 9;
						TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
						TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
						TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

						TIM_Cmd(TIM2, ENABLE); //uruchomienie

						TIM_OCInitTypeDef TIM_OCInitStructure;
						/* PWM1 Mode configuration: */
						TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
						TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
						TIM_OCInitStructure.TIM_Pulse = 0;
						TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

						TIM_OC1Init(TIM2, &TIM_OCInitStructure);
						TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

			TIM2->CCR1 = 8400;

	TM_MFRC522_Init();
	for (;;) {/*
		if (TM_MFRC522_Check(CardID) == MI_OK) {
			CardID_a = CardID[0];
			CardID_b = CardID[1];
			CardID_c = CardID[2];
			CardID_d = CardID[3];
			CardID_e = CardID[4];
		} else {
			a = -1;

		}*/
	}

}


void RGB(){

}
