#ifndef __POSITION__H__
#define __POSITION__H__

#include "comm.h"

class Speed
{
	public:
		Speed(uint32_t x_speed, uint32_t y_speed):x_speed(x_speed), y_speed(y_speed){}

		~Speed(){}

		void set(uint32_t x, uint32_t y);

		uint32_t get_x_speed();

		uint32_t get_y_speed();
	private:
		uint32_t x_speed;  // m / s
		uint32_t y_speed; // m/s
};

class Position
{
	public:
		Position(uint32_t x, uint32_t y, bool is_down): x(x), y(y), is_down(is_down){
		}

		//Position(const Position& other){}          // copy construct function

		//Position operator=(const Position& other){}  // assign overload function
		
		~Position(){
		}

		uint32_t get_x() const;

		uint32_t get_y() const;

		bool set_x(uint32_t x);

		bool set_y(uint32_t	x);

		bool is_corner();

		// tell the ball whether is outside.
		bool is_outside();

		void recover_outside();

		/* if up = true, tell wheather the goal is in the up gate.
		   else tell wheather the goal is in the down gate.
		*/
		bool is_goal();

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
		bool is_down;
};


#endif
