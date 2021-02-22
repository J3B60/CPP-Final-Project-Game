#ifndef FORCEZONE_H
#define FORCEZONE_H
#include <vector>
#include "card.h"

using namespace std;

class ForceZone {
	private:
		vector<Card> FZone = {}; //Force Zone
		
	public:
		bool AddCardToFZone(Card InputCard); //FZone Total cannot > 13 Check + Add Card and return if successful
		int GetFZoneSize(); //Getter for the number of cards in the FZone
		int GetFZoneFirstCardNumber();
		char GetFZoneFirstCardSuit();
		int ZoneTotal(); //Zone Total (Used for Attack, tribute and Adding Cards)
		int OncePerTurnCounter = 0; //Set to Zero by EndTurn
		Card RemoveCard(); //For Discard/Tribute
		int GetFZoneCardNumber(int CardPosition);
		char GetFZoneCardSuit(int CardPosition);
		int AttackReveal = 0;//REVEAL CARDS WHEN ATTACKED, (When = 1)
};

#endif