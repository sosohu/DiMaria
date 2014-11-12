#ifndef __COMM__H
#define __COMM__H

#include<stdint.h>


// const value
const int32_t	FIELD_WIDTH = 68;
const int32_t	FIELD_LENGTH = 106;
const int32_t	GATE_WIDTH = 7; // real value is 7.35m
const int32_t	GATE_LENGTH = 0;
const int32_t	GATE_HIGH = 2; // real value is 2.44m
const int32_t	PENALTY_WIDTH = 40; 
const int32_t	PENALTY_LENGTH = 16;
const int32_t	ON_BOUNDARY = -1; 
const int32_t	AIR_RESISTANCE = 2; // m/s
const int32_t	NUM_PLAYERS = 20;  // on the field , do not contain the subtution
const int32_t	NUM_KEEPERS = 2;
const int32_t	NUM_BOYS = 22;
const int32_t	NUM_POS = 20;   // the num of pos who boy can play: ST , AMC ...
const int32_t	FREE_DIS = 3;	// the value declare the area of free(FREE_DIS^2)
const int32_t  STEAL_DIS = 3;	// the value declare the area of steal(STEAL_DIS^2)
const int32_t ATR_MAX_LEN = 200;
const int32_t NUM_ATR = 41;  // update in the time
// Status
const int32_t OVER_STATUS = 0xa0;
const int32_t CORNER_STATUS = 0xa1;
const int32_t FREE_STATUS = 0xa2;
const int32_t OUT_STATUS = 0xa3;
const int32_t GOAL_STATUS = 0xa4;
const int32_t CON_STATUS = 0xa5;

//ERROR
const int32_t MISS_INPUT = 0xe0;
const int32_t OPEN_FAILED = 0xe1;

#endif
