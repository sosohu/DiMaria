#ifndef __POSITION__H__
#define __POSITION__H__

#include "comm.h"

class Speed
{
	public:
		Speed(){}

		~Speed(){}

		void set();

		uint32_t get_x_speed();

		uint32_t get_y_speed();
	private:
		uint32_t x_speed;  // m / s
		uint32_t y_speed; // m/s
};


class Position
{
	public:
		Position(uint32_t x, uint32_t y, bool down): x(x), y(y), is_down(down){
		}

		//Position(const Position& other){}          // copy construct function

		//Position operator=(const Position& other){}  // assign overload function
		
		~Position(){
		}

		uint32_t get_x() const;

		uint32_t get_y() const;

		bool set_x(uint32_t x);

		bool set_y(uint32_t	x);

		bool is_outside();

		void recover_outside();

		int	left(Position& rhs );

		int	right(Position& rhs);

		int	up(Position& rhs);

		int	down(Position& rhs);

		void move(Speed& sp);

		
		bool in_penalty_area(); // up == true , the player is owned to up ,the penalty area is in down
		// penalty area size is 40*16

		uint32_t distance(const Position& other);
		// compute the distance to the other
		

	private:
		uint32_t x; // width offside to the 0 dot
		uint32_t y; // length offside to the 0 dot
		bool 	is_down; // down == ture , the player is belonged to the down, others, up
};


#endif
