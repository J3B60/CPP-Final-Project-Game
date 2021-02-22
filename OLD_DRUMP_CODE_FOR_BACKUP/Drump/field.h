#ifndef FIELD_H
#define FIELD_H
#include "monster_zone.h"
#include "force_zone.h"
#include "deck.h"
#include "discard.h"
#include "hand.h"
#include "player.h"
#include <vector>

class Field { //Will be passed to a Show Function (To allow for the Show/Display Function to be changend in the future to a GUI)
	private:
		
	public:
		Field();
		Player P1; //Player 1 ##Comes with Hand, MZones, FZones and all their functions
		Player P2; //Player 2 ##
		Deck DrumpDeck; //Deck on the Field
		Discard DrumpDiscard; //Discard Pile on the Field
};

#endif