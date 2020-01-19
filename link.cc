#include "link.h"
#include <string>

Link::Link(size_t row, size_t col, size_t player, size_t strength, char name, bool isHidden, bool switched, bool boosted):
	row{row}, col{col}, player{player}, strength{strength}, name{name}, isHidden{isHidden}, switched{switched}, boosted{boosted} {

}

Link::~Link() {}
/*
size_t Link::getplayer(){
	return this->player;
}
char Link::getname(){
	return this->name;
}
size_t Link::getrow(){
	return this->row;
}
size_t Link::getcol(){
	return this->col;
}
size_t Link::getstrength(){
	return this->strength;
}
*/
void Link::setrow(size_t n) {
	this->row = n;
}


void Link::setcol(size_t n) {
	this->col = n;
}

