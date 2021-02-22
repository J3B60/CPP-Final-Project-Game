#ifndef FORCEZONE_H
#define FORCEZONE_H
#include <vector>
#include "card.h"

using namespace std;

class ForceZone {
	private:
		vector<Card> FZone = {}; //Force Zone
		int ZoneTotal; //Zone Total (Used for Attack, tribute and Adding Cards)
	public:
		bool AddCardToFZone(Card InputCard); //FZone Total cannot > 13 Check + Add Card and return if successful

};

#endif