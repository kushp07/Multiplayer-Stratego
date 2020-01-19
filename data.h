#ifndef DATA_H
#define DATA_H
#include "link.h"
#include <string>
#include "info.h"

class Data: public Link {
	public:
		Data(size_t row, size_t col, size_t player, size_t strength, char name, bool isHidden = true, bool switched = false, bool boosted = false );
		CellInfo getInfo() const override;
		void incstrength() override;
		void reveal() override;
		void setswitched(bool b) override;
		void setboosted(bool b) override;
};

#endif
