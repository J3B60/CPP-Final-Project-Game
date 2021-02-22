#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

class Deck {
	private:
		vector<Card> PlayingDeck = { Card(1, 'S', 'F',  0, 0, true), Card(2, 'S', 'F', 0, 0, false), Card(3, 'S', 'F', 0, 0, false), Card(4, 'S', 'F', 0, 0, false), Card(5, 'S', 'F', 0, 0, false), Card(6, 'S', 'F', 0, 0, false), Card(7, 'S', 'F', 0, 0, false), Card(8, 'S', 'F', 0, 0, false), Card(9, 'S', 'F', 0, 0, false), Card(10, 'S', 'M', 10, 10, false), Card(11, 'S', 'M', 5, 11, false), Card(12, 'S', 'M', 12, 12, false), Card(13, 'S', 'M', 13, 13, false), Card(1, 'D', 'F', 0, 0, true), Card(2, 'D', 'F', 0, 0, false), Card(3, 'D', 'F', 0, 0, false), Card(4, 'D', 'F', 0, 0, false), Card(5, 'D', 'F', 0, 0, false), Card(6, 'D', 'F', 0, 0, false), Card(7, 'D', 'F', 0, 0, false), Card(8, 'D', 'F', 0, 0, false), Card(9, 'D', 'F', 0, 0, false), Card(10, 'D', 'M', 10, 10, false), Card(11, 'D', 'M', 5, 11, false), Card(12, 'D', 'M', 12, 12, false), Card(13, 'D', 'M', 13, 13, false), Card(1, 'C', 'F', 0, 0, true), Card(2, 'C', 'F', 0, 0, false), Card(3, 'C', 'F', 0, 0, false), Card(4, 'C', 'F', 0, 0, false), Card(5, 'C', 'F', 0, 0, false), Card(6, 'C', 'F', 0, 0, false), Card(7, 'C', 'F', 0, 0, false), Card(8, 'C', 'F', 0, 0, false), Card(9, 'C', 'F', 0, 0, false), Card(10, 'C', 'M', 10, 10, false), Card(11, 'C', 'M', 5, 11, false), Card(12, 'C', 'M', 12, 12, false), Card(13, 'C', 'M', 13, 13, false), Card(1, 'H', 'F', 0, 0, true), Card(2, 'H', 'F', 0, 0, false), Card(3, 'H', 'F', 0, 0, false), Card(4, 'H', 'F', 0, 0, false), Card(5, 'H', 'F', 0, 0, false), Card(6, 'H', 'F', 0, 0, false), Card(7, 'H', 'F', 0, 0, false), Card(8, 'H', 'F', 0, 0, false), Card(9, 'H', 'F', 0, 0, false), Card(10, 'H', 'M', 10, 10, false), Card(11, 'H', 'M', 5, 11, false), Card(12, 'H', 'M', 12, 12, false), Card(13, 'H', 'M', 13, 13, false) };
		Card EMPTY;
		//Standard 52 Card Playing Deck
	public:
		int PlayingDeckSize(); //Get the number of cards in deck, (if = 0 End Game, Check before Draw)
		void StartGame(); //Start Game, Each Player Draws 5 Cards and No draw on first term
		Card DrawCard(); //Card Draw, Select player and return them a card, Card is added to vector, Card in deck is removed
};

#endif