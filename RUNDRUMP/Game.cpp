#include <iostream>
#include <windows.h>
#include <string>
#include "field.h"
#include "hand.h"
#include "player.h"
#include "force_zone.h"

void ENDGAME(int ENDTYPE);
void SHOW(int PlayerTurn, int ShowType);
void STARTGAME();
Field PlayField;
//void ClearScreen();
int Turns = 1;
bool ATTACK;

using namespace std;

int main() {
	int Win = 0;
	char USERINPUT;
	int UserInputCardPosition, UserInputSelectedZone, CurrentTurnPlayerForSHOW, USERMENUINPUT, UserOptionSelect;
	int ShowType = 1;
	int DRUMPTurn = 0;
	int CurrentOpponentForSHOW;
	int RecycleCounter = 0;
	int ACECHOICE = 0;
	Player* CurrentPlayer = &(PlayField.P1);
	Player* CurrentOpponent = &(PlayField.P2);
	cout << "|  __ \\  |  __ \\ | |  | | |  \\/  | |  __ \\\n| |  | | | |__)| | |  | | | \\  / | | |__)|\n| |  | | |  _  / | |  | | | |\\/| | |  ___/\n| |__| | | | \\ \\ | |__| | | |  | | | |\n|_____/  |_|  \\_\\ \\____/  |_|  |_| |_|\nBy: Milan Lacmanovic\n" << endl;
	while (1) {
		cout << "\n~~~ MAIN MENU ~~~\n 1.Start Game\n 2.View Type\n 3.Rules\n 4.Commands\n 5.Quit" << endl;
		while (!(cin >> USERMENUINPUT)) {
			cin.clear();
			while (cin.get() != '\n') {
				continue;
			}
			cout << "Invalid input.  Try again: ";
		}
		switch (USERMENUINPUT) {
		case 1:
			//GAME
			//START GAME
			PlayField.DrumpDeck.StartGame();
			for (int StartGameDraw = 0; StartGameDraw < 5; StartGameDraw++) {
				if (PlayField.P1.PHand.DrawCardToHand(PlayField.DrumpDeck.DrawCard()) == false) {
					ENDGAME(0);
					Win = 1;
					break;
				}
				if ((PlayField.P2.PHand.DrawCardToHand(PlayField.DrumpDeck.DrawCard()) == false)) {
					ENDGAME(0);
					Win = 1;
					break;
				}
			}
			CurrentTurnPlayerForSHOW = 1;
			CurrentOpponentForSHOW = 2;
			while (Win == 0) {
				//SHOW FIELD
				SHOW(CurrentTurnPlayerForSHOW, ShowType);
				///////////////////////
				//DECISION
				while (!(cin >> USERINPUT)) {
					cin.clear();
					while (cin.get() != '\n') {
						continue;
					}
					cout << "Invalid input.  Try again: ";
				}
				switch (USERINPUT) {
				case 'h':
					cout << "---GAME HELP---\n\nSuits:\n S: Spade\n D: Diamond\n C: Club\n H: Heart\n\nInputs:\nF: Move chosen Force card from hand to chosen Force Zone\nR: Recycle Chosen Monster card then chose to either draw or take card from discard\nM: Select Monster Card and a zone to tribute\nA: Select Force Card to Attack opponents selected zone with\nJ: Tribute Ace in hand for a Jack Monster\nE: End your turn\nh: Help with commands(this text)\nr: Rules of DRUMP\n---------------------------------------" << endl; //TODO
					break;
					/////////////////////////////////////////////////////////
				case 'r': //Done
					cout << "---DRUMP RULES---\n\nForce Cards:\n ACE = Either 1 OR 11\n 2\n 3\n 4\n 5\n 6\n 7\n 8\n 9\n\nMonster Cards:\n 10,    Cost: 10, Value: 10\n JACK,  Cost: 11, Value: 5\n QUEEN, Cost: 12, Value: 12\n KING,  Cost: 13, Value: 13\n\n\nTake Turns either:\n1.Placing Cards in Force Zones\n2.Tributing Force for Monster Cards\n3.Attacking Opponents Force Zones\n4.Recycling Cards\n\n1.You Can Select a Force Card to place in a Force Zone, Force Cards can be stacked in these zones (Zone totals up to the sum of the number on the cards). Zone cannot exceed sum of 13 otherwise cards are sent to discard pile. (Zones can be attacked by opposing Player) 1st card is placed face up, other stacked cards in zone are facedown. ACE have value of either 1 OR 11\n\n2.You can tribute a zone with a total force that equals the cost of a monster card. You must collect a monster card of each suit to win. Tributed cards go to the discard pile. ACE cards can be used as tribute for a JACK if the ace is in the hand.\n\n3.You can Attack an oppoenets force zone by using your force from the hand, the opponent has the option to defend. Attacking force cards are added to the total of the attacked zone, if zone exceeds 13 then the zone and attacking card is sent to discard and attacking player may draw a card. However Attacked player may defend with any(including Monster) card with higher number than attack card. The Attacker then has the option to attack with a higher card, this goes on until player stops attacking, defending, run out of cards to use or an ACE is played.\n\n4.Players can discard a Monster Card from the hand to either Draw a card from the deck or add a discarded card to their hand.\n\nMore rules can be found online searching 'Drump game', rules are on Drump wikia\n-----------------------------------------------------" << endl;
					break;
					/////////////////////////////////////////////////////////
				case 'F':
					do {
						cout << "Card Position:";
						while (!(cin >> UserInputCardPosition)) {
							cin.clear();
							while (cin.get() != '\n') {
								continue;
							}
							cout << "Invalid input.  Try again: ";
						}
					} while (UserInputCardPosition < 1 || UserInputCardPosition > CurrentPlayer->PHand.NoCardsHand());
					do{
						cout << "Select Zone:"; 
						while (!(cin >> UserInputSelectedZone)) {
							cin.clear();
							while (cin.get() != '\n') {
								continue;
							}
							cout << "Invalid input.  Try again: ";
						}
					} while (UserInputSelectedZone < 1 || UserInputSelectedZone > CurrentPlayer->ForceZoneGroup.size());
					CurrentPlayer->PHand.PlayCardFromHand(CurrentPlayer->ForceZoneGroup[UserInputSelectedZone-1].AddCardToFZone(CurrentPlayer->PHand.SelectCard(UserInputCardPosition-1)));
					break;
					////////////////////////////////////////////////////////
				case 'R':
					if (RecycleCounter < 2) {
						do {
							cout << "Card Position:"; 
							while (!(cin >> UserInputCardPosition)) {
								cin.clear();
								while (cin.get() != '\n') {
									continue;
								}
								cout << "Invalid input.  Try again: ";
							}
						} while (UserInputCardPosition < 1 || UserInputCardPosition > CurrentPlayer->PHand.NoCardsHand());
						if (PlayField.DrumpDiscard.RecycleCard(CurrentPlayer->PHand.SelectCard(UserInputCardPosition - 1)) == true) {
							CurrentPlayer->PHand.PlayCardFromHand(true);
							cout << "1.Draw Card\n2.Choose Card from Discard\n:"; 
							while (!(cin >> UserOptionSelect)) {
								cin.clear();
								while (cin.get() != '\n') {
									continue;
								}
								cout << "Invalid input.  Try again: ";
							}
							if (UserOptionSelect == 1) {
								CurrentPlayer->PHand.DrawCardToHand(PlayField.DrumpDeck.DrawCard());
								RecycleCounter++;
							}
							else {
								if (UserOptionSelect == 2) {
									PlayField.DrumpDiscard.DiscardShow();
									UserInputCardPosition = -1;
									while (UserInputCardPosition < 1 || UserInputCardPosition > PlayField.DrumpDiscard.GetDiscardSize()) {
										cout << "Choose Card:"; 
										while (!(cin >> UserInputCardPosition)) {
											cin.clear();
											while (cin.get() != '\n') {
												continue;
											}
											cout << "Invalid input.  Try again: ";
										}
									}
									CurrentPlayer->PHand.DrawCardToHand(PlayField.DrumpDiscard.TakeCard(UserInputCardPosition - 1));
									RecycleCounter++;
									//While Answer not valid Loop: END
								}
								//IF Discard Recycle Chosen: END
							}
							//Else Options: END
						}
					}
			
					break;
					////////////////////////////////////////////////////////
				case 'M':
					do {
						cout << "Card Position:"; 
						while (!(cin >> UserInputCardPosition)) {
							cin.clear();
							while (cin.get() != '\n') {
								continue;
							}
							cout << "Invalid input.  Try again: ";
						}
					} while (UserInputCardPosition < 1 || UserInputCardPosition > CurrentPlayer->PHand.NoCardsHand());
					do {
						cout << "Tribute Zone:"; 
						while (!(cin >> UserInputSelectedZone)) {
							cin.clear();
							while (cin.get() != '\n') {
								continue;
							}
							cout << "Invalid input.  Try again: ";
						}
					} while (UserInputSelectedZone < 1 || UserInputSelectedZone > CurrentPlayer->ForceZoneGroup.size());
					if (CurrentPlayer->PHand.SelectCard(UserInputCardPosition -1).CardCostGet() == CurrentPlayer->ForceZoneGroup[UserInputSelectedZone -1].ZoneTotal()) {
						for (int MonsterZoneLoopCheck = 0; MonsterZoneLoopCheck < CurrentPlayer->MonsterZoneGroup.size(); MonsterZoneLoopCheck++) {
							if (CurrentPlayer->MonsterZoneGroup[MonsterZoneLoopCheck].AddMonsterToZone(CurrentPlayer->PHand.SelectCard(UserInputCardPosition -1)) == true) {
								CurrentPlayer->PHand.PlayCardFromHand(true);
								while (CurrentPlayer->ForceZoneGroup[UserInputSelectedZone -1].GetFZoneSize() > 0) {
									PlayField.DrumpDiscard.DiscardCard(CurrentPlayer->ForceZoneGroup[UserInputSelectedZone -1].RemoveCard());
								}
								break;
							}
							else {
								CurrentPlayer->PHand.PlayCardFromHand(false);
							}
						}
					}
					break;
					////////////////////////////////////////////////////////
				case 'A':
					do {
						cout << "Card Position:"; 
						while (!(cin >> UserInputCardPosition)) {
							cin.clear();
							while (cin.get() != '\n') {
								continue;
							}
							cout << "Invalid input.  Try again: ";
						}
					} while (UserInputCardPosition < 1 || UserInputCardPosition > CurrentPlayer->PHand.NoCardsHand() || CurrentPlayer->PHand.PlayerHand[UserInputCardPosition -1].CardTypeGet() == 'M');
					do {
						cout << "Select Zone:"; 
						while (!(cin >> UserInputSelectedZone)) {
							cin.clear();
							while (cin.get() != '\n') {
								continue;
							}
							cout << "Invalid input.  Try again: ";
						}
					} while (UserInputSelectedZone < 1 || UserInputSelectedZone > CurrentOpponent->ForceZoneGroup.size());
					if (CurrentOpponent->ForceZoneGroup[UserInputSelectedZone-1].GetFZoneSize() > 0) {//If Zone has any cards continue else loop back/cancel attack
						if (CurrentOpponent->ForceZoneGroup[UserInputSelectedZone - 1].AddCardToFZone(CurrentPlayer->PHand.SelectCard(UserInputCardPosition - 1)) == true) {
							CurrentPlayer->PHand.PlayCardFromHand(true);
							CurrentOpponent->ForceZoneGroup[UserInputSelectedZone - 1].AttackReveal = 1;
							cout << "User Attacked Zone: " << UserInputSelectedZone;
						}
						else {
							CurrentOpponent->ForceZoneGroup[UserInputSelectedZone - 1].AttackReveal = 1;
							CurrentPlayer->PHand.PlayCardFromHand(PlayField.AddCardToAttackPile(CurrentPlayer->PHand.SelectCard(UserInputCardPosition - 1)));
							cout << "\a" << "User Attacked Zone: " << UserInputSelectedZone << ", Opponents Decision to Defend";
							ATTACK = true;
							//ATTACK: BEGINS
							while (ATTACK == true) {
								//OPPONENTS CHOICE: BEGINS
								SHOW(CurrentOpponentForSHOW, ShowType);
								UserInputCardPosition = -1;
								while (UserInputCardPosition < 0 || UserInputCardPosition > CurrentOpponent->PHand.NoCardsHand()) {
									cout << "\nSelect Card, 0 to Pass:"; 
									while (!(cin >> UserInputCardPosition)) {
										cin.clear();
										while (cin.get() != '\n') {
											continue;
										}
										cout << "Invalid input.  Try again: ";
									}
									if (UserInputCardPosition > 0){
										if (CurrentOpponent->PHand.SelectCard(UserInputCardPosition-1).CardNumberGet() <= PlayField.AttackPile[PlayField.AttackPile.size() -1].CardNumberGet()){
											if (PlayField.AttackPile[PlayField.AttackPile.size() -1].CardAceGet() == false){
												UserInputCardPosition = -1; //ReDo Loop
											}
										}
									}
								}
								if (UserInputCardPosition == 0) {//Opponent Passes
									cout << "Attack Successful";
									while (PlayField.AttackPile.size() > 0) {//Discard Attack Pile
										PlayField.DrumpDiscard.DiscardCard(PlayField.RemoveCardFromAttackPile());
									}
									while (CurrentOpponent->ForceZoneGroup[UserInputSelectedZone - 1].GetFZoneSize() > 0) {//Discard Opponents ForceZone
										PlayField.DrumpDiscard.DiscardCard(CurrentOpponent->ForceZoneGroup[UserInputSelectedZone - 1].RemoveCard());
									}
									CurrentPlayer->PHand.DrawCardToHand(PlayField.DrumpDeck.DrawCard());//Attacker Draws a Card
									ATTACK = false; //END ATTACk
									break;
								}
								else{//If Opponent Plays Card
									if (CurrentOpponent->PHand.SelectCard(UserInputCardPosition -1).CardAceGet() == true || CurrentOpponent->PHand.SelectCard(UserInputCardPosition - 1).CardNumberGet() == 13) {
										CurrentOpponent->PHand.PlayCardFromHand(PlayField.AddCardToAttackPile(CurrentOpponent->PHand.SelectCard(UserInputCardPosition - 1)));
										while (PlayField.AttackPile.size() > 0) {//Discard Attack Pile
											PlayField.DrumpDiscard.DiscardCard(PlayField.RemoveCardFromAttackPile());
										}
										ATTACK = false;
										break;
									}
									else {
										CurrentOpponent->PHand.PlayCardFromHand(PlayField.AddCardToAttackPile(CurrentOpponent->PHand.SelectCard(UserInputCardPosition - 1)));
									}
								}
								//ATTACKERS CHOICE: BEGINS
								cout << "\a" << "Attackers Turn";
								SHOW(CurrentTurnPlayerForSHOW, ShowType);
								UserInputCardPosition = -1;
								while (UserInputCardPosition < 0 || UserInputCardPosition > CurrentPlayer->PHand.NoCardsHand()) {
									cout << "\nSelect Card, 0 to Pass:"; 
									while (!(cin >> UserInputCardPosition)) {
										cin.clear();
										while (cin.get() != '\n') {
											continue;
										}
										cout << "Invalid input.  Try again: ";
									}
									if (UserInputCardPosition > 0){
										if (CurrentPlayer->PHand.SelectCard(UserInputCardPosition-1).CardNumberGet() <= PlayField.AttackPile[PlayField.AttackPile.size() -1].CardNumberGet()){
											if (PlayField.AttackPile[PlayField.AttackPile.size() -1].CardAceGet() == false){
												UserInputCardPosition = -1; //ReDo Loop
											}
										}
									}
								}
								if (UserInputCardPosition == 0) {//Player Passes
									cout << "Defend Successful";
									while (PlayField.AttackPile.size() > 0) {//Discard Attack Pile
										PlayField.DrumpDiscard.DiscardCard(PlayField.RemoveCardFromAttackPile());
									}
									ATTACK = false; //END ATTACK
									break;
								}
								else {//If Opponent Plays Card
									if (CurrentPlayer->PHand.SelectCard(UserInputCardPosition - 1).CardAceGet() == true || CurrentPlayer->PHand.SelectCard(UserInputCardPosition - 1).CardNumberGet() == 13) {
										CurrentPlayer->PHand.PlayCardFromHand(PlayField.AddCardToAttackPile(CurrentPlayer->PHand.SelectCard(UserInputCardPosition - 1)));
										while (PlayField.AttackPile.size() > 0) {//Discard Attack Pile
											PlayField.DrumpDiscard.DiscardCard(PlayField.RemoveCardFromAttackPile());
										}
										while (CurrentOpponent->ForceZoneGroup[UserInputSelectedZone - 1].GetFZoneSize() > 0) {//Discard Opponents ForceZone
											PlayField.DrumpDiscard.DiscardCard(CurrentOpponent->ForceZoneGroup[UserInputSelectedZone - 1].RemoveCard());
										}
										CurrentPlayer->PHand.DrawCardToHand(PlayField.DrumpDeck.DrawCard());//Attacker Draws a Card
										ATTACK = false;
										break;
									}
									else {
										CurrentOpponent->PHand.PlayCardFromHand(PlayField.AddCardToAttackPile(CurrentOpponent->PHand.SelectCard(UserInputCardPosition - 1)));
									}
								}
							}
						}
					}
					break;
					////////////////////////////////////////////////////////
				case 'J':
					do {
						cout << "Select JACK:"; 
						while (!(cin >> UserInputCardPosition)) {
							cin.clear();
							while (cin.get() != '\n') {
								continue;
							}
							cout << "Invalid input.  Try again: ";
						}
					} while (UserInputCardPosition < 1 || UserInputCardPosition > CurrentPlayer->PHand.NoCardsHand());
					do {
						cout << "Select ACE:"; 
						while (!(cin >> UserInputSelectedZone)) {
							cin.clear();
							while (cin.get() != '\n') {
								continue;
							}
							cout << "Invalid input.  Try again: ";
						}
					} while (UserInputSelectedZone < 1 || UserInputSelectedZone > CurrentPlayer->ForceZoneGroup.size());
					//CASE M COPY, NEED TO EDIT
					if (CurrentPlayer->PHand.SelectCard(UserInputCardPosition - 1).CardCostGet() == 11 && CurrentPlayer->PHand.SelectCard(UserInputSelectedZone - 1).CardAceGet() == true) {
						for (int MonsterZoneLoopCheck = 0; MonsterZoneLoopCheck < CurrentPlayer->MonsterZoneGroup.size(); MonsterZoneLoopCheck++) {
							if (CurrentPlayer->MonsterZoneGroup[MonsterZoneLoopCheck].AddMonsterToZone(CurrentPlayer->PHand.SelectCard(UserInputCardPosition - 1)) == true) {
								CurrentPlayer->PHand.PlayCardFromHand(true);
								if (UserInputSelectedZone > UserInputCardPosition) {//To Fix sending Ace to discard when Jack is sent first the Ace shifts one position if after Jack in hand
									CurrentPlayer->PHand.PlayCardFromHand(PlayField.DrumpDiscard.DiscardCard(CurrentPlayer->PHand.SelectCard(UserInputSelectedZone - 2)));
								}
								else {
									CurrentPlayer->PHand.PlayCardFromHand(PlayField.DrumpDiscard.DiscardCard(CurrentPlayer->PHand.SelectCard(UserInputSelectedZone - 1)));
								}
								break;
							}
							else {
								CurrentPlayer->PHand.PlayCardFromHand(false);
							}
						}
					}
					////////////////////////////
					break;
					////////////////////////////////////////////////////////
				case 'E':
					//RESET COUNTER FOR FZONE
					for (int LoopResetCounter = 0; LoopResetCounter < CurrentPlayer->ForceZoneGroup.size(); LoopResetCounter++) {
						CurrentPlayer->ForceZoneGroup[LoopResetCounter].OncePerTurnCounter = 0;
					}
					//CHECK IF HAND > 5
					while (CurrentPlayer->PHand.NoCardsHand() > 5) {
						do {
							cout << "Select Card to Discard:"; 
							while (!(cin >> UserInputCardPosition)) {
								cin.clear();
								while (cin.get() != '\n') {
									continue;
								}
								cout << "Invalid input.  Try again: ";
							}
						} while (UserInputCardPosition < 1 || UserInputCardPosition > CurrentPlayer->PHand.NoCardsHand());
						UserInputCardPosition = -1;
						while (UserInputCardPosition < 0 || UserInputCardPosition > CurrentPlayer->PHand.NoCardsHand()) {//Repeat Until Valid input
							while (!(cin >> UserInputCardPosition)) {
								cin.clear();
								while (cin.get() != '\n') {
									continue;
								}
								cout << "Invalid input.  Try again: ";
							}
						}
						CurrentPlayer->PHand.PlayCardFromHand(PlayField.DrumpDiscard.DiscardCard(CurrentPlayer->PHand.SelectCard(UserInputCardPosition - 1)));
					}
					//CHECK IF DRUMP
					if (PlayField.P2.TotalMonsterCards() == PlayField.P2.MonsterZoneGroup.size() && PlayField.P1.TotalMonsterCards() == PlayField.P1.MonsterZoneGroup.size()) {
						cout << "DOUBLE DRUMP" << endl;
						ENDGAME(2);
						Win = 1;
						break;
					}
					if (PlayField.P1.TotalMonsterCards() == PlayField.P1.MonsterZoneGroup.size()) {
						cout << "DRUMP" << endl;
						if (DRUMPTurn + 1 == Turns) {
							ENDGAME(3);
							Win = 1;
							break;
						}
						DRUMPTurn = Turns;
					}
					if (PlayField.P2.TotalMonsterCards() == PlayField.P2.MonsterZoneGroup.size()) {
						cout << "DRUMP" << endl;
						ENDGAME(4);
						Win = 1;
						break;
					}
					//CHANGE PLAYER
					if (CurrentTurnPlayerForSHOW == 1) {
						CurrentTurnPlayerForSHOW = 2;
						CurrentOpponentForSHOW = 1;
						CurrentOpponent = &(PlayField.P1);
						CurrentPlayer = &(PlayField.P2);
					}
					else {
						CurrentTurnPlayerForSHOW = 1;
						CurrentOpponentForSHOW = 2;
						CurrentOpponent = &(PlayField.P2);
						CurrentPlayer = &(PlayField.P1);
					}
					//NEXT TURN
					RecycleCounter = 0;
					Turns++;
					cout << "\a";
					//NEXT PLAYER DRAW CARD (DONE HERE SO THAT WIN CAN BE CHANGED TO 1 if cant Draw)
					if (Turns > 2) {//Turns Bigger than number of players
						if (CurrentPlayer->PHand.DrawCardToHand(PlayField.DrumpDeck.DrawCard()) == false) {
							Win = 2;
							ENDGAME(0);
						}
					}
					break;
					////////////////////////////////////////////////////////
				default:
					cout << "Incorrect Input, Please Try Again" << endl;
					break;
				}
				//switch USERINPUT: END
			} 
			//while Win = 0: END
			break;
			//END CASE 1
		case 2:
			cout << "\nSelect View Type:\n1.Console Small Cards\n2.Consol ASCII Art Cards(Unavailable)\n3.GUI(Unvavailable)\n" << endl;
			while (!(cin >> USERMENUINPUT)) {
				cin.clear();
				while (cin.get() != '\n') {
					continue;
				}
				cout << "Invalid input.  Try again: ";
			}
			switch (USERMENUINPUT){
					default:
					ShowType = 1; //Other Options currently not implemented
					break;
			}
			break;
			//END CASE 2
		case 3:
			cout << "---DRUMP RULES---\n\nForce Cards:\n ACE = Either 1 OR 11\n 2\n 3\n 4\n 5\n 6\n 7\n 8\n 9\n\nMonster Cards:\n 10,    Cost: 10, Value: 10\n JACK,  Cost: 11, Value: 5\n QUEEN, Cost: 12, Value: 12\n KING,  Cost: 13, Value: 13\n\n\nTake Turns either:\n1.Placing Cards in Force Zones\n2.Tributing Force for Monster Cards\n3.Attacking Opponents Force Zones\n4.Recycling Cards\n\n1.You Can Select a Force Card to place in a Force Zone, Force Cards can be stacked in these zones (Zone totals up to the sum of the number on the cards). Zone cannot exceed sum of 13 otherwise cards are sent to discard pile. (Zones can be attacked by opposing Player) 1st card is placed face up, other stacked cards in zone are facedown. ACE have value of either 1 OR 11\n\n2.You can tribute a zone with a total force that equals the cost of a monster card. You must collect a monster card of each suit to win. Tributed cards go to the discard pile. ACE cards can be used as tribute for a JACK if the ace is in the hand.\n\n3.You can Attack an oppoenets force zone by using your force from the hand, the opponent has the option to defend. Attacking force cards are added to the total of the attacked zone, if zone exceeds 13 then the zone and attacking card is sent to discard and attacking player may draw a card. However Attacked player may defend with any(including Monster) card with higher number than attack card. The Attacker then has the option to attack with a higher card, this goes on until player stops attacking, defending, run out of cards to use or an ACE is played.\n\n4.Players can discard a Monster Card from the hand to either Draw a card from the deck or add a discarded card to their hand.\n\nMore rules can be found online searching 'Drump game', rules are on Drump wikia\n-----------------------------------------------------" << endl;
			break;
		case 4:
			cout << "---GAME HELP---\n\nSuits:\n S: Spade\n D: Diamond\n C: Club\n H: Heart\n\nInputs:\nF: Move chosen Force card from hand to chosen Force Zone\nR: Recycle Chosen Monster card then chose to either draw or take card from discard\nM: Select Monster Card and a zone to tribute\nA: Select Force Card to Attack opponents selected zone with\nJ: Tribute Ace in hand for a Jack Monster\nE: End your turn\nh: Help with commands(this text)\nr: Rules of DRUMP\n---------------------------------------" << endl; //TODO
			break;
		case 5:
			return 0;
			break;
			//END CASE 5
		default:
			cout << "Invalid Input, Please try again" << endl;
			break;
		}
		//Switch USERMENUINPUT: END
	}
}
//Main: END

void ENDGAME(int ENDTYPE) {
	switch (ENDTYPE) {
	case 0://ERROR FROM DRAWING AT BEGINING OF GAME
		cout << "ERROR Cannot Start Game Cannot Draw" << endl;
		break;
	////////////////////////////////////////////////////////////////////
	case 1://WHEN DECK EMPTY
		cout << "Cant Draw, no cards in deck, Endgame" << endl;
		cout << "Player 1 Total: " << PlayField.P1.MonsterTotalValue() << endl;
		cout << "Player 2 Total: " << PlayField.P2.MonsterTotalValue() << endl;
		if (PlayField.P1.MonsterTotalValue() > PlayField.P2.MonsterTotalValue()) {
			cout << "Player 1 WINS" << endl;
		}
		if (PlayField.P1.MonsterTotalValue() == PlayField.P2.MonsterTotalValue()) {
			cout << "Game Draw" << endl;
		}
		if (PlayField.P1.MonsterTotalValue() < PlayField.P2.MonsterTotalValue()) {
			cout << "Player 2 WINS" << endl;
		}
		break;
	////////////////////////////////////////////////////////////////////
	case 2://WHEN DOUBLE DRUMP
		cout << "Double DRUMP, Endgame" << endl;
		cout << "Player 1 Total: " << PlayField.P1.MonsterTotalValue() << endl;
		cout << "Player 2 Total: " << PlayField.P2.MonsterTotalValue() << endl;
		if (PlayField.P1.MonsterTotalValue() > PlayField.P2.MonsterTotalValue()) {
			cout << "Player 1 WINS" << endl;
		}
		if (PlayField.P1.MonsterTotalValue() == PlayField.P2.MonsterTotalValue()) {
			cout << "Game Draw" << endl;
		}
		if (PlayField.P1.MonsterTotalValue() < PlayField.P2.MonsterTotalValue()) {
			cout << "Player 2 WINS" << endl;
		}
		break;
		////////////////////////////////////////////////////////////////
	case 3://WHEN PLAYER 1 WINS
		cout << "Player 1 WINS" << endl;
		break;
	case 4://WHEN PLAYER 2 WINS
		cout << "Player 2 WINS" << endl;
		break;
	}
	//switch ENDGAME: END
}
//ENDGAME: END

void SHOW(int PlayerTurn, int ShowType) {
	if (ShowType == 1){
		cout << endl << "---GAME---" << "Turn: " << Turns << "-----" << endl;
		cout << endl << "       Player 2" << endl;
		//OPPONENTS HAND: BEGINS
		cout << "Hand:";
		if (PlayerTurn == 2) {
			for (int ShowHandP2 = 0; ShowHandP2 < PlayField.P2.PHand.NoCardsHand(); ShowHandP2++) {
				cout << '[' << PlayField.P2.PHand.PlayerHand[ShowHandP2].CardNumberGet() << PlayField.P2.PHand.PlayerHand[ShowHandP2].CardSuitGet() << ']';
			}
		}
		else {
			for (int ShowHandP2 = 0; ShowHandP2 < PlayField.P2.PHand.NoCardsHand(); ShowHandP2++) {
				cout << "[*]";
			}
		}
		//OPPONENTS MZONES BACK ROW: BEGINS
		cout << endl << endl << "[";
		if (PlayField.P2.MonsterZoneGroup[3].GetMZoneSize() == 0) {//HEARTS
			cout << "M";
		}
		else {
			cout << PlayField.P2.MonsterZoneGroup[3].GetMZoneCardNumber();
		}
		cout << PlayField.P2.MonsterZoneGroup[3].ZoneSuitType;
		cout << "][";
		if (PlayField.P2.MonsterZoneGroup[0].GetMZoneSize() == 0) {//SPADE
			cout << "M";
		}
		else {
			cout << PlayField.P2.MonsterZoneGroup[0].GetMZoneCardNumber();
		}
		cout << PlayField.P2.MonsterZoneGroup[0].ZoneSuitType;
		cout << "] ";
		//OPPONENTS FZONES BACK ROW: BEGINS
		cout << "[";
		if (PlayField.P2.ForceZoneGroup[3].GetFZoneSize() == 0) {
			cout << "FZ 4";
		}
		if (PlayField.P2.ForceZoneGroup[3].GetFZoneSize() >= 1) {
			cout << PlayField.P2.ForceZoneGroup[3].GetFZoneFirstCardNumber() << PlayField.P2.ForceZoneGroup[3].GetFZoneFirstCardSuit();
			//TODO if (){}//If Ace true && Number == 11 then output [*11'suit']
		}
		//////////////////////////////////////////////
		if (PlayField.P2.ForceZoneGroup[3].GetFZoneSize() > 1) {
			if (PlayField.P2.ForceZoneGroup[3].AttackReveal == 0 && PlayerTurn == 1) {
				cout << "*" << (PlayField.P2.ForceZoneGroup[3].GetFZoneSize() - 1);
			}
			else {
				for (int RevealLoop = 1; RevealLoop < PlayField.P2.ForceZoneGroup[3].GetFZoneSize(); RevealLoop++) {//Start from 2nd Card
					cout << "(" << PlayField.P2.ForceZoneGroup[3].GetFZoneCardNumber(RevealLoop) << PlayField.P2.ForceZoneGroup[3].GetFZoneCardSuit(RevealLoop) << ")";
				}
			}
		}
		////////////////////////////////////////////////
		cout << "][";
		if (PlayField.P2.ForceZoneGroup[2].GetFZoneSize() == 0) {
			cout << "FZ 3";
		}
		if (PlayField.P2.ForceZoneGroup[2].GetFZoneSize() >= 1) {
			cout << PlayField.P2.ForceZoneGroup[2].GetFZoneFirstCardNumber() << PlayField.P2.ForceZoneGroup[2].GetFZoneFirstCardSuit();
		}
		if (PlayField.P2.ForceZoneGroup[2].GetFZoneSize() > 1) {
			if (PlayField.P2.ForceZoneGroup[2].AttackReveal == 0 && PlayerTurn == 1) {
				cout << "*" << (PlayField.P2.ForceZoneGroup[2].GetFZoneSize() - 1);
			}
			else {
				for (int RevealLoop = 1; RevealLoop < PlayField.P2.ForceZoneGroup[2].GetFZoneSize(); RevealLoop++) {//Start from 2nd Card
					cout << "(" << PlayField.P2.ForceZoneGroup[2].GetFZoneCardNumber(RevealLoop) << PlayField.P2.ForceZoneGroup[2].GetFZoneCardSuit(RevealLoop) << ")";
				}
			}
		}
		cout << "]" << endl;
		//OPPONENTS MZONES FRONT ROW: BEGINS
		cout << "[";
		if (PlayField.P2.MonsterZoneGroup[1].GetMZoneSize() == 0) {//HEARTS
			cout << "M";
		}
		else {
			cout << PlayField.P2.MonsterZoneGroup[1].GetMZoneCardNumber();
		}
		cout << PlayField.P2.MonsterZoneGroup[1].ZoneSuitType;
		cout << "][";
		if (PlayField.P2.MonsterZoneGroup[2].GetMZoneSize() == 0) {//SPADE
			cout << "M";
		}
		else {
			cout << PlayField.P2.MonsterZoneGroup[2].GetMZoneCardNumber();
		}
		cout << PlayField.P2.MonsterZoneGroup[2].ZoneSuitType;
		cout << "] ";
		//OPPONENTS FZONES FRONT ROW: BEGINS
		cout << "[";
		if (PlayField.P2.ForceZoneGroup[1].GetFZoneSize() == 0) {
			cout << "FZ 2";
		}
		if (PlayField.P2.ForceZoneGroup[1].GetFZoneSize() >= 1) {
			cout << PlayField.P2.ForceZoneGroup[1].GetFZoneFirstCardNumber() << PlayField.P2.ForceZoneGroup[1].GetFZoneFirstCardSuit();
		}
		if (PlayField.P2.ForceZoneGroup[1].GetFZoneSize() > 1) {
			if (PlayField.P2.ForceZoneGroup[1].AttackReveal == 0 && PlayerTurn == 1) {
				cout << "*" << (PlayField.P2.ForceZoneGroup[1].GetFZoneSize() - 1);
			}
			else {
				for (int RevealLoop = 1; RevealLoop < PlayField.P2.ForceZoneGroup[1].GetFZoneSize(); RevealLoop++) {//Start from 2nd Card
					cout << "(" << PlayField.P2.ForceZoneGroup[1].GetFZoneCardNumber(RevealLoop) << PlayField.P2.ForceZoneGroup[1].GetFZoneCardSuit(RevealLoop) << ")";
				}
			}
		}
		cout << "][";
		if (PlayField.P2.ForceZoneGroup[0].GetFZoneSize() == 0) {
			cout << "FZ 1";
		}
		if (PlayField.P2.ForceZoneGroup[0].GetFZoneSize() >= 1) {
			cout << PlayField.P2.ForceZoneGroup[0].GetFZoneFirstCardNumber() << PlayField.P2.ForceZoneGroup[0].GetFZoneFirstCardSuit();
		}
		if (PlayField.P2.ForceZoneGroup[0].GetFZoneSize() > 1) {
			if (PlayField.P2.ForceZoneGroup[0].AttackReveal == 0 && PlayerTurn == 1) {
				cout << "*" << (PlayField.P2.ForceZoneGroup[0].GetFZoneSize() - 1);
			}
			else {
				for (int RevealLoop = 1; RevealLoop < PlayField.P2.ForceZoneGroup[0].GetFZoneSize(); RevealLoop++) {//Start from 2nd Card
					cout << "(" << PlayField.P2.ForceZoneGroup[0].GetFZoneCardNumber(RevealLoop) << PlayField.P2.ForceZoneGroup[0].GetFZoneCardSuit(RevealLoop) << ")";
				}
			}
		}
		cout << "]" << endl;
		//OPPONENTS SIDE: END
		//MIDDLE FIELD: BEGINS
		cout << endl;
		if (ATTACK == true) {
			cout << "[";
		}
		else {
			cout << "    [";
		}
		if (PlayField.DrumpDeck.PlayingDeckSize() > 0) {
			cout << "Deck";
		}
		else {
			cout << "-";
		}
		cout << "] ";
		//ATTACK MIDDLE FIELD: BEGIN
		if (ATTACK == true) {
			cout << "[" <<PlayField.AttackPile[PlayField.AttackPile.size() - 1].CardNumberGet() << PlayField.AttackPile[PlayField.AttackPile.size() - 1].CardSuitGet() << "] ";
		}
		//DISCARD MIDDLE FIELD: BEGIN
		cout << "[";
		if (PlayField.DrumpDiscard.GetDiscardSize() > 0) {
			cout << "DisC";
		}
		else {
			cout << "-";
		}
		cout << "]" << endl << endl;
		//MIDDLE FIELD: END
		//PLAYER 1 FZONE FRONT ROW: BEGINS
		cout << "[";
		if (PlayField.P1.ForceZoneGroup[0].GetFZoneSize() == 0) {
			cout << "FZ 1";
		}
		if (PlayField.P1.ForceZoneGroup[0].GetFZoneSize() >= 1) {
			cout << PlayField.P1.ForceZoneGroup[0].GetFZoneFirstCardNumber() << PlayField.P1.ForceZoneGroup[0].GetFZoneFirstCardSuit();
		}
		if (PlayField.P1.ForceZoneGroup[0].GetFZoneSize() > 1) {
			if (PlayField.P1.ForceZoneGroup[0].AttackReveal == 0 && PlayerTurn == 2) {
				cout << "*" << (PlayField.P1.ForceZoneGroup[0].GetFZoneSize() - 1);
			}
			else {
				for (int RevealLoop = 1; RevealLoop < PlayField.P1.ForceZoneGroup[0].GetFZoneSize(); RevealLoop++) {//Start from 2nd Card
					cout << "(" << PlayField.P1.ForceZoneGroup[0].GetFZoneCardNumber(RevealLoop) << PlayField.P1.ForceZoneGroup[0].GetFZoneCardSuit(RevealLoop) << ")";
				}
			}
		}
		cout << "][";
		if (PlayField.P1.ForceZoneGroup[1].GetFZoneSize() == 0) {
			cout << "FZ 2";
		}
		if (PlayField.P1.ForceZoneGroup[1].GetFZoneSize() >= 1) {
			cout << PlayField.P1.ForceZoneGroup[1].GetFZoneFirstCardNumber() << PlayField.P1.ForceZoneGroup[1].GetFZoneFirstCardSuit();
		}
		if (PlayField.P1.ForceZoneGroup[1].GetFZoneSize() > 1) {
			if (PlayField.P1.ForceZoneGroup[1].AttackReveal == 0 && PlayerTurn == 2) {
				cout << "*" << (PlayField.P1.ForceZoneGroup[1].GetFZoneSize() - 1);
			}
			else {
				for (int RevealLoop = 1; RevealLoop < PlayField.P1.ForceZoneGroup[1].GetFZoneSize(); RevealLoop++) {//Start from 2nd Card
					cout << "(" << PlayField.P1.ForceZoneGroup[1].GetFZoneCardNumber(RevealLoop) << PlayField.P1.ForceZoneGroup[1].GetFZoneCardSuit(RevealLoop) << ")";
				}
			}
		}
		cout << "] ";
		//PLAYER 1 MZONE FRONT ROW: BEGINS
		cout << "[";
		if (PlayField.P1.MonsterZoneGroup[2].GetMZoneSize() == 0) {//HEARTS
			cout << "M";
		}
		else {
			cout << PlayField.P1.MonsterZoneGroup[2].GetMZoneCardNumber();
		}
		cout << PlayField.P1.MonsterZoneGroup[2].ZoneSuitType;
		cout << "][";
		if (PlayField.P1.MonsterZoneGroup[1].GetMZoneSize() == 0) {//SPADE
			cout << "M";
		}
		else {
			cout << PlayField.P1.MonsterZoneGroup[1].GetMZoneCardNumber();
		}
		cout << PlayField.P1.MonsterZoneGroup[1].ZoneSuitType;
		cout << "]" << endl;
		//PLAYERS FZONE BACK ROW: BEGINS
		cout << "[";
		if (PlayField.P1.ForceZoneGroup[2].GetFZoneSize() == 0) {
			cout << "FZ 3";
		}
		if (PlayField.P1.ForceZoneGroup[2].GetFZoneSize() >= 1) {
			cout << PlayField.P1.ForceZoneGroup[2].GetFZoneFirstCardNumber() << PlayField.P1.ForceZoneGroup[2].GetFZoneFirstCardSuit();
		}
		if (PlayField.P1.ForceZoneGroup[2].GetFZoneSize() > 1) {
			if (PlayField.P1.ForceZoneGroup[2].AttackReveal == 0 && PlayerTurn == 2) {
				cout << "*" << (PlayField.P1.ForceZoneGroup[2].GetFZoneSize() - 1);
			}
			else {
				for (int RevealLoop = 1; RevealLoop < PlayField.P1.ForceZoneGroup[2].GetFZoneSize(); RevealLoop++) {//Start from 2nd Card
					cout << "(" << PlayField.P1.ForceZoneGroup[2].GetFZoneCardNumber(RevealLoop) << PlayField.P1.ForceZoneGroup[2].GetFZoneCardSuit(RevealLoop) << ")";
				}
			}
		}
		cout << "][";
		if (PlayField.P1.ForceZoneGroup[3].GetFZoneSize() == 0) {
			cout << "FZ 4";
		}
		if (PlayField.P1.ForceZoneGroup[3].GetFZoneSize() >= 1) {
			cout << PlayField.P1.ForceZoneGroup[3].GetFZoneFirstCardNumber() << PlayField.P1.ForceZoneGroup[3].GetFZoneFirstCardSuit();
		}
		if (PlayField.P1.ForceZoneGroup[3].GetFZoneSize() > 1) {
			if (PlayField.P1.ForceZoneGroup[3].AttackReveal == 0 && PlayerTurn == 2) {
				cout << "*" << (PlayField.P1.ForceZoneGroup[3].GetFZoneSize() - 1);
			}
			else {
				for (int RevealLoop = 1; RevealLoop < PlayField.P1.ForceZoneGroup[3].GetFZoneSize(); RevealLoop++) {//Start from 2nd Card
					cout << "(" << PlayField.P1.ForceZoneGroup[3].GetFZoneCardNumber(RevealLoop) << PlayField.P1.ForceZoneGroup[3].GetFZoneCardSuit(RevealLoop) << ")";
				}
			}
		}
		cout << "] ";
		//PLAYERS MZONE BACK ROW: BEGINS
		cout << "[";
		if (PlayField.P1.MonsterZoneGroup[0].GetMZoneSize() == 0) {//HEARTS
			cout << "M";
		}
		else {
			cout << PlayField.P1.MonsterZoneGroup[0].GetMZoneCardNumber();
		}
		cout << PlayField.P1.MonsterZoneGroup[0].ZoneSuitType;
		cout << "][";
		if (PlayField.P1.MonsterZoneGroup[3].GetMZoneSize() == 0) {//SPADE
			cout << "M";
		}
		else {
			cout << PlayField.P1.MonsterZoneGroup[3].GetMZoneCardNumber();
		}
		cout << PlayField.P1.MonsterZoneGroup[3].ZoneSuitType;
		cout << "]" << endl << endl << "Hand:";
		//PLAYERS HAND
		if (PlayerTurn == 1) {
			for (int ShowHandP1 = 0; ShowHandP1 < PlayField.P1.PHand.NoCardsHand(); ShowHandP1++) {
				cout << '[' << PlayField.P1.PHand.PlayerHand[ShowHandP1].CardNumberGet() << PlayField.P1.PHand.PlayerHand[ShowHandP1].CardSuitGet() << ']';
			}
		}
		else {
			for (int ShowHandP1 = 0; ShowHandP1 < PlayField.P1.PHand.NoCardsHand(); ShowHandP1++) {
				cout << "[*]";
			}
		}
		cout << endl << "       Player 1" << endl << endl << ":";
	}
	//SHOWTYPE 1: END
	if (ShowType == 2) { //TODO
		//####################
	}
	//SHOWTYPE 2: END
}

void STARTGAME() {
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
}

/* Not Used so far
void ClearScreen() //TAKEN FROM INTERNET# To be used to clear the command line so that opponent cant see previous move/ opponents hand
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	/*if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	/*if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	/*if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	/*SetConsoleCursorPosition(hStdOut, homeCoords);
}
*/