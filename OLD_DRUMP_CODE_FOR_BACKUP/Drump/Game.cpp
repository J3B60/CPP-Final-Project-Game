#include <iostream>
#include <string>
#include "field.h"
#include "hand.h"
#include "player.h"
#include "force_zone.h"

void ENDGAME(int ENDTYPE);
Field PlayField;

using namespace std;

int main() {
	int Win = 0;
	char USERINPUT;
	int UserInputCardPosition, UserInputSelectedZone;
	
	cout << "|  __ \\  |  __ \\ | |  | | |  \\/  | |  __ \\\n| |  | | | |__)| | |  | | | \\  / | | |__)|\n| |  | | |  _  / | |  | | | |\\/| | |  ___/\n| |__| | | | \\ \\ | |__| | | |  | | | |\n|_____/  |_|  \\_\\ \\____/  |_|  |_| |_|\nBy: Milan Lacmanovic\n" << endl;
	cout << "\nType H for Help with Inputs, Type R for Game Rules" << endl;
	while (Win == 0) {
		//START GAME
		PlayField.DrumpDeck.StartGame();
		for (int StartGameDraw = 0; StartGameDraw <= 5; StartGameDraw++) {
			if (PlayField.P1.PHand.DrawCardToHand(PlayField.DrumpDeck.DrawCard()) == false) {
				ENDGAME(0);
				break;
			}
			if ((PlayField.P2.PHand.DrawCardToHand(PlayField.DrumpDeck.DrawCard()) == false)) {
				ENDGAME(0);
				break;
			}
		}
		//PlayersTurn
		cout << "\nPlayer 1's Turn" << endl;
		//SHOW FIELD
		
		//Quick test/////////////
		cout << "Player 1 HAND:" << endl;
		cout << "--------\n|" << PlayField.P1.PHand.PlayerHand[0].CardNumberGet()<<"     |\n|  /\\  |\n| (__) |\n|  ||  |\n|     "<< PlayField.P1.PHand.PlayerHand[0].CardNumberGet() <<"|\n--------\n" << endl;
		cout << '[' << PlayField.P1.PHand.PlayerHand[0].CardNumberGet() << PlayField.P1.PHand.PlayerHand[0].CardSuitGet() << ']' << ' ';
		cout << '[' << PlayField.P1.PHand.PlayerHand[1].CardNumberGet() << PlayField.P1.PHand.PlayerHand[1].CardSuitGet() << ']' << ' ';
		cout << '[' << PlayField.P1.PHand.PlayerHand[2].CardNumberGet() << PlayField.P1.PHand.PlayerHand[2].CardSuitGet() << ']' << ' ';
		cout << '[' << PlayField.P1.PHand.PlayerHand[3].CardNumberGet() << PlayField.P1.PHand.PlayerHand[3].CardSuitGet() << ']' << ' ';
		cout << '[' << PlayField.P1.PHand.PlayerHand[4].CardNumberGet() << PlayField.P1.PHand.PlayerHand[4].CardSuitGet() << ']' << endl;
		cout << "Player 2 HAND:" << endl;
		cout << '[' << PlayField.P2.PHand.PlayerHand[0].CardNumberGet() << PlayField.P2.PHand.PlayerHand[0].CardSuitGet() << ']' << ' ';
		cout << '[' << PlayField.P2.PHand.PlayerHand[1].CardNumberGet() << PlayField.P2.PHand.PlayerHand[1].CardSuitGet() << ']' << ' ';
		cout << '[' << PlayField.P2.PHand.PlayerHand[2].CardNumberGet() << PlayField.P2.PHand.PlayerHand[2].CardSuitGet() << ']' << ' ';
		cout << '[' << PlayField.P2.PHand.PlayerHand[3].CardNumberGet() << PlayField.P2.PHand.PlayerHand[3].CardSuitGet() << ']' << ' ';
		cout << '[' << PlayField.P2.PHand.PlayerHand[4].CardNumberGet() << PlayField.P2.PHand.PlayerHand[4].CardSuitGet() << ']' << endl;
		////////////////////////
		//DECISION
		cin >> USERINPUT;
		switch (USERINPUT) {
		case 'h':
			cout << "---GAME HELP---\n\nSuits:\n S: Spade\n D: Diamond\n C: Club\n H: Heart\n\n Info to be added" << endl; //TODO
			break;
		/////////////////////////////////////////////////////////
		case 'r': //Done
			cout << "---DRUMP RULES---\n\nForce Cards:\n ACE = Either 1 OR 11\n 2\n 3\n 4\n 5\n 6\n 7\n 8\n 9\n\nMonster Cards:\n 10,    Cost: 10, Value: 10\n JACK,  Cost: 11, Value: 5\n QUEEN, Cost: 12, Value: 12\n KING,  Cost: 13, Value: 13\n\n\nTake Turns either:\n1.Placing Cards in Force Zones\n2.Tributing Force for Monster Cards\n3.Attacking Opponents Force Zones\n4.Recycling Cards\n\n1.You Can Select a Force Card to place in a Force Zone, Force Cards can be stacked in these zones (Zone totals up to the sum of the number on the cards). Zone cannot exceed sum of 13 otherwise cards are sent to discard pile. (Zones can be attacked by opposing Player) 1st card is placed face up, other stacked cards in zone are facedown. ACE have value of either 1 OR 11\n\n2.You can tribute a zone with a total force that equals the cost of a monster card. You must collect a monster card of each suit to win. Tributed cards go to the discard pile. ACE cards can be used as tribute for a JACK if the ace is in the hand.\n\n3.You can Attack an oppoenets force zone by using your force from the hand, the opponent has the option to defend. Attacking force cards are added to the total of the attacked zone, if zone exceeds 13 then the zone and attacking card is sent to discard and attacking player may draw a card. However Attacked player may defend with any(including Monster) card with higher number than attack card. The Attacker then has the option to attack with a higher card, this goes on until player stops attacking, defending, run out of cards to use or an ACE is played.\n\n4.Players can discard a Monster Card from the hand to either Draw a card from the deck or add a discarded card to their hand.\n\nMore rules can be found online searching 'Drump game', rules are on Drump wikia" << endl;
			break;
		/////////////////////////////////////////////////////////
		case 'F':
			cout << "Card Position:"; cin >> UserInputCardPosition;
			cout << "Select Zone:"; cin >> UserInputSelectedZone;
			PlayField.P1.PHand.PlayCardFromHand(PlayField.P1.ForceZoneGroup[UserInputSelectedZone].AddCardToFZone(PlayField.P1.PHand.SelectCard(UserInputCardPosition)));
			break;
		////////////////////////////////////////////////////////
		default:
			cout << "Incorrect Input, Please Try Again" << endl;
			break;
		}
		//switch USERINPUT: END
	} 
	//while Win = 0: END
}
//Main: END

void ENDGAME(int ENDTYPE) {
	switch (ENDTYPE) {
	case 0:
		cout << "ERROR Cannot Start Game Cannot Draw" << endl;
		break;

		/////////////////
	}
	//switch ENDGAME: END
}
//ENDGAME: END