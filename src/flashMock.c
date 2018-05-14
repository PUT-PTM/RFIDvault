#include <flashMock.h>

void initFlash() {
	deleteAllCardsFromFlash();
}

int addCardToFlash(struct CardID card) {
	if (cardsIterator >= 5)
		return -1;
	cards[cardsIterator++] = card;
	return 0;
}

void deleteAllCardsFromFlash() {
	for (int i = 0; i < 5; i++) {
		cards[i].a = 0;
		cards[i].b = 0;
		cards[i].c = 0;
		cards[i].d = 0;
		cards[i].e = 0;
	}
	cardsIterator = 0;
}

int checkCard(struct CardID card) {
	if (cardsIterator <= 0)
		return -2;

	for (int i = 0; i < cardsIterator; i++) {
		if ((cards[i].a == card.a) && (cards[i].b == card.b)
				&& (cards[i].c == card.c) && (cards[i].d == card.d)
				&& (cards[i].e == card.e))
			return 0;
	}

	return -1;
}
