#ifndef DISCARD_H
#define DISCARD_H
#include <vector>
#include "Card.h"

class Discard {
	private:
		vector<Card> PlayingDiscard = {}; //Discard Pile
	public:
		bool DiscardCard(Card InputCard); //Return if
		bool RecycleCard(Card InputRCard);
		void DiscardShow();
		Card TakeCard(int InputCardPosition);
		int GetDiscardSize();
};

#endif