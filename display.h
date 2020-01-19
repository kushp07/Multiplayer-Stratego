#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H
#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "subject.h"
#include "state.h"
#include "info.h"
using namespace std;

class gameDisplay: public Observer<State> {
	protected:
		vector<vector<char>> theDisplay;
		// Player 1 Data:
		int p1viruses = 0;
		int p1data = 0;
		vector<char> p1abilities;
		//int p1abilities = 5;
		vector<string> p1order;
		bool p2hidden[8] = {true};
		// Player 2 Data:
		int p2viruses = 0;
		int p2data = 0;
		vector<char> p2abilities;
		vector<string> p2order;
		bool p1hidden[8] = {true};

		int playerTurn = 1;
		const int gridSize;
	public:
		gameDisplay(int n);
		void setTurn(int n);
		//virtual void notify(Subject<State> &whoNotified, bool empty) override = 0;
		//friend std::ostream &operator<<(std::ostream &out, const Display &td) = 0;
};






#endif
