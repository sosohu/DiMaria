#include "mmath.h"
#include <cmath>

int32_t Distance(int32_t x, int32_t y){
	return sqrt(x*x + y*y);
}

int32_t GenSpeed(int32_t strength){
	return strength / 2 + 1;
}
