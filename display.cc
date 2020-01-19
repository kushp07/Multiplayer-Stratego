#include "display.h"
#include <vector>
#include <iostream>
using namespace std;

gameDisplay::gameDisplay(int n): gridSize{n} {
	vector<vector<char>> display;
	for (int i = 1; i <= n; ++i) {
		vector<char> row;
		for (int j = 1; j <= n; ++j) {
			char current = '.';
			if ((i == 1 && j == 4) || (i == 1 && j == 5) ||
			    (i == 8 && j == 4) || (i == 8 && j == 5)) {
				current = 'S';
			}
			row.emplace_back(current);
		}
		display.emplace_back(row);
	}
	this->theDisplay = display;
	for (int i = 0; i < n; ++i) {
		p1order.emplace_back("");
		p2order.emplace_back("");
	}
	for (int i = 0; i < 5; ++i) {
		p1abilities.emplace_back(' ');
		p2abilities.emplace_back(' ');
	}
}

void gameDisplay::setTurn(int n) {
	playerTurn = n;
}



