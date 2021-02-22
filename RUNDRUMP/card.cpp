#include "card.h"

Card::Card() {
	Number = 0;
	Suit = 'x';
	Type = 'x';
	Value = 0;
	Cost = 0;
	Ace = false;
}

char Card::CardTypeGet() { //For convenience (Covers 10,11,12,13)
	return Type;
}

int Card::CardNumberGet() {
	return Number;
}

char Card::CardSuitGet() {
	return Suit;
}

bool Card::CardAceGet() {
	return Ace;
}

int Card::CardCostGet() {
	return Cost;
}

int Card::CardValueGet() {
	return Value;
}

Card::Card(int NumberInput, char SuitInput, char TypeInput, int ValueInput, int CostInput, bool AceInput) {
	Number = NumberInput;
	Suit = SuitInput;
	Type = TypeInput;
	Value = ValueInput;
	Cost = CostInput;
	Ace = AceInput;
}

void Card::AceNumberSet(int AceNumber) {
	if (Ace == true) {
		if (AceNumber == 1 || AceNumber == 11) {
			Number = AceNumber;
		}
	}
}