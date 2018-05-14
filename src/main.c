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
	TM_MFRC522_Init();

	servoInit();
	closeServo();

	ledInit();
	setLED(0);

	serviceButtonInit();
	//0->open 1->close
	int stateLock = 1;

	while (1) {
		//servoSetDuty(40);

		if (stateLock == 1) {
			//tryb otwartego sejfu

			struct CardID currentCard = readCard();

			if (checkCard(currentCard) == 0) {
				openServo();
				stateLock = 1;
			}
		} else if (stateLock == 0) {
			//tryb serwisowy

			/*tutaj wklep sobie przerwania(StasiaXD), którymi bedziesz coœ tam serwisowa³ i jakiœ licznik, ¿e niby jak
			 od 5 sekund jest zakmniêtye to sobie odpalaszto na dole
			 if(przytrzymaniePrzyciskuCzyCoœCoTamOgarnie¯eZamknalesSejfXD==1){
			 closeServo();
			 stateLock=1;
			 }*/
		}
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
