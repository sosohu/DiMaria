#include "RealStatus.h"

uint32_t BallStatus::NextStatus()
{	
	if(ball->position.is_outside()){
		ball->position.recover_outside();
		return CONNER_STATUS;
	}
	
	if(BallControl){

	}
	else{
		ball->position.move(ball->speed);
	}
	return 0;
}

void PlayerStatus::NextStatus()
{

}

void KeeperStatus::NextStatus()
{

}

// the func is the most important function, it tells you what will happen 
// in the next second by the position information of players and ball. so 
// how to implement the func is the core thing
void RealStatus::NextStatus()
{				// next second's status
	std::vector<PlayerStatus>::iterator iter = player->begin();
	assert( NUM_PLAYERS == player->size());
	for(; iter != player->end(); iter++){
		*iter.NextStatus();
	}

	std::vector<KeeperStatus>::iterator iter = keeper->begin();
	assert( NUM_KEEPERS == keeper->size());
	for(; iter != keeper->end(); iter++){
		*iter.NextStatus();
	}

	ball->NextStatus();
}
