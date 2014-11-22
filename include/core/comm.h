#ifndef __COMM__H
#define __COMM__H

#include<stdint.h>

// const value set fot whole project, there should be all up alpha.

// const value
const int32_t	FIELD_WIDTH = 68;
const int32_t	FIELD_LENGTH = 106;
const int32_t	GATE_WIDTH = 7; // real value is 7.35m
const int32_t	GATE_LENGTH = 0;
const int32_t	GATE_HIGH = 2; // real value is 2.44m
const int32_t	PENALTY_WIDTH = 40; 
const int32_t	PENALTY_LENGTH = 16;
const int32_t	ON_BOUNDARY = -1; 
const int32_t	AIR_RESISTANCE = 0; // m/s
const int32_t	NUM_PLAYERS = 20;  // on the field , do not contain the subtution
const int32_t	NUM_KEEPERS = 2;
const int32_t	NUM_BOYS = 22;
const int32_t	NUM_POS = 20;   // the num of pos who boy can play: ST , AMC ...
const int32_t	FREE_DIS = 3;	// the value declare the area of free(FREE_DIS^2)
const int32_t 	STEAL_DIS = 3;	// the value declare the area of steal(STEAL_DIS^2)
const int32_t 	GET_DIS = 3;	// the value declare the area of get the free ball(GET_DIS^2)
const int32_t 	ATR_MAX_LEN = 200;
const int32_t	NUM_ATR = 41;  // update in the time
const int32_t	MIN_INT = (-1<<31);
const int32_t	MAX_INT	= -(MIN_INT + 1);
const int32_t	STEP_LEN = 3; // player move len per step by the max speed
const int32_t	MAX_ATR = 20;  // max atr value
// Status
const int32_t	OVER_STATUS = 0xa0;
const int32_t	CORNER_STATUS = 0xa1;
const int32_t	FREE_STATUS = 0xa2;
const int32_t	OUT_STATUS = 0xa3;
const int32_t	GOAL_STATUS = 0xa4;
const int32_t	CON_STATUS = 0xa5;
// Choose
const int32_t 	SHOOT_CHOOSE = 0xb0;
const int32_t 	SIEGE_CHOOSE = 0xb1;
const int32_t 	PASS_CHOOSE = 0xb2;
const int32_t 	DRI_CHOOSE = 0xb3;
// Detail for Choose
const int32_t	PASS_FORWARD = 0xc0;
const int32_t	PASS_BACK = 0xc1;

//ERROR
const int32_t MISS_INPUT = 0xe0;
const int32_t OPEN_FAILED = 0xe1;

#endif
