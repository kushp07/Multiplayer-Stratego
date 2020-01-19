#include "data.h"
#include <string>

Data::Data(size_t row, size_t col, size_t player, size_t strength, char name, bool isHidden, bool swtiched, bool boosted):
	Link{row, col, player, strength, name, isHidden, switched, boosted} {
}

CellInfo Data::getInfo() const {
	if (switched){
		return CellInfo {strength, row, col, name, player, true, isHidden, switched, boosted};
	}else{
		return CellInfo {strength, row, col, name, player, false, isHidden, switched, boosted};
	}
}

void Data::incstrength() {
	strength++;
}

void Data::reveal() {
	isHidden = false;
}

void Data::setswitched(bool b){
	switched = b;
}

void Data::setboosted(bool b) {
	boosted = b;
}
