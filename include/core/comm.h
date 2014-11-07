#ifndef __COMM__H
#define __COMM__H

#include<stdint.h>



const uint32_t	FIELD_WIDTH = 68;
const uint32_t	FIELD_LENGTH = 106;
const uint32_t	ON_BOUNDARY = -1; 
const uint32_t	AIR_RESISTANCE 50; // m/s
const uint32_t	NUM_PLAYERS = 20;  // on the field , do not contain the subtution
const uint32_t	NUM_KEEPERS = 2;
const uint32_t	NUM_BOYS = 22;
const uint32_t	NUM_POS = 20;   // the num of pos who boy can play: ST , AMC ...
const uint32_t	FREE_DIS = 3;	// the value declare the area of free(FREE_DIS^2)


#endif
