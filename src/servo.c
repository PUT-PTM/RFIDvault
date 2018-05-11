#include <servo.h>
#include "stm32f4xx.h"

void servoInit() {
	RCC_AHB1PeriphClockCmd(SERVO_GPIO_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinAFConfig(SERVO_GPIO_PORT, SERVO_GPIO_PIN_SOURCE, SERVO_TIMER_GPIO);
	GPIO_InitStructure.GPIO_Pin = SERVO_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SERVO_GPIO_PORT, &GPIO_InitStructure);

	///timer
	RCC_APB1PeriphClockCmd(SERVO_TIMER_RCC, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = SERVO_TIMER_PERIOD - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIMER_PRESCALER - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(SERVO_TIMER, &TIM_TimeBaseStructure);

	TIM_Cmd(SERVO_TIMER, ENABLE); //uruchomienie

	TIM_OCInitTypeDef TIM_OCInitStructure;
	/* PWM1 Mode configuration: */
	TIM_OCInitStructure.TIM_OCMode = SERVO_TIMER_CHANEL;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(SERVO_TIMER, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(SERVO_TIMER, TIM_OCPreload_Enable);
}

void servoSetDuty(unsigned int duty) {
	TIM2->CCR1 = (uint32_t) (SERVO_TIMER_PERIOD) * (duty / 100);
}

//R - 0 PD12
//G - 1 PD13
//B - 2 PD14
void setLED(int whichLED){
	if(whichLED==0){
		TIM4->CCR1 = 8400;
			TIM4->CCR2 = 0;
			TIM4->CCR3 = 0;
	}
	else if(whichLED==1){
		TIM4->CCR1 = 0;
			TIM4->CCR2 = 8400;
			TIM4->CCR3 = 0;
	}
	else if(whichLED==2){
		TIM4->CCR1 = 0;
			TIM4->CCR2 = 0;
			TIM4->CCR3 = 8400;
	}
	else{
		TIM4->CCR1 = 0;
			TIM4->CCR2 = 0;
			TIM4->CCR3 = 0;
	}
}
