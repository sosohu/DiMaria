#ifndef __ENVIRONMENT__H__
#define __ENVIRONMENT__H__

#include "comm.h"
#include "Position.h"
#include "RealStatus.h"

// id is in up side ? yes return true otherwise return false
bool isUpSide(int32_t id);

// trans the scope to the up view
Scope tran2UpScope(Scope s);

// judge whether the position in the scope
// in return true, out return false
bool isInScope(Position p, Scope s);

// choose one from left, right, left-up, right-up
void randChooseUp(int32_t &x, int32_t &y, int32_t pace);


#endif
