#include "textdisplay.h"
#include <vector>
#include <iostream>
using namespace std;

TextDisplay::TextDisplay(int n): gameDisplay{n} {

}

void TextDisplay::notify(Subject<State> &whoNotified, bool empty) {
	StateType s = whoNotified.getState().statetype;
	if (s == StateType::Cell) {
		int row;
		int col;
		char name;
		int firewall;
		if (whoNotified.getLink()) {
			row = whoNotified.getLink()->getInfo().row;
			col = whoNotified.getLink()->getInfo().col;
			name = whoNotified.getLink()->getInfo().name;
		} else {
			row = whoNotified.getInfo2().row;
			col = whoNotified.getInfo2().col;
		}
		firewall = whoNotified.getInfo2().firewall;
		if (firewall == 1) {
			theDisplay[row][col] = 'M';
		} else if (firewall == 2) {
			theDisplay[row][col] = 'W';
		} else if (!empty) {
			theDisplay[row][col] = name;
		} else {
			theDisplay[row][col] = '.';
		}
	} else if (s == StateType::Player) {
		if (whoNotified.getInfo().playerNumber == 1) {
			p1data = whoNotified.getInfo().downloadeddata;
			p1viruses = whoNotified.getInfo().downloadedviruses;
			// Abilities
			int toRemove = p1abilities.size() - whoNotified.getInfo().abilities.size();
			for (int i = 0; i < whoNotified.getInfo().abilities.size(); ++i){
				p1abilities.at(i) = whoNotified.getInfo().abilities.at(i);
			}
			for (int i = 0; i < toRemove; ++i) {
				p1abilities.pop_back();
			}
			////////////////
			for (int i = 0; i < whoNotified.getInfo().order.size(); ++i) {
				p1order.at(i) = whoNotified.getInfo().order.at(i); 
			}
			for (int i = 0; i < 8; ++i) {
				p1hidden[i] = whoNotified.getInfo().revealed[i];
			}
		} else if (whoNotified.getInfo().playerNumber == 2) {
			p2data = whoNotified.getInfo().downloadeddata;
			p2viruses = whoNotified.getInfo().downloadedviruses;
			// Abilities
			int toRemove = p2abilities.size() - whoNotified.getInfo().abilities.size();
			for (int i = 0; i < whoNotified.getInfo().abilities.size(); ++i){
				p2abilities.at(i) = whoNotified.getInfo().abilities.at(i);
			}
			for (int i = 0; i < toRemove; ++i) {
				p2abilities.pop_back();
			}
			////////////////
			for (int i = 0; i < whoNotified.getInfo().order.size(); ++i) {
				p2order.at(i) = whoNotified.getInfo().order.at(i);
			}
			for (int i = 0; i < 8; ++i) {
				p2hidden[i] = whoNotified.getInfo().revealed[i];
			}
		}	
	}
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	out << "Player 1:" << endl;
	out << "Downloaded: " << td.p1data << "D, " << td.p1viruses << "V" << endl;
	out << "Abilities: " << td.p1abilities.size() << endl;
	for (int i = 0; i < 8; ++i) {
		char c = 'a' + i;
		string key = "";
		if (td.playerTurn == 1) {
			key += td.p1order.at(i);
		} else if (td.p1hidden[i]) {
			key += "?";
		} else if (!td.p1hidden[i]) {
			key += td.p1order.at(i);
		}
		out << c << ": " << key << "  ";
		if (i == 3 || i == 7) {
			out << endl;
		}
	}
	out << "========" << endl;
	for (int i = 0; i < td.gridSize; ++i) {
		for (int j = 0; j < td.gridSize; ++j) {
			out << td.theDisplay[i][j];
		}
		out << endl;
	}
	out << "========" << endl;
	out << "Player 2:" << endl;
	out << "Downloaded: " << td.p2data << "D. " << td.p2viruses << "V" << endl;
	out << "Abilities: " << td.p2abilities.size() << endl;
	for (int i = 0; i < 8; ++i) {
		char c = 'A' + i;
		string key = "";
		if (td.playerTurn == 2) {
			key += td.p2order.at(i);
		} else if (td.p2hidden[i]) {
			key += "?";
		} else if (!td.p2hidden[i]) {
			key += td.p2order.at(i);
		}
		out << c << ": " << key << "  ";
		if (i == 3 || i == 7) {
			out << endl;
		}
	}
	out << "----------------------------" << endl;
	if (td.playerTurn == 1) {
		out << "Player 1's Turn: " << endl;
	} else if (td.playerTurn == 2) {
		out << "Player 2's Turn: " << endl;
	}
	return out;
}
