#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include "ability.h"
#include "link.h"
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"

using namespace std;
class Player: public Subject<State> {
	int playerNumber;
	vector<Link*> downloaded;
	vector<Link*> owns;
	vector<char> abilities;
	vector<string> order;
	int downloadedviruses = 0;
	int downloadeddata = 0;
	public:
		vector<Link*> getowns();
		vector<Link*> getdownloaded();
		vector<char> getabilities();
		Player(vector<Link*> downloaded, vector<Link*> owns, vector<char> abilities, vector<string> order, int playerNumber);
		~Player();
		void downloadLink(Link *);
		PlayerInfo getInfo() const override;
		void removeability(int i);
		void addability(char c);
		vector<string> &getorder();

};

#endif
