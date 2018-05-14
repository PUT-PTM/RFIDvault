#include <servo.h>
#include "stm32f4xx.h"

void servoInit() {
	RCC_AHB1PeriphClockCmd(SERVO_GPIO_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinAFConfig(SERVO_GPIO_PORT, SERVO_GPIO_PIN_SOURCE | LED_PINS_SOURCE,
	GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = SERVO_GPIO_PIN | LED_PINS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(SERVO_GPIO_PORT, &GPIO_InitStructure);

	///timer
	RCC_APB1PeriphClockCmd(SERVO_TIMER_RCC, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = TIMER_PERIOD - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = TIMER_PRESCALER - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(SERVO_TIMER, &TIM_TimeBaseStructure);

	TIM_Cmd(SERVO_TIMER, ENABLE);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	/* PWM2 Mode configuration: */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 600;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	SERVO_TIMER_PWM_INIT(SERVO_TIMER, &TIM_OCInitStructure);
	SERVO_TIMER_PWM_PRELOAD_CONFIG(SERVO_TIMER, TIM_OCPreload_Enable);
}

void ledInit() {
	RCC_AHB1PeriphClockCmd(LED_GPIO_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LED_PINS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);

	GPIO_ResetBits(LED_PORT, LED_PINS);
}

void servoSetDuty(unsigned int duty) {
	TIM_SetCompare4(SERVO_TIMER, duty);
}

int openServo() {
	return 0;
}

int closeServo() {
	return 0;
}

void setLED(int whichLED) {
	GPIO_ResetBits(LED_PORT, LED_PINS);
	if (whichLED == 0) {
		GPIO_SetBits(LED_PORT, LED_1);
	} else if (whichLED == 1) {
		GPIO_SetBits(LED_PORT, LED_2);
	} else if (whichLED == 2) {
		GPIO_SetBits(LED_PORT, LED_3);
	}
}
