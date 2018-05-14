#include <RFID_lib.h>
#include <flashMock.h>

struct CardID readCard() {
	uint8_t id[5];
	struct CardID card;

	if (TM_MFRC522_Check(id) == MI_OK) {
		struct CardID newCard  = {id[0], id[1], id[2], id[3], id[4]};
		card = newCard;
	}

	return card;
}
