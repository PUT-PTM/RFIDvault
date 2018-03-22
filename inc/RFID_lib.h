#ifndef __RFID_lib_H
#define __RFID_lib_H

#include <tm_stm32f4_mfrc522.h>

struct CardID{
	uint8_t a, b, c, d, e;
};

extern CardID readCard();

#endif /* __RFID_lib_H */
