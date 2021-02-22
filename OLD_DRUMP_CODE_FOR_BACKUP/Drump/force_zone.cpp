#include "force_zone.h"
#include "card.h"

bool ForceZone::AddCardToFZone(Card InputCard) { //Allows for a card to be added to the zone from the players hand
	if (InputCard.CardTypeGet() == 'F' && (InputCard.CardNumberGet() + ZoneTotal) < 14) {
		FZone.push_back(InputCard);
		ZoneTotal += InputCard.CardNumberGet();
		return true;
	}
	else {
		return false;
	}
}