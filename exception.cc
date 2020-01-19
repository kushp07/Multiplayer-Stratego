#include "exception.h"

using namespace std;

Exception::Exception(string error): error{error}{}
string Exception::getError(){
	return error;
}
