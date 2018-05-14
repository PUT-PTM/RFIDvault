#ifndef __servo_H
#define __servo_H

#define SERVO_TIMER_RCC RCC_APB1Periph_TIM4
#define TIMER_PERIOD 20000
#define TIMER_PRESCALER 84
#define SERVO_TIMER TIM4
#define SERVO_TIMER_GPIO GPIO_AF_TIM4
#define SERVO_TIMER_CHANEL CCR4
#define SERVO_TIMER_PWM_INIT TIM_OC4Init
#define SERVO_TIMER_PWM_PRELOAD_CONFIG TIM_OC4PreloadConfig

#define SERVO_GPIO_RCC RCC_AHB1Periph_GPIOD
#define SERVO_GPIO_PORT GPIOD
#define SERVO_GPIO_PIN_SOURCE GPIO_PinSource15
#define SERVO_GPIO_PIN GPIO_Pin_15
#define SERVO_0_ANGLE 600
#define SERVO_120_ANGLE 1800

#define LED_GPIO_RCC RCC_AHB1Periph_GPIOD
#define LED_1 GPIO_Pin_12
#define LED_2 GPIO_Pin_13
#define LED_3 GPIO_Pin_14
#define LED_PINS LED_1 | LED_2 | LED_3
#define LED_PORT GPIOD
#define LED_PINS_SOURCE GPIO_PinSource12 | GPIO_PinSource13 | GPIO_PinSource14

void servoInit();
void servoSetDuty(unsigned int duty);

void openServo();
void closeServo();

//R - 0 PD12
//G - 1 PD13
//B - 2 PD14
void ledInit();
void setLED(int whichLED);

#endif /* __servo_H */
