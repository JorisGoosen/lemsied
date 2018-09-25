#include <string>
#include <algorithm>


struct exceptioneel
{
	exceptioneel(std::string str) : msg(str+"\n") {}

	const char * what() { return msg.c_str(); }
		
	std::string msg;
};
