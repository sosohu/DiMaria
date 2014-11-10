#ifndef __BALL__H__
#define __BALL__H__

#include "comm.h"
#include "Position.h"

typedef struct
{
	uint32_t color;
	uint32_t size; // r
} Bal_Atr;

class Ball
{
	public:
		Ball(Bal_Atr bal_atr):bal_atr(bal_atr){
		}

		~Ball(){
		}

	private:
		Bal_Atr bal_atr;
};


#endif
