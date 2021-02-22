#include "hand.h"
#include "card.h"
#include <vector>
#include "player.h"

int Hand::NoCardsHand(){
	return PlayerHand.size(); //Number of Cards in the Player's Hand (For Show, Both Players can see)
}

Card Hand::SelectCard(int CardPosition) {
	if (CardPosition > 0 && CardPosition <= PlayerHand.size()) { //If Card Exists then return the chosen card
		CurrentCardPosition = CardPosition;
		return PlayerHand[CardPosition];
	}
	else {
		CurrentCardPosition = 0;
		return EMPTY; //Return EMPTY if false
	}
}

void Hand::PlayCardFromHand(bool ResultFromFunction) {
	if (ResultFromFunction == true) { //If Card was accepted then
		PlayerHand.erase(PlayerHand.begin() + CurrentCardPosition); //Remove Card From Hand
	}
}

///////////////////////////////////////////////////////////////////////////////
bool Hand::AceJack(int FirstHandPosition, int SecondHandPosition) {
	if (PlayerHand[FirstHandPosition].CardAceGet() == true && PlayerHand[SecondHandPosition].CardNumberGet() == 11) {
		//AddMonsterCardToZone(PlayerHand[SecondHandPosition]); //Check Monster_zone
		return false; //PLACEHOLDER
	}
}

bool Hand::MonsterTribute(int HandPosition, int ForceZoneInput) {
	return false; //PLACEHOLDER
}

bool Hand::DrawCardToHand(Card DrawnCard) {
	if (DrawnCard.CardSuitGet() == 'x') {
		return false;
	}
	else {
		PlayerHand.push_back(DrawnCard);
		return true;
	}
}