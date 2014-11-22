#include "Environment.h"

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
