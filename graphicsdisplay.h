#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "state.h"
#include "info.h"
#include "subject.h"
#include "window.h"
#include "display.h"
#include <string>
using namespace std;

class GraphicsDisplay: public gameDisplay {
	Xwindow *board;
	string getColour(size_t i, size_t j);
	string getAbilities(vector<char> abilities);
	void updateBoard();
	int playerscalled;
	public:
		GraphicsDisplay(int n, Xwindow *board);
		~GraphicsDisplay();
//		void init(size_t boardSize);
		void notify(Subject<State> &whoNotified, bool empty) override;
};

#endif

