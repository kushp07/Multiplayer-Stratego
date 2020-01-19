#include "cell.h"
#include <iostream>

Cell::Cell(size_t r, size_t c, bool server, bool player1firewall, bool player2firewall, bool player1trap, bool player2trap): row{r}, col{c}, 
	server{server}, player1firewall{player1firewall}, player2firewall{player2firewall}, player1trap{player1trap}, player2trap{player2trap}  {
	setState(State{StateType::Cell});
}

void Cell::addLink(Link* l) {
	this->l = l;
}

bool Cell::isServer() {
	return server;
}

void Cell::setLink(Link * l) {
	// ORDER MATTERS FOR THIS DONT CHANGE PLSSS
	if (l == nullptr) {
		notifyObservers(true);
		this->l = l;
	} else {
		this->l = l;
		notifyObservers(false);
	}
}

Link* Cell::getLink() {
	return l;
}

void Cell::setfirewall(int player, bool b) {
	if(player == 1) {
		player1firewall = b;
	} else if(player == 2) {
		player2firewall = b;
	}
	notifyObservers(true);
}
bool Cell::isfirewall(int player) {
	if(player == 1) {
		return player1firewall;
	} else if(player == 2) {
		return player2firewall;
	}
}

CellInfo2 Cell::getInfo2() const {
	int firewall;
	if (player1firewall) {
		firewall = 1;
	} else if (player2firewall) {
		firewall = 2;
	} else {
		firewall = 0;
	}
	int r = row - 1;
	int c = col - 1;
	return CellInfo2 {r, c, server, firewall};
}

void Cell::settrap(int player, bool b) {
	if(player == 1) {
                player1trap = b;
        } else if(player == 2) {
                player2trap = b;
        }
}

bool Cell::istrap(int player) {
        if(player == 1) {
                return player1trap;
        } else if(player == 2) {
                return player2trap;
        }
}
