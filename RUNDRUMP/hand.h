#ifndef HAND_H
#define HAND_H

#include <vector>
#include <string>
#include "card.h"
#include "deck.h"

class Hand {
	public:
		int NoCardsHand(); //Number of Cards in the Hand **VISIBLE TO OTHER PLAYER(FOR SHOW FIELD CLASS/FUNCTION DISPLAY)
		Card SelectCard(int CardPosition); //Card Getter, First check if move Valid (wait for bool return true then use function below vv) Uses CurrentCardPosition Variable
		void PlayCardFromHand(bool ResultFromFunction); //Plays the card from hand, returning a card to another function, Replacing the card at that position to Null(Or shifting all other cards using vector function) Uses CurrentCardPosition Variable
		bool AceJack(int AceHandPosistion, int JackHandPosition); //Selecting the two cards from the hand position (in the vector)
		bool DrawCardToHand(Card DrawnCard);
		vector<Card> PlayerHand = {};	//Holds the Players Hand
	private:
		//vector<Card> PlayerHand = {};	//Holds the Players Hand
		Card EMPTY; //NULL CARD
		int CurrentCardPosition = -1; //The Current Chosen Position, Requires 2 functions to be run hence use of variable, Set to 0 at the end of Last Function
};

#endif
