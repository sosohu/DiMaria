#include "Position.h"
#include <math.h>
#include <stddef.h>

void Speed::set(uint32_t x, uint32_t y)
{
		x_speed = x;
		y_speed = y;
}

uint32_t Speed::get_x_speed()
{
		return	x_speed;
}

uint32_t Speed::get_y_speed()
{
		return	y_speed;
}

uint32_t Position::get_x() const
{
	return x;
}

uint32_t Position::get_y() const
{
	return y;
}

bool Position::set_x(uint32_t x_val)
{
	x = x_val;
	return true;
}

bool Position::set_y(uint32_t y_val)
{
	y = y_val;
	return true;
}

bool Position::is_corner()
{
	if(y < 0 || y > FIELD_LENGTH)
		return true;
	return false;	
}

bool Position::is_outside()
{
	if(x < 0 || x > FIELD_WIDTH)
		return true;
	return false;
}

void Position::recover_outside()
{
	if(y < 0){
		if (x < FIELD_WIDTH/2){
			x = 0;
			y = 0;
	}
		else{
			x = FIELD_WIDTH;
			y = 0;
		}
		return;
	}

	if(y > FIELD_LENGTH){
		if (x < FIELD_WIDTH/2){
			x = 0;
			y = FIELD_LENGTH;
		}
		else{
			x = FIELD_WIDTH;
			y = FIELD_LENGTH;
		}
		return;
	}

	if(x < 0)
		x = 0;
	else
		x = FIELD_WIDTH;

	return;
}

bool Position::is_goal()
{
	if(y < 0 && x > (FIELD_WIDTH - GATE_WIDTH)/2 && x < (FIELD_WIDTH + GATE_WIDTH)/2)
		return true;
	if(y > FIELD_LENGTH && x > (FIELD_WIDTH - GATE_WIDTH)/2 && x < (FIELD_WIDTH + GATE_WIDTH)/2)
		return true;
	return false;	
}

int Position::left(Position& rhs)
{
	if (x == 0)
		return ON_BOUNDARY;
	rhs.set_x(x - 1);
	return 0;
}

int	Position::right(Position& rhs)
{
	if (x == FIELD_WIDTH)
		return ON_BOUNDARY;
	rhs.set_x(x + 1);
	return 0;
}

int	Position::up(Position& rhs)
{
	if (y == FIELD_LENGTH)
		return ON_BOUNDARY;
	rhs.set_y(y + 1);
	return 0;
}

int Position::down(Position& rhs)
{
	if (y == 0)
		return ON_BOUNDARY;
	rhs.set_y(y - 1);
	return 0;
}

void Position::move(Speed& sp)
{
	x = x + sp.get_x_speed();
	y = y + sp.get_y_speed();
}

bool Position::in_penalty_area()
{				// up == true , the player is owned to up ,the penalty area is in down
	if (is_down) {
		if (x >= 14 && x <= 54 && y >= 0 && y <= 16) {
			return true;
		}
	} else {
		if (x >= 14 && x <= 54 && y >= 90 && y <= 106) {
			return true;
		}
	}
}				// penalty area size is 40*16

uint32_t Position::distance(const Position & other)
{
	return sqrt((x - other.get_x()) * (x - other.get_x()) +
		    (y - other.get_y()) * (y - other.get_y()));
}				// compute the distance to the other
