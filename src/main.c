/**
 ******************************************************************************
 * @file    main.c
 * @author  Damian Wiatrzyk, Andrzej Dybowski
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */
#include "RFID_lib.h"
#include <tm_stm32f4_mfrc522.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_flash.h"
#include <servo.h>
#include <buttons.h>

int licznikExti0 = 0;
int licznikTim2 = 0;
int licznikExti4 = 0;

int stateLock = 1; //0->open 1->close
int timer2Run = 0; // 0 -> false; 1 -> true
int elseMain = 0;

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
	TM_MFRC522_Init();

	servoInit();
	closeServo();

	ledInit();
	setLED(0);

	serviceButtonInit();
	doorButtonInit();

	while (1) {

		if (stateLock == 1) {
			//tryb otwartego sejfu

			struct CardID currentCard;
			uint8_t id[5];
			if (TM_MFRC522_Check(id) == MI_OK) {
				struct CardID newCard = { id[0], id[1], id[2], id[3], id[4] };
				currentCard = newCard;

				int check = checkCard(currentCard);
				if (check == 0) {
					openServo();
					stateLock = 0;
				} else if (check == -1) {
					elseMain++;
				}
			}
		}
	}
	return 0;
}

void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		struct CardID currentCard;
		uint8_t id[5];
		if (TM_MFRC522_Check(id) == MI_OK) {
			struct CardID newCard = { id[0], id[1], id[2], id[3], id[4] };
			currentCard = newCard;
		}

		if (addCardToFlash(currentCard) == 0)
			licznikExti0++;
		// wyzerowanie flagi wyzwolonego przerwania
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {

		licznikTim2++;
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void EXTI4_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
		while (TIM_GetFlagStatus(TIM3, TIM_FLAG_Update))
			;
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		closeServo();
		// wyzerowanie flagi wyzwolonego przerwania
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}
