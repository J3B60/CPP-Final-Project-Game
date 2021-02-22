#include "deck.h"
#include "card.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "player.h"

using namespace std;

void Deck::StartGame() {
	srand(unsigned(time(0)));
	random_shuffle( PlayingDeck.begin(), PlayingDeck.end() );
	//Add cards to players hands
}

Card Deck::DrawCard() {
	if (PlayingDeckSize() != 0) { //If the Deck is not empty
		Card temp;	//Temporary holder for a Card
		temp = PlayingDeck[PlayingDeck.size() - 1]; //Copy top of deck
		PlayingDeck.pop_back();	//Remove top card from deck
		return temp; //Return Card to Hand Function
	}
	else {
		return EMPTY; //Give Hand a Blank Card
	}
		
}

int Deck::PlayingDeckSize() {
	return PlayingDeck.size(); //Return Deck size (For End Game Condition, Can't Draw)
}