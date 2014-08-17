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

void RealStatus::ComputeStatus()
{
	uint32_t len = player->size();
	// compute the distance_boy
	for(uint32_t i = 0; i < len -1; i++){
		for(uint32_t j = i + 1; j < len; j++){
			si.distance_boy[i][j][0] = (*player)[j].position.get_x() 
										- (*player)[i].position.get_x(); 
			si.distance_boy[i][j][1] = (*player)[j].position.get_y() 
										- (*player)[i].position.get_y(); 
			si.distance_boy[j][i][0] = -si.distance_boy[j][i][0];
			si.distance_boy[j][i][1] = -si.distance_boy[j][i][1];
		}
	}
	for(uint32_t i = 0; i < len; i++){
		si.distance_boy[20][i][0] = (*player)[i].position.get_x()
									- (*player)[20].position.get_x();
		si.distance_boy[20][i][1] = (*player)[i].position.get_y()
									- (*player)[20].position.get_y();
		si.distance_boy[i][20][0] = -si.distance_boy[20][i][0];
		si.distance_boy[i][20][1] = -si.distance_boy[20][i][1];

		si.distance_boy[21][i][0] = (*player)[i].position.get_x()
									- (*player)[21].position.get_x();
		si.distance_boy[21][i][1] = (*player)[i].position.get_y()
									- (*player)[21].position.get_y();
		si.distance_boy[i][21][0] = -si.distance_boy[21][i][0];
		si.distance_boy[i][21][1] = -si.distance_boy[21][i][1];
	}

	si.distance_boy[20][21][0] = (*player)[21].position.get_x()
								- (*player)[20].position.get_x();
	si.distance_boy[20][21][1] = (*player)[21].position.get_y()
								- (*player)[20].position.get_y();
	si.distance_boy[21][20][0] = -si.distance_boy[20][21][0];
	si.distance_boy[21][20][1] = -si.distance_boy[20][21][1];

	// compute the freedom_boy
	for(uint32_t i = 0; i < 10; i++){
		si.freedom_boy[i]	=	0;
		si.freedom_boy[i + 10]	=	0;
		for(uint32_t j = 10; j < 20; j++){
				if(	(abs(si.distance_boy[i][j][0]) <= FREE_DIS) ||
					(abs(si.distance_boy[i][j][1]) <= FREE_DIS) ){
					si.freedom_boy[i]++;
					si.freedom_boy[j]++;
				}
			}	
		}
		if(	(abs(si.distance_boy[i][21][0]) <= FREE_DIS) ||
			(abs(si.distance_boy[i][21][1]) <= FREE_DIS) ){
			si.freedom_boy[i]++;
			si.freedom_boy[21]++;
		}
		if(	(abs(si.distance_boy[i + 10][20][0]) <= FREE_DIS) ||
			(abs(si.distance_boy[i + 10][20][1]) <= FREE_DIS) ){
			si.freedom_boy[i + 10]++;
			si.freedom_boy[20]++;
		}
	}

	// compute the distance_gate
	for(uint32_t i = 0; i < 10; i++){
			si.distance_gate[i][0] = 	
	}
	
}

/*
	compute next second's status
	the func is the most important function, it tells you what will happen 
	in the next second by the position information of players and ball. so 
	how to implement the func is the core thing
*/
void RealStatus::NextStatus()
{				
	ComputeStatus(); // compute the StatusInfo	

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
