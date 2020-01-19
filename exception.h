#ifndef EXC_H
#define EXC_H

#include <stdexcept>

class Exception{
	std::string error;
	public:
		Exception(std::string error);
		std::string getError();
};


#endif
