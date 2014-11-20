#ifndef __Conversion__H__
#define __Conversion__H__

#include "comm.h"
#include <string>

std::string Int2Str(int32_t data);

int32_t Str2Int(std::string str);

const char* Str2Chr(std::string str);


#endif
