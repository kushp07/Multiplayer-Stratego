#ifndef INFO_H
#define INFO_H

#include "link.h"
#include <string>
#include <vector>

using namespace std;

class CellInfo2 {
	public:
		int row;
		int col;
		bool server;
		int firewall;
};

class CellInfo {
	public:
		size_t strength;
		size_t row;
		size_t col;
		char name;
		size_t player;
		bool isVirus;
		bool isHidden;
		bool switched;
		bool boosted;
};

class PlayerInfo {
	public:
		int downloadedviruses;
		int downloadeddata;
		vector<char> abilities;
		vector<string> order;
		int playerNumber;
		bool revealed[8];
		PlayerInfo(int downloadedviruses, int downloadeddata, vector<char> abilities, vector<string> order, int playerNumber, bool revealed[]):
			downloadedviruses{downloadedviruses}, downloadeddata{downloadeddata}, abilities{abilities}, order{order}, playerNumber{playerNumber} {
				for (int i = 0; i < 8; ++i) {
					this->revealed[i] = revealed[i];
				}
			}
};


#endif
