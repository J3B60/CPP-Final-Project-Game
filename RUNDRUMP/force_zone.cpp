#include "force_zone.h"
#include "card.h"

bool ForceZone::AddCardToFZone(Card InputCard) { //Allows for a card to be added to the zone from the players hand
	if (OncePerTurnCounter < 1 && InputCard.CardTypeGet() == 'F' && (InputCard.CardNumberGet() + ZoneTotal()) < 14) {
		FZone.push_back(InputCard);
		//ZoneTotal Will Automatically add this to total when next called
		OncePerTurnCounter++;
		return true;
	}
	else {
		return false;
	}
}

int ForceZone::GetFZoneSize() {
	return FZone.size();
}

int ForceZone::GetFZoneFirstCardNumber() {
	if (FZone.size() > 0) {
		return FZone[0].CardNumberGet();
	}
	else {
		return 0;
	}
}

char ForceZone::GetFZoneFirstCardSuit() {
	return FZone[0].CardSuitGet();
}

int ForceZone::ZoneTotal() {
	if (FZone.size() > 0) {
		int Total = 0;
		for (int SumLoop = 0; SumLoop < FZone.size(); SumLoop++) {
			Total = Total + FZone[SumLoop].CardNumberGet();
		}
		return Total;
	}
	else {
		return 0;
	}
}

Card ForceZone::RemoveCard() {
	Card temp;
	temp = FZone[FZone.size() - 1];
	FZone.pop_back();
	return temp;
}

int ForceZone::GetFZoneCardNumber(int CardPosition) {
	return FZone[CardPosition].CardNumberGet();
}

char ForceZone::GetFZoneCardSuit(int CardPosition) {
	return FZone[CardPosition].CardSuitGet();
}