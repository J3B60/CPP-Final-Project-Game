#ifndef PLAYER_H
#define PLAYER_H
#include "hand.h"
#include <vector>
#include "force_zone.h"
#include "monster_zone.h"

class Player {
	private:
		
	public:
		Hand PHand; //Players hand
		vector<MonsterZone> MonsterZoneGroup = { MonsterZone('S'), MonsterZone('D'), MonsterZone('C'), MonsterZone('H') }; //Zone for each Suit
		vector<ForceZone> ForceZoneGroup = { ForceZone(), ForceZone(), ForceZone(), ForceZone() }; //4 Zones for Force Cards, 1,2,3,4
		Player();
		Player(int InputPlayerNo); //Creat Player with a Number
		int PlayerNo;  //Player Number to be shown on screen
		int MonsterTotalValue();
		int TotalMonsterCards();
};

#endif