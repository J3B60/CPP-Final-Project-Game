#ifndef DISCARD_H
#define DISCARD_H
#include "discard.h"
#include <vector>
#include "Card.h"

class Discard {
	private:
		vector<Card> PlayingDiscard = {}; //Discard Pile
	public:
		bool DiscardCard(); //Return if Discard
};

#endif