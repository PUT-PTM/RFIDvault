#ifndef __flashMock_H
#define __flashMock_H

#include <RFID_lib.h>

struct CardID cards[5];
uint8_t cardsIterator = 0;

void initFlash();
int addCardToFlash(struct CardID card);
int checkCard(struct CardID card);
void deleteAllCardsFromFlash();

#endif /* __flashMock_H */
