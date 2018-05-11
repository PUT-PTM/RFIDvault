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

void servoInit();
void servoSetDuty(unsigned int duty);

#endif /* __servo_H */
