#ifndef LINK_H
#define LINK_H
#include <string>
#include "info.h"
class CellInfo;
using namespace std;
class Link {
	protected:
	 size_t row;
	 size_t col;
	 size_t player;
	 size_t strength;
	 char name;
	 bool isHidden;
	 bool switched;
	 bool boosted;
	public:
	//	size_t getplayer();
	//	char getname();
	//	size_t getrow();
	//	size_t  getcol();
	//	size_t getstrength();

		void setrow(size_t n);
		void setcol(size_t n);
		virtual void incstrength() = 0;
		virtual void reveal() = 0;
		virtual ~Link();
		Link(size_t row, size_t col, size_t player, size_t strength, char name, bool isHidden = true, bool switched = false, bool boosted = false);
		virtual CellInfo getInfo() const = 0;
		virtual void setswitched(bool b) = 0;
		virtual void setboosted(bool b) = 0;
};

#endif

