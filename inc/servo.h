#ifndef __servo_H
#define __servo_H

#define SERVO_TIMER_RCC RCC_APB1Periph_TIM2
#define SERVO_TIMER_PERIOD 8400
#define SERVO_TIMER_PRESCALER 10
#define SERVO_TIMER TIM2
#define SERVO_TIMER_GPIO GPIO_AF_TIM2
#define SERVO_TIMER_CHANEL TIM_OCMode_PWM1

#define SERVO_GPIO_RCC RCC_AHB1Periph_GPIOA
#define SERVO_GPIO_PORT GPIOA
#define SERVO_GPIO_PIN_SOURCE GPIO_PinSource15
#define SERVO_GPIO_PIN GPIO_Pin_15

void servoInit();
void servoSetDuty(unsigned int duty);

#endif /* __servo_H */
