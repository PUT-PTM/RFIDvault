#ifndef __flashMock_H
#define __flashMock_H

#include <RFID_lib.h>

struct CardID cards[5];
uint8_t cardsIterator = 0;

void initFlash();

/*
 * dodaje kartê do pamiêci flash
 * return:
 * 0 - dodano kartê do pamiêci
 * -1 - pe³na pamiêc
 */
int addCardToFlash(struct CardID card);

/*
 * sprawdza czy karta jest we flashu
 * return:
 * -1 - nie znaleziono karty we flashu
 * -2 - pusta pamiêc
 * 0 - karta jest w pamiêci flash
 */
int checkCard(struct CardID card);

void deleteAllCardsFromFlash();

#endif /* __flashMock_H */
