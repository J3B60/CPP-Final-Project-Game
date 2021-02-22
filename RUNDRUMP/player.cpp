#include "player.h"

Player::Player(int InputPlayerNo) {
	PlayerNo = InputPlayerNo;
}

Player::Player() {

}

int Player::MonsterTotalValue() {
	int Total = 0;
	for (int TotalLoop = 0; TotalLoop < MonsterZoneGroup.size(); TotalLoop++) {
		Total = Total + MonsterZoneGroup[TotalLoop].GetMZoneValue();
	}
	return Total;
}
int Player::TotalMonsterCards() {
	int Total = 0;
	for (int TotalLoop = 0; TotalLoop < MonsterZoneGroup.size(); TotalLoop++) {
		Total = Total + MonsterZoneGroup[TotalLoop].GetMZoneSize();
	}
	return Total;
}