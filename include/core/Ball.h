#ifndef __BALL__H__
#define __BALL__H__

#include "comm.h"
#include "Position.h"

class Ball
{
	public:
		Ball(){
		}

		~Ball(){
		}

	private:
		Position pisiton;
		Speed	speed;
};


#endif
