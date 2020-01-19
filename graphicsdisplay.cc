#include "graphicsdisplay.h"
#include <vector>
#include <iostream>
using namespace std;

GraphicsDisplay::GraphicsDisplay(int n, Xwindow *board): gameDisplay{n}, board{board} {
}

GraphicsDisplay::~GraphicsDisplay(){
	delete board;
}

void GraphicsDisplay::notify(Subject<State> &whoNotified, bool empty) {
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
		playerscalled += 1;
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
	if (playerscalled >= 2) {
		updateBoard();
	}
}

string GraphicsDisplay::getColour(size_t i, size_t j) {
	char name = theDisplay[i][j];
	int index;
	int player = 0;
	string colourstrength;
	string colour;
	string strength;
	if (name == '.') {
		colour = "white";
		strength += "0";
	} else if (name == 'S') {
		colour =  "blue";
		strength += "0";
	} else if (name == 'M' || name == 'W') {
		if (name == 'M'){
			colour = "blueM";
		}else {
			colour = "blueW";
		}
		strength += "0";
	} else if (name <= 'h' && name >= 'a') {
		index = name - 'a';
		player = 1;
	} else if (name <= 'H' && name >= 'A') {
		index = name - 'A';
		player = 2;
	}

	if (player == 1 && playerTurn == 1) {
		if (p1order[index][0] == 'V') {
			colour = "red";
		} else if (p1order[index][0] == 'D') {
			colour = "green";
		}
		strength += p1order[index][1];
	} else if (player == 1 && playerTurn == 2) {
		if (p1hidden[index]) {
			colour = "black";
		} else if (p1order[index][0] == 'V') {
			colour = "red";
		} else if (p1order[index][0] == 'D') {
			colour = "green";
		}
		strength += p1order[index][1];
	} else if (player == 2 && playerTurn == 1) {
		if (p2hidden[index]) {
			colour = "black";
		} else if (p2order[index][0] == 'V') {
			colour = "red";
		} else if (p2order[index][0] == 'D') {
			colour = "green";
		}
		strength += p2order[index][1];
	} else if (player == 2 && playerTurn == 2) {
		if (p2order[index][0] == 'V') {
			colour = "red";
		} else if (p2order[index][0] == 'D') {
			colour = "green";
		}
		strength += p2order[index][1];
	}
	colourstrength = name + strength + colour;
	return colourstrength;
}

string GraphicsDisplay::getAbilities(vector<char> abilities){
	string s;
	for (int i=0;i<abilities.size();++i){
		s += abilities[i];
	}
	return s;
}

string IntToChar(int n){
	string s;
	char c = '0' + n;
	s += c;
	return s;
}

void GraphicsDisplay::updateBoard() {
	size_t bufferheight = (600-500)/2;
	size_t length = 500 / gridSize;
	string p1astring = "Abilities: "+getAbilities(p1abilities);
	string p2astring = "Abilities: "+getAbilities(p2abilities);
	string p1v = IntToChar(p1viruses);
	string p2v = IntToChar(p2viruses);
	string p1d = IntToChar(p1data);
	string p2d = IntToChar(p2data);
	string p1dstring = "Downloaded: " + p1d + "D " + p1v + "V";
	string p2dstring = "Downloaded: " + p2d + "D " + p2v + "V";
	string p1string = "Player 1: ";
	string p2string = "Player 2: ";
	for (size_t i = 0; i < gridSize; ++i) {
		for (size_t j = 0; j < gridSize; ++j) {
			string colourstrength = getColour(i, j);
			string colour = colourstrength.substr(2, colourstrength.length() - 1);
			string strength = colourstrength.substr(1, 1);
			string name = colourstrength.substr(0,1);
			if (colour == "black") {
				board->fillRectangle(j * length + j , (i * length + i) + bufferheight, length, length, Xwindow::Black);
				board->fillRectangle((j * length + j) + (length/4),((i * length + i) + bufferheight)+(length/4), length/2, length/2, Xwindow::White);
				board->drawString(j * length + j + (length / 2) -2, i * length + i + (length / 2) + 3 + bufferheight, name);
			} else if (colour == "white") {
				board->fillRectangle(j * length + j,(i * length + i) + bufferheight, length, length, Xwindow::White);
			} else if (colour == "red") {
				board->fillRectangle(j * length + j,(i * length + i) + bufferheight, length, length, Xwindow::Black);
				board->fillRectangle((j * length + j) + (length/4),((i * length + i) + bufferheight)+(length/4), length/2, length/2, Xwindow::Red);
				board->drawString(j * length + j + (length / 2) - 10, i * length + i + (length / 2) + bufferheight + 3, name + " " + strength);
			} else if (colour == "green") {
				board->fillRectangle(j * length + j, i * length + i + bufferheight, length, length, Xwindow::Black);
				board->fillRectangle((j * length + j) + (length/4),((i * length + i) + bufferheight)+(length/4), length/2, length/2, Xwindow::Green);
				board->drawString(j * length + j + (length / 2) - 10, i * length + i + (length / 2) + bufferheight + 3, name + " " + strength);
			} else if ((colour == "blueM") || (colour == "blueW")) {
				string which = colour.substr(4,1);
				board->fillRectangle(j * length + j, i * length + i + bufferheight, length, length, Xwindow::Red);
				board->drawString(j * length + j + (length / 2), i * length + i + (length / 2) + bufferheight, which);
			} else if (colour == "blue") {
				board->fillRectangle(j * length + j, i * length + i + bufferheight, length, length, Xwindow::Blue);
				board->drawString(j * length + j + (length / 2), i * length + i + (length / 2) + bufferheight, "S");
			}
		}
	}
	board->fillRectangle(0,0,500,50, Xwindow::White);
	board->fillRectangle(0,550,500,50, Xwindow::White);
	board->drawString(30,33,p1string);
	board->drawString(30,575,p2string);
	board->drawString(205,33,p1dstring);
	board->drawString(205,575,p2dstring);
	board->drawString(380,33,p1astring);
	board->drawString(380,575,p2astring);
}

