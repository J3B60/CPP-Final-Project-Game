#include "field.h"

Field::Field() {
}

Card Field::RemoveCardFromAttackPile() {
	Card temp;
	temp = AttackPile[AttackPile.size() - 1];//Should not be called when AttackPile EMPTY
	AttackPile.pop_back();
	return temp;
}

bool Field::AddCardToAttackPile(Card InputCard) {
	if (AttackPile.size() == 0) {
		AttackPile.push_back(InputCard);
		return true;
	}
	else {
		if (InputCard.CardNumberGet() > AttackPile[AttackPile.size() - 1].CardNumberGet()) {
			AttackPile.push_back(InputCard);
			return true;
		}
		else {
			if (InputCard.CardAceGet() == true) {
				AttackPile.push_back(InputCard);
				return true;
			}
			else {
				return false;
			}
		}
	}
}