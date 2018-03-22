/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include <tm_stm32f4_mfrc522.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


uint8_t CardID[5];

uint8_t CardID_a, CardID_b, CardID_c, CardID_d, CardID_e;

int a = 0;

int main(void) {
	TM_MFRC522_Init();
	for (;;) {
		if (TM_MFRC522_Check(CardID) == MI_OK) {
			CardID_a = CardID[0];
			CardID_b = CardID[1];
			CardID_c = CardID[2];
			CardID_d = CardID[3];
			CardID_e = CardID[4];
		} else {
			a = -1;
		}
	}
}
