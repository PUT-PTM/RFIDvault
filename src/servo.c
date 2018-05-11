#include <servo.h>
#include "stm32f4xx.h"

void servoInit() {
	RCC_AHB1PeriphClockCmd(SERVO_GPIO_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinAFConfig(SERVO_GPIO_PORT, SERVO_GPIO_PIN_SOURCE, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = SERVO_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(SERVO_GPIO_PORT, &GPIO_InitStructure);
	///timer
	RCC_APB1PeriphClockCmd(SERVO_TIMER_RCC, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = SERVO_TIMER_PERIOD - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIMER_PRESCALER - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(SERVO_TIMER, &TIM_TimeBaseStructure);

	TIM_Cmd(SERVO_TIMER, ENABLE);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	/* PWM1 Mode configuration: */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	SERVO_TIMER_PWM_INIT(SERVO_TIMER, &TIM_OCInitStructure);
	SERVO_TIMER_PWM_PRELOAD_CONFIG(SERVO_TIMER, TIM_OCPreload_Enable);
}

void servoSetDuty(unsigned int duty) {
	SERVO_TIMER->SERVO_TIMER_CHANEL = (uint32_t) (5000)
			* (duty / 100);
}
