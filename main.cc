#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include "grid.h"
#include "exception.h"
#include <stdexcept>
//#include "state.h"
//#include "cell.h"
#include "window.h"
#include "graphicsdisplay.h"
#include "display.h"
#include "ability.h"
using namespace std;


size_t charToInt1(char c) {
        string s;
        s += c;
        size_t n;
        istringstream ss{s};
        ss >> n;
        return n;
}

vector<string> addLinks(string s){
	int length = s.length();
	vector<string> porder;
	string lError = "\n*Invalid Links*\n";
	if(length != 16){
		throw Exception(lError);
	}
	for (int i=0;i<length;i+=2){
		if (s[i] == 'D' || s[i] == 'V'){
			if ((charToInt1(s[i+1]) <= 4) && (charToInt1(s[i+1]) > 0)){
				string t;
				char link = s[i];
				char linkStrength = s[i+1];
				t += link;
				t +=linkStrength;
				porder.push_back(t);
			}
			else{
				throw Exception(lError);
			}
		}
		else {
			throw Exception(lError);
		}
	}
	return porder;
}

vector<char> addAbilities(string s) {
	int length = s.length();
	vector<char> p1abilities;
	int countL = 0;
	int countF = 0;
	int countD = 0;
	int countP = 0;
	int countS = 0;
	int countA = 0;
	int countT = 0;
	int countE = 0;
	int max = 2;
	string limitError = "\n*Cannot have more than two of the same ability*\n";
	string aError = "\n*Invalid Abilities*\n";
	if(length != 5) {
		throw Exception(aError);
	}
	for (int i = 0; i < length; ++i) {
		if (s[i] == 'L') {
			if (countL < max){
				p1abilities.push_back(s[i]);
				countL++;
			}else{
				throw Exception(limitError);
			}
		} else if (s[i] == 'F') {
			if (countF < max){
				p1abilities.push_back(s[i]);
				countF++;
			}else{
				throw Exception(limitError);
			}
	  	} else if (s[i] == 'D') {
                        if (countD < max){
                                p1abilities.push_back(s[i]);
				countD++;
                        }else{
                                throw Exception(limitError);
                        } 
		} else if (s[i] == 'P') {
     			if (countP < max){
				p1abilities.push_back(s[i]);
                                countP++;
                        }else{
                                throw Exception(limitError);
                        }
		} else if (s[i] == 'S') {
                        if (countS < max){
				p1abilities.push_back(s[i]);
                                countS++;
                        }else{
                                throw Exception(limitError);
                        }
		} else if (s[i] == 'W') {
                        if (countA < max){
                                p1abilities.push_back(s[i]);
				countA++;
                        }else{
                                throw Exception(limitError);
                        }
		} else if (s[i] == 'T') {
                        if (countT < max){
                                p1abilities.push_back(s[i]);
				countT++;
                        }else{
                                throw Exception(limitError);
                        }
		} else if (s[i] == 'E') {
                        if (countE < max){
                                p1abilities.push_back(s[i]);
				countE++;
                        }else{
                                throw Exception(limitError);
                        }
		}
		else {
			throw Exception(aError);
		}
	}
	return p1abilities;
}

int main(int argc, char *argv[]) {
	string s;
	bool graphics = false;
	bool A1 = false;
	bool A2 = false;
	bool L1 = false;
	bool L2 = false;
	vector<char> p1abilities = addAbilities("LFDSP");
	vector<char> p2abilities = addAbilities("LFDSP");
	vector<string> p1order{"V1","V2","V3","V4","D1","D2","D3","D4"};
	vector<string> p2order{"V1","V2","V3","V4","D1","D2","D3","D4"};
	for (int i = 1; i < argc; ++i) {
		s = argv[i];
		if (A1) {
			try {
				p1abilities = addAbilities(s);
			}
			catch(Exception &e) {
				cout << e.getError() << endl;
				return 1;
			}
			A1 = false;
		} else if (A2) {
                        try {
                                p2abilities = addAbilities(s);
                        }
                        catch(Exception &e) {
				cout << e.getError() << endl;
				return 1;
			}
                        A2 = false;
		} else if (L1){
			try{
				p1order = addLinks(s);
			}
			catch(Exception &e) {
				cout << e.getError() << endl;
				return 1;
			}
			L1 = false;
		} else if (L2){
                        try{
                                p2order = addLinks(s);
                        }
                        catch(Exception &e) {
				cout << e.getError() << endl;
				return 1;
			}
                        L2 = false;
		} else if (s == "-ability1") {
			A1 = true;
		} else if (s == "-ability2") {
			A2 = true;
		} else if (s == "-link1") {
			L1 = true;	
		} else if (s == "-link2") {
			L2 = true;
		} else if (s == "-graphics") {
			graphics = true;
		} else{
			cerr << "\n*Invalid Argument*\n" << endl;
			return 0;
		}
	}
	if(A1 || A2 || L1 || L2) {
		cerr << "\n*Invalid Argument*\n" << endl;
		return 0;
	}
	string cmd;
	bool isFirst = true;
	Grid g(graphics);
	Xwindow *xw = nullptr;
	GraphicsDisplay *display = nullptr;
	if (graphics) {
		xw = new Xwindow;
		display = new GraphicsDisplay(8, xw);
		g.setObserver(display);
	}
	if (graphics) {
	xw->fillRectangle(0, 0, 500, 600, Xwindow::Blue);
	xw->fillRectangle(0, 595,500,10, Xwindow::Black);
	}
	g.init(8, p1order, p2order, p1abilities, p2abilities);
	cout << g;
       	while(cin){
		string cmd;
		cin >> cmd;
		if (graphics) {
		xw->fillRectangle(0, 605, 500, 95, Xwindow::White);
		}
		if ((cmd == "quit")||(cmd == "QUIT")) {
			break;
    		}
		if (cmd == "sequence"){
			string filename;
			cin >> filename;
			ifstream f {filename};
			string s;
			while (f >> s) {
				if (graphics) {
				xw->fillRectangle(0, 605, 500, 95, Xwindow::White);
				}
				if (s == "move"){
					char link;
					string dir;
					f >> link >> dir;
					try{
						g.move(link,dir);
						isFirst = true;
						cout << g;
					}
					catch(Exception &e){
						cout << e.getError() << endl;
						if (graphics) {
						xw->drawString(20, 620, e.getError());
						}
					}
				}else if (s == "abilities"){
					string myabilities = g.abilities();
					cout << myabilities << endl;
					if (graphics) {
					xw->drawString(20, 620, myabilities);
					}
				}else if (s == "board"){
					cout << g;
				}else if (s == "ability"){
					size_t which;

					f >> which;
					if (isFirst){
				try{
					g.ability(which, f);
					cout << g;
					isFirst = false;
				}
				catch(Exception &e){
					cout << e.getError() << endl;
					isFirst = true;
					if (graphics) {
					xw->drawString(20, 620, e.getError());
					}
				}
					}
					else{
						cerr << "\n*Cannot use more than one ability*\n" << endl;
						if (graphics) {
						xw->drawString(20, 620, "*Cannot use more than one ability*");
						}
					}	
				}
				else{
					cerr << "\n*Enter a valid Command*\n" << endl;
					if (graphics) {
					xw->drawString(20, 620, "*Enter a valid Command*");
					}
				}
				f.clear();
			}
		}else if (cmd == "move"){
			char link;
			string dir;
			if(cin >> link){ 
			if (cin >> dir){
			try{
				g.move(link,dir);
				isFirst = true;
				cout << g;
			}
			catch(Exception &e){
				cout << e.getError() << endl;
				if (graphics) {
				xw->drawString(20, 620, e.getError());
				}
			}
			}else {
				cerr << "\n*Invalid Input*\n" << endl;
				if (graphics) {
				xw->drawString(25, 620, "*Invalid Input*");
				}
			}
			}
		}else if (cmd == "abilities"){
			string myabilities = g.abilities();
			cout << myabilities << endl;
			if (graphics) {
			xw->drawString(20, 620, myabilities);
			}
		}else if (cmd == "board"){
			cout << g;
		}else if (cmd == "ability"){
			size_t which;
			cin >> which;
			if (isFirst){
				try{
					g.ability(which, cin);
					cout << g;
					isFirst = false;
				}
				catch(Exception &e){
					cout << e.getError() << endl;
					isFirst = true;
					if (graphics) {
					xw->drawString(20, 620, e.getError());
					}
				}
			}else{
				cerr << "\n*Cannot use more than one ability*\n" << endl;
				if (graphics) {
				xw->drawString(20, 620, "*Cannot use more than one ability*");
				}
			}
		}else {
			cerr << "\n*Enter a valid Command*\n" << endl;
			if (graphics) {
			xw->drawString(20, 620, "*Enter a valid Command*");
			}
		}
		cin.clear();
		if (g.whoWon() == 1) {
			cout << "Player 1 Won!" << endl;
			if (graphics) {
			xw->drawString(20, 620,"Player 1 Won!");
			}
			break;
		} else if (g.whoWon() == 2) {
			cout << "Player 2 Won!" << endl;
			if (graphics) {
			xw->drawString(20, 620,"Player 2 Won!");
			}
			break;
		}
		
	}
}

