#ifndef __flashMock_H
#define __flashMock_H

#include <RFID_lib.h>

struct CardID cards[5];
uint8_t cardsIterator = 0;

void initFlash();

/*
 * dodaje kart� do pami�ci flash
 * return:
 * 0 - dodano kart� do pami�ci
 * -1 - pe�na pami�c
 */
int addCardToFlash(struct CardID card);

/*
 * sprawdza czy karta jest we flashu
 * return:
 * -1 - nie znaleziono karty we flashu
 * -2 - pusta pami�c
 * 0 - karta jest w pami�ci flash
 */
int checkCard(struct CardID card);

void deleteAllCardsFromFlash();

#endif /* __flashMock_H */
