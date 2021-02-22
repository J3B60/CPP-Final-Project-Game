#ifndef MONSTERZONE_H
#define MONSTERZONE_H
#include "card.h"
#include <vector>

using namespace std;

class MonsterZone {
	private:
		vector<Card> MZone = {}; //Monster Card Zone (MAX size = 1 else error).
	public:
		char ZoneSuitType; //Monster Zone Suit Type (one of every suit)
		MonsterZone(char ZoneSuitTypeInput); //Construct zone of each suit for each player
		int GetMZoneSize();
		int GetMZoneCardNumber();
		int GetMZoneValue();
		bool AddMonsterToZone(Card InputMonsterCard);
};

#endif