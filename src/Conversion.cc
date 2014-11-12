#include "Conversion.h"
#include <sstream> 

std::string Int2Str(int32_t data){
	std::stringstream ss;
	ss<<data; 
	return ss.str();
}

int32_t Str2Int(std::string str){
	char *end;
	int32_t ret = static_cast<int32_t>(strtol(str.c_str(), &end, 10));
	return ret;
}
