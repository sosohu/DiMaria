#ifndef __POSITION__H__
#define __POSITION__H__

#include "comm.h"

typedef struct	Speed
{
	uint32_t x_speed;  // m / s
	uint32_t y_speed; // m/s
} Diraction;

class Position
{
	public:
		Position(uint32_t x, uint32_t y, bool down): x(x), y(y), down(down){
			
		}

		//Position(const Position& other){}          // copy construct function

		//Position operator=(const Position& other){}  // assign overload function
		
		~Position(){
		}

		uint32_t get_x(){
			return x;
		}

		uint32_t get_y(){
			return y;
		}

		Position left(){
			if(x == 0)	return NULL;
			return Position(x - 1, y);
		}

		Position right(){
			if(x == FIELD_WIDTH)	return NULL;
			return Position(x + 1, y);
		}

		Position up(){
			if(y == FIELD_LENGTH)	return NULL;
			return Position(x, y + 1);
		}

		Position down(){
			if(y == 0)	return NULL;
			return Position(x, y - 1);
		}

		
		bool in_penalty_area(){ // up == true , the player is owned to up ,the penalty area is in down
				if(down){
					if(x >= 14 && x <= 54 && y >= 0 && y <= 16){
						return true;
					}
				}
				else{
					if(x >= 14 && x <= 54 && y >= 90 && y <= 106){
						return true;
					}
				}
		}// penalty area size is 40*16

		uint32_t distance(const Position& other){
			return sqrt((x - other.get_x())*(x - other.get_x()) + (y - other.get_y())*(y - other.get_y()));
		}// compute the distance to the other
		

	private:
		uint32_t x; // width offside to the 0 dot
		uint32_t y; // length offside to the 0 dot
		bool 	down; // down == ture , the player is belonged to the down, others, up
};


#endif
