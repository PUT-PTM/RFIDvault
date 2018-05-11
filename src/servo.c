#include <servo.h>
#include "stm32f4xx.h"

void servoInit() {
	RCC_AHB1PeriphClockCmd(SERVO_GPIO_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinAFConfig(SERVO_GPIO_PORT, SERVO_GPIO_PIN_SOURCE | LED_PINS_SOURCE, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = SERVO_GPIO_PIN | LED_PINS;
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
	/* PWM2 Mode configuration: */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	SERVO_TIMER_PWM_INIT(SERVO_TIMER, &TIM_OCInitStructure);
	SERVO_TIMER_PWM_PRELOAD_CONFIG(SERVO_TIMER, TIM_OCPreload_Enable);

	LED_1_TIMER_PWM_INIT(LED_TIMER, &TIM_OCInitStructure);
	LED_1_TIMER_PWM_PRELOAD_CONFIG(LED_TIMER, TIM_OCPreload_Enable);

	LED_2_TIMER_PWM_INIT(LED_TIMER, &TIM_OCInitStructure);
	LED_2_TIMER_PWM_PRELOAD_CONFIG(LED_TIMER, TIM_OCPreload_Enable);

	LED_3_TIMER_PWM_INIT(LED_TIMER, &TIM_OCInitStructure);
	LED_3_TIMER_PWM_PRELOAD_CONFIG(LED_TIMER, TIM_OCPreload_Enable);
}

void servoSetDuty(unsigned int duty) {
	SERVO_TIMER->SERVO_TIMER_CHANEL = (uint32_t) (SERVO_TIMER_PERIOD)
			* (duty / 100);
}

//R - 0 PD12
//G - 1 PD13
//B - 2 PD14
void setLED(int whichLED) {
	if (whichLED == 0) {
		LED_TIMER->CCR1 = 5000;
		LED_TIMER->CCR2 = 0;
		LED_TIMER->CCR3 = 0;
	} else if (whichLED == 1) {
		LED_TIMER->CCR1 = 0;
		LED_TIMER->CCR2 = 5000;
		LED_TIMER->CCR3 = 0;
	} else if (whichLED == 2) {
		LED_TIMER->CCR1 = 0;
		LED_TIMER->CCR2 = 0;
		LED_TIMER->CCR3 = 5000;
	} else {
		LED_TIMER->CCR1 = 0;
		LED_TIMER->CCR2 = 0;
		LED_TIMER->CCR3 = 0;
	}
}
