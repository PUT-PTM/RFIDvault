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
#include "stm32f4_flash.h"

void RGB();
//void SetSERWO();

uint8_t CardID[5];

uint8_t CardID_a, CardID_b, CardID_c, CardID_d, CardID_e;

int a = 0;

uint16_t data;
int main(void) {
	Internal_FLASH_Init();

	uint16_t writeData = 1;

	Internal_FLASH_Write(0x5555, writeData);
	data = Internal_FLASH_Read(0x5555);
	while(1);

	return 0;
}
/*
void RGB() {

}
*/
