#include "RealStatus.h"

uint32_t BallStatus::NextStatus()
{	
	if(ball->position.is_outside()){
		ball->position.recover_outside();
		ball->speed.set(0,0);
		return CORNER_STATUS;   // notify corner
	}
	
	if(BallControl){	
		assert(kicked.valid);
		ball->speed.set(kicked.x_speed, kicked.y_speed);
	}
	else{
		ball->position.move(ball->speed);
		weaken(ball->speed);
	}
	return 0;
}

void BallStatus::weaken(Speed& sp)
{
	uint32_t x = sp.get_x_speed();
	uint32_t y = sp.get_y_speed();

	if(x > 0)
		x = x > AIR_RESISTANCE? x - AIR_RESISTANCE : 0;
	else
		x = x < -AIR_RESISTANCE? x + AIR_RESISTANCE : 0;

	if(y > 0)
		y = y > AIR_RESISTANCE? y - AIR_RESISTANCE : 0;
	else
		y = y < -AIR_RESISTANCE? y + AIR_RESISTANCE : 0;

	sp.set(x, y);
}

// sp is player/keeper status, sb is ball status
void SmartSelect(Status& sp, Status& sb, bool catch_ball = false) 
{
	
}

void PlayerStatus::NextStatus()
{
	if(catch_ball){
		
		return;
	}
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

	ball->NextStatus();  // must be later than player and keeper
}
