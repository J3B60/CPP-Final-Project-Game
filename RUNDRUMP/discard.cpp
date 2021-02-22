#include "discard.h"

bool Discard::DiscardCard(Card InputCard) {//False??
	PlayingDiscard.push_back(InputCard);
	return true;
}

bool Discard::RecycleCard(Card InputRCard) {
	if (InputRCard.CardTypeGet() == 'M') {
		PlayingDiscard.push_back(InputRCard);
		return true;
	}
	else {
		return false;
	}
}

void Discard::DiscardShow() {
	for (int ShowLoop = 0; ShowLoop < PlayingDiscard.size(); ShowLoop++) {
		cout << ShowLoop + 1 << ". [" << PlayingDiscard[ShowLoop].CardNumberGet() << PlayingDiscard[ShowLoop].CardSuitGet() << "]" << endl;
	}
}

Card Discard::TakeCard(int InputCardPosition) {
	Card temp;
	temp = PlayingDiscard[InputCardPosition];
	PlayingDiscard.erase(PlayingDiscard.begin() + InputCardPosition);
	return temp;
}

int Discard::GetDiscardSize() {
	return PlayingDiscard.size();
}