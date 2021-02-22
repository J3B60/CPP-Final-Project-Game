#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card {
	public:
		Card(); //Default: for NULL/EMPTY Card, (0, 'x', 'x', 0, 0, false)
		Card(int NumberInput, char SuitInput, char TypeInput, int ValueInput, int CostInput, bool AceInput); //Make cards from deck class
		char CardTypeGet(); //Card Type Getter for FZone and MZone
		int CardNumberGet(); //Card Number Getter for FZone totals, Monster Card Tributes, Attacking&Defending etc
		char CardSuitGet(); //Card Suit Getter for MZone
		bool CardAceGet();
		int CardCostGet();
		int CardValueGet();
		void AceNumberSet(int AceNumber);
	private:
		char Type; //Card Monster/Force
		int Number; //Card Number 1-13
		char Suit; //Card Suit 'S'=Spade, 'D'=Diamond, 'C'=Clubs, 'H'=Heats
		int Value; //Monster Card Value for points call on Double Drump/Empty Deck
		int Cost; //Monster Card Cost for Tributes (because of Jack Exception = 5, easier to handle)
		bool Ace; //Ace true or False, For Ace = 1 OR 11, Ace&Jack in hand
};
#endif