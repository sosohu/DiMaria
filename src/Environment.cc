#include "Environment.h"
#include <cstdlib>

bool isUpSide(int32_t id){
	if(id < 10 || id == 20)	return true;
	return false;
}

Scope tran2UpScope(Scope s){
	Scope ret;
	ret.x_start = s.x_start;
	ret.x_end = s.x_end;
	ret.x_start = FIELD_LENGTH - s.y_end;
	ret.y_end = FIELD_LENGTH - s.y_start;
	return ret;
}

bool isInScope(Position p, Scope s){
	if(p.get_x() >= s.x_start && p.get_x() <= s.x_end
		&& p.get_y() >= s.y_start && p.get_y() <= s.y_end){
		return true;
	}
	return false;
}

void randChooseUp(int32_t &x, int32_t &y, int32_t pace){
	srand((int)time(NULL));
	int32_t c = rand() % 4;
	int32_t speed = STEP_LEN*pace/MAX_ATR;
	switch(c){
	case 0: x = x - speed * 2 / 3; break;   // left
	case 1: x = x + speed * 2 / 3; break;   // right
	case 2: x = x - speed * 2 / 3; y = y + speed; break; // left-up
	case 3: x = x + speed * 2 / 3; y = y + speed; break; // right-up
	default: ;
	}
}
