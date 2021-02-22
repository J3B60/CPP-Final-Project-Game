#include "monster_zone.h"

MonsterZone::MonsterZone(char ZoneSuitTypeInput) {
	ZoneSuitType = ZoneSuitTypeInput;
}

int MonsterZone::GetMZoneSize() {
	return MZone.size();
}

int MonsterZone::GetMZoneCardNumber() {
	if (MZone.size() == 1) {
		return MZone[0].CardNumberGet();
	}
	else {
		return 0;
	}
}

bool MonsterZone::AddMonsterToZone(Card InputMonsterCard) {
	if (InputMonsterCard.CardTypeGet() == 'M' && InputMonsterCard.CardSuitGet() == ZoneSuitType && MZone.size() == 0) {
		MZone.push_back(InputMonsterCard);
		return true;
	}
	else {
		return false;
	}
}

int MonsterZone::GetMZoneValue() {
	if (MZone.size() == 1) {
		return MZone[0].CardValueGet();
	}
	else {
		return 0;
	}
}