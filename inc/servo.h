#ifndef __servo_H
#define __servo_H

#define SERVO_TIMER_RCC RCC_APB1Periph_TIM4
#define SERVO_TIMER_PERIOD 5000
#define SERVO_TIMER_PRESCALER 84
#define SERVO_TIMER TIM4
#define SERVO_TIMER_GPIO GPIO_AF_TIM4
#define SERVO_TIMER_CHANEL CCR4
#define SERVO_TIMER_PWM_INIT TIM_OC4Init
#define SERVO_TIMER_PWM_PRELOAD_CONFIG TIM_OC4PreloadConfig

#define SERVO_GPIO_RCC RCC_AHB1Periph_GPIOD
#define SERVO_GPIO_PORT GPIOD
#define SERVO_GPIO_PIN_SOURCE GPIO_PinSource15
#define SERVO_GPIO_PIN GPIO_Pin_15

#define LED_PINS GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
#define LED_PORT GPIOD
#define LED_TIMER TIM4
#define LED_PINS_SOURCE GPIO_PinSource12 | GPIO_PinSource13 | GPIO_PinSource14
#define LED_1_TIMER_PWM_INIT TIM_OC1Init
#define LED_1_TIMER_PWM_PRELOAD_CONFIG TIM_OC1PreloadConfig
#define LED_2_TIMER_PWM_INIT TIM_OC2Init
#define LED_2_TIMER_PWM_PRELOAD_CONFIG TIM_OC2PreloadConfig
#define LED_3_TIMER_PWM_INIT TIM_OC3Init
#define LED_3_TIMER_PWM_PRELOAD_CONFIG TIM_OC3PreloadConfig

void servoInit();
void servoSetDuty(unsigned int duty);

//R - 0 PD12
//G - 1 PD13
//B - 2 PD14
void setLED(int whichLED);

#endif /* __servo_H */
