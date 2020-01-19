#include "player.h"
#include <vector>
#include <map>
#include <iostream>
#include "ability.h"
#include "info.h"

using namespace std;

Player::Player(vector<Link*> downloaded, vector<Link*> owns, vector<char> abilities, vector<string> order, int playerNumber):
	downloaded{downloaded}, owns{owns}, abilities{abilities}, order{order}, playerNumber{playerNumber} {
		setState(State{StateType::Player});
}

Player::~Player() {
	for (int i = 0; i < owns.size(); ++i) {
		delete owns[i];
	}
	owns.clear();
}

vector<Link*> Player::getowns(){
	return this->owns;
}

vector<Link*> Player::getdownloaded() {
	return this->downloaded;
}

vector<char> Player::getabilities(){
	return this->abilities;
}

void Player::addability(char c) {
	abilities.emplace_back(c);
}

void Player::downloadLink(Link *l) {
	downloaded.emplace_back(l);
	if (l->getInfo().isVirus) {
		downloadedviruses += 1;
	} else {
		downloadeddata += 1;
	}
	l->setrow(10);
	l->setcol(10);	
	l->reveal();
	notifyObservers(true);

}


PlayerInfo Player::getInfo() const {
	bool revealed[8] = {true};
	for (int i = 0; i < 8; ++i) {
		revealed[i] = owns[i]->getInfo().isHidden;
	}
	return PlayerInfo {downloadedviruses, downloadeddata, abilities, order, playerNumber, revealed};
}

void Player::removeability(int i) {
	abilities.erase(abilities.begin() + i);
	notifyObservers(true);
}

vector<string> &Player::getorder(){
	return order;
}
