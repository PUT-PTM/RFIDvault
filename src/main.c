/**
 ******************************************************************************
 * @file    main.c
 * @author  Damian Wiatrzyk, Andrzej Dybowski
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include <tm_stm32f4_mfrc522.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_flash.h"
#include <servo.h>
#include <buttons.h>

int licznik = 0;
int main(void) {
	/*
	 codeInitFlash = Internal_FLASH_Init();
	 uint16_t* data_ptr = data;

	 if (codeInitFlash == 1) {
	 uint16_t writeData = 1;

	 codeWriteFlash = Internal_FLASH_Write(1, writeData);
	 for (int i = 0; i < 10; i++) {
	 data[i] = Internal_FLASH_Read(i);
	 data_ptr++;
	 }
	 }
	 */

	servoInit();
	openServo();

	ledInit();
	setLED(0);

	serviceButtonInit();

	while (1) {
	}

	return 0;
}


void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		licznik++;
		// wyzerowanie flagi wyzwolonego przerwania
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
