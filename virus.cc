#include "virus.h"
#include <string>
#include <iostream>

Virus::Virus(size_t row, size_t col, size_t player, size_t strength, char name, bool isHidden, bool switched, bool boosted):
	Link{row, col, player, strength, name, isHidden, switched, boosted} {
}
CellInfo Virus::getInfo() const {
	if (switched){
		return CellInfo {strength, row, col, name, player, false, isHidden, switched, boosted};
	}else{
		return CellInfo {strength, row, col, name, player, true, isHidden, switched, boosted};
	}
}

void Virus::incstrength() {
	strength++;
}

void Virus::reveal() {
	isHidden = false;
}

void Virus::setswitched(bool b){
	switched = b;
}

void Virus::setboosted(bool b) {
	boosted = b;
}

