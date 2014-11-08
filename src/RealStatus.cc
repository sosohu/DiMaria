#include "RealStatus.h"

void Status::setPosition(uint32_t x, uint32_t y){
	position.set_x(x);
	position.set_y(y);
}

void Status::setPositionMove(Speed &sp){
	position.move(sp);
}

void Status::setPositionRecover_Outside(){
	position.recover_outside();
}

void Status::setSpeed(uint32_t x, uint32_t y){
	speed.set(x, y);
}

Position Status::getPosition(){
	return position;
}

uint32_t Status::getPositionX(){
	return position.get_x();
}

uint32_t Status::getPositionY(){
	return position.get_y();
}

bool Status::getPositionIs_outside(){
	return position.is_outside();
}

bool Status::getPositionIs_corner(){
	return position.is_corner();
}

bool Status::getPositionIs_goal(){
	return position.is_goal();
}

Speed Status::getSpeed(){
	return speed;
}

// ball fly by the speed
uint32_t BallStatus::NextStatus()
{	
	
	ball.setPositionMove(ball->speed);
	weaken(ball.speed);

	if(ball.getPositionIs_goal()){
		return GOAL_STATUS;
	}

	if(ball.getPositionIs_corner()){
		return CORNER_STATUS;
	}

	if(ball.getPositionIs_outside()){
		ball.setPositionRecover_Outside();
		ball.setSpeed(0,0);
		return CORNER_STATUS;   // notify corner
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

Ball getBall(){
	return ball;
}

void PlayerStatus::NextStatus()
{
	//default
}

Player PlayerStatus::getPlayer(){
	return player;
}

Phy_Atr PlayerStatus::getPlayerPhy_Atr(){
	return player.getPhy_Atr();
}

Men_Atr PlayerStatus::getPlayerMen_Atr(){
	return player.getMen_Atr();
}

Tec_Atr PlayerStatus::getPlayerTec_Atr(){
	return player.getTec_Atr();
}

Kee_Atr PlayerStatus::getPlayerKee_Atr(){
	return player.getKee_Atr();
}

/*
void KeeperStatus::NextStatus()
{
	//default
}

Player KeeperStatus::getPlayer(){
	return player;
}
*/


void RealStatus::ComputeStatus()
{
	uint32_t len = player.size();
	// compute the distance_boy
	// for player to player
	for(uint32_t i = 0; i < len -1; i++){
		for(uint32_t j = i + 1; j < len; j++){
			si.distance_boy[i][j][0] = player[j].getPositionX() 
										- player[i].getPositionX(); 
			si.distance_boy[i][j][1] = player[j].getPositionY() 
										- player[i].getPositionY(); 
			si.distance_boy[j][i][0] = -si.distance_boy[j][i][0];
			si.distance_boy[j][i][1] = -si.distance_boy[j][i][1];
		}
	}
	// for keeper to palyer
	for(uint32_t i = 0; i < len; i++){
		si.distance_boy[20][i][0] = player[i].getPositionX()
									- player[20].getPositionX();
		si.distance_boy[20][i][1] = player[i].getPositionY()
									- player[20].getPositionY();
		si.distance_boy[i][20][0] = -si.distance_boy[20][i][0];
		si.distance_boy[i][20][1] = -si.distance_boy[20][i][1];

		si.distance_boy[21][i][0] = player[i].getPositionX()
									- player[21].getPositionX();
		si.distance_boy[21][i][1] = player[i].getPositionY()
									- player[21].getPositionY();
		si.distance_boy[i][21][0] = -si.distance_boy[21][i][0];
		si.distance_boy[i][21][1] = -si.distance_boy[21][i][1];
	}
	// for keeper to keeper
	si.distance_boy[20][21][0] = player[21].getPositionX()
								- player[20].getPositionX();
	si.distance_boy[20][21][1] = player[21].getPositionY()
								- player[20].getPositionY();
	si.distance_boy[21][20][0] = -si.distance_boy[20][21][0];
	si.distance_boy[21][20][1] = -si.distance_boy[20][21][1];

	// compute the freedom_boy
	for(uint32_t i = 0; i < 10; i++){
		si.freedom_boy[i]	=	0;
		si.freedom_boy[i + 10]	=	0;
		// player to player
		for(uint32_t j = 10; j < 20; j++){
				if(	(abs(si.distance_boy[i][j][0]) <= FREE_DIS) ||
					(abs(si.distance_boy[i][j][1]) <= FREE_DIS) ){
					si.freedom_boy[i]++;
					si.freedom_boy[j]++;
				}
			}	
		}
		// player to keeper
		if(	(abs(si.distance_boy[i][21][0]) <= FREE_DIS) ||
			(abs(si.distance_boy[i][21][1]) <= FREE_DIS) ){
			si.freedom_boy[i]++;
			si.freedom_boy[21]++;
		}
		// player to keeper
		if(	(abs(si.distance_boy[i + 10][20][0]) <= FREE_DIS) ||
			(abs(si.distance_boy[i + 10][20][1]) <= FREE_DIS) ){
			si.freedom_boy[i + 10]++;
			si.freedom_boy[20]++;
		}
	}

	// compute the distance to the offside 's gate
	// for up side
	for(uint32_t i = 0; i < 10; i++){
		si.distance_gate[i][0] = FIELD_WIDTH/2 - player[i].getPositionX();	
		si.distance_gate[i][1] = player[i].getPositionY();	
	}
	si.distance_gate[20][0] = FIELD_WIDTH/2 - player[20].getPositionX();
	si.distance_gate[20][1] = player[20].getPositiony();	
	// for down side
	for(uint32_t i = 10; i < 20; i++){
		si.distance_gate[i][0] = FIELD_WIDTH/2 - player[i].getPositionX();	
		si.distance_gate[i][1] = FIELD_LENGTH - player[i].getPositionY();	
	}
	si.distance_gate[21][0] = FIELD_WIDTH/2 - player[21].getPositionX();
	si.distance_gate[21][1] = FIELD_LENGTH - player[21].getPositionY();	
	// compute the distance to the ball
	int ball_x = ball.getPositionX();
	int ball_y = ball.getPositionY();
	for(uint32_t i = 0; i < NUM_BOYS; i++){
		si.distance_ball[i][0] = ball_x - player[i].getPositionX();
		si.distance_ball[i][1] = ball_y - player[i].getPositionY();
	}

	// compute wheather the ball is controled and who control it
	BallControl = false;
	for(uint32_t i = 0; i< NUM_BOYS; i++){
		if(si.distance_ball[i][0] == 0 && si.distance_ball[i][1] == 0){
			BallControl = true;
			catch_boy = i;
			break;
		}
	}
}

/*
	Compute next second's status
	The func is the most important function, it tells you what will happen 
	in the next second by the position information of players and ball. so 
	how to implement the func is the core thing

	At the first vesion, we simply the process
	(1) the player catch the ball,
		he will make the decision with three ways: shoot , pass and siege
	the shoot is most simple, he shoots the ball to the offside's gate
	the pass is most complex, he can pass forward , pass back
	the siege is easy, he tries to make the ball get out of the field. 
	the dribbling is a little complex, he will carry the ball to the gate

	(2)	the player does not catch the ball but he is the nearest one of the ball.
		if the ball is catched by his teammate, he will do nothing, otherwise
	he will try to steal the ball from the offside.

	(3)	others
		do nothing, just stand on his position.			
*/
uint32_t RealStatus::NextStatus()
{				
	ComputeStatus(); // compute the StatusInfo	
	if(BallControl){
		// for catch boy
		SmartSelect(catch_boy);
		// for steal boy
		SmartDefend(catch_boy);
		return CON_STATUS;
	}else{
		uint32_t ret = ball.NextStatus();
		switch(ret){
			case CORNER_STATUS: status_comment = "We are the corner."; break;
			case OUT_STATUS: status_comment = "The goal is outside."; break;
			case GOAL_STATUS: status_comment = "Goooooooooal!!!!!"; break;
			default:	;
		}
		//return ret;
		return OVER_STATUS; // version 0.0.1, only one round.
	}
}

// id is player/keeper's id who catch the ball
void RealStatus::SmartSelect(uint32_t id) 
{
	bool up = id < 10? true : false;
	if(id == 20)	up = true;
	int posx = player[id].getPositionX();
	int posy = player[id].getPositionY();
	// compute every reason the make the decision
	TacticsInfo &ti = up? ti_up : ti_down;
	int decision = 0; // 0 is shoot, 1 is siege , 2 is pass and 3 is dribbling
	if((up && posy > FIELD_LENGTH/2) || (!up && posy < FIELD_LENGTH/2)){
		// attack field
		if((ti.detail == 2 && abs(si.distance_gate[id][1]) < FIELD_LENGTH/3)
			|| (abs(si.distance_gate[id][0]) < FIELD_WIDTH/4 && abs(si.distance_gate[id][1]) < FIELD_LENGTH / 4 )){ 
			// shoot more
			decision = 0;	
		}else{
			if(ti.detail == 4)
				decision = 3
			else
				decision = 2;
		}
	}else{
		// defend field
		if(ti.total == 1 && abs(si.distance_gate[id][1] < FIELD_LENGTH/3)){
			decision = 1;
		}else{
			if(ti.detail == 4)
				decision = 3
			else
				decision = 2;
		}
	}
	// if shoot
	if(decision == 0)
	{
		int strength = player[id].getPlayerPhy_Atr().strength;
		int speed = strength; // 1 ~ 20 m/s
		ball.setSpeed(distance_gate[id][0] * speed / distance_gate[id][1], speed);
		BallControl = false;
		status_comment = "He is shooting !!!";
		return;
	}
	// if siege
	if(decision == 1)
	{
		outside = true;
		int x = posx < FIELD_WIDTH/2 ? 0 : FIELD_WIDTH;
		ball.setPositionX(x);
		ball.setPositionY(posy);
		BallControl = false;
		status_comment = "He is siegeing ...";
		return;
	}
	// if pass
	if(decision == 2)
	{
		// compute every reason to make decision
		int pass_decision = 0; // 0 is pass forward, 1 is pass back
		if(ti.total == 1)	pass_decision = 1;
		// if pass forward
		if(pass_decision == 0)
		{
			int start = up ? 0 : 10;
			int index = -1 , count = 11;
			for(uint32_t i = start; i < start + 10; i++){
				if(i != id){ 
					if(start == 10 && player[i].getPositionY() > posy){
						if(si.around_boys[i] < count){
							count = si.around_boys[i];
							index = i;
						}
					}
					if(start == 0 && player[i].getpositionY() < posy){
						if(si.around_boys[i] < count){
							count = si.around_boys[i];
							index = i;
						}
					}
				}
			}
			int strength = player[id].getPlayerPhy_Atr().strength;
			int speed = strength; // 1 ~ 20 m/s
			ball.setSpeed( distance_boy[id][index][0] * speed 
									/ distance_boy[id][index][1], speed);
			BallControl = false;
			status_comment = "He is passing forward !";
			return;
		}
		// if pass back
		if(pass_decision == 1)
		{
			int start = up ? 0 : 10;
			int index = -1 , count = 11;
			for(uint32_t i = start; i < start + 10; i++){
				if(i != id){ 
					if(start == 10 && player[i].getPositionY() < posy){
						if(si.around_boys[i] < count){
							count = si.around_boys[i];
							index = i;
						}
					}
					if(start == 0 && player[i].getPositionY() > posy){
						if(si.around_boys[i] < count){
							count = si.around_boys[i];
							index = i;
						}
					}
				}
			}
			int strength = player[id].getPlayerPhy_Atr().strength;
			int speed = strength; // 1 ~ 20 m/s
			ball.setSpeed( distance_boy[id][index][0] * speed 
									/ distance_boy[id][index][1], speed);
			BallControl = false;
			status_comment = "He is passing back .";
			return;
		}
		if(decision == 3){
			// will construct
			status_comment = "He is getting break !!";
			return;
		}
	}
}

//	
void RealStatus::SmartDefend(uint32_t id){
	int start = id < 10? 10 : 0;
	if(id == 20)	start = 10;
	int min = FIELD_LENGTH, index, cur;
	for(uint32_t i = start; i < start + 10; i++){
		if((cur = sqrt(si.distance_boy[i][id][0]*si.distance_boy[i][id][0]
				+ si.distance_boy[i][id][1]*si.distance_boy[i][id][1])) < min){
			min = cur;
			index = i;
		}
	}
	if(min < STEAL_DIS){
		// steal success or not
		bool success = player[index].getPlayerTec_Atr.tracking > player[id].getPlayerTec_Atr.dribbling? true : false;
		if(success){
			ball.setSpeed(0,0);
			catch_boy = index;
			BallControl = true;
		}
	}
}

void RealStatus::SmartAttack(uint32_t id){
	//default
}

// when the goal, notify.
void RealStatus::NotifyGoal(){
	//default
}

// reset the status after the goal.
void RealStatus::ResetStatus(bool up = true){
	// reset player
	for(uint32_t i = 0; i < NUM_BOYS; i++){
		player[i].setPosition(init_position[i].x, init_position[i].y);
		player[i].setSpeed(0, 0);
	}
	// reset ball
	ball.setPosition(init_ball.x, init_ball.y);

	// reset si
	ComputeStatus();

	BallControl = true;
	catch_boy = up? 9 : 19;
	outside = false;
	corner = false;
	status_comment = "";
}

// start corner.
void RealStatus::StartCorner(){
	
}

// start freeball.
void RealStatus::StartFree(){
	//default.
}

// start outside
void RealStatus::StartOutside(){

}

// compute the status each times and perpare for the Status.
void RealStatus::ComputeStatus(){

}

// return the comment of match by the Status.
string RealStatus::TextComment(){
	return status_comment;
}
