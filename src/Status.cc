#include "Status.h"
#include "Print.h"

void Status::setPosition(int32_t x, int32_t y){
	position.set_x(x);
	position.set_y(y);
}

void Status::setPositionMove(Speed sp){
	position.move(sp);
}

void Status::setPositionRecover_Outside(){
	position.recover_outside();
}

void Status::setSpeed(int32_t x, int32_t y){
	speed.set(x, y);
}

Position Status::getPosition(){
	return position;
}

int32_t Status::getPositionX(){
	return position.get_x();
}

int32_t Status::getPositionY(){
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
int32_t BallStatus::NextStatus()
{	
	//default
}

void BallStatus::weaken()
{
	Speed sp = getSpeed();
	int32_t x = sp.get_x_speed();
	int32_t y = sp.get_y_speed();
	PRINT_MSG("%d, %d", x, y);

	if(x > 0)
		x = x > AIR_RESISTANCE? x - AIR_RESISTANCE : 0;
	else
		x = x < -AIR_RESISTANCE? x + AIR_RESISTANCE : 0;

	if(y > 0)
		y = y > AIR_RESISTANCE? y - AIR_RESISTANCE : 0;
	else
		y = y < -AIR_RESISTANCE? y + AIR_RESISTANCE : 0;

	setSpeed(x, y);
}

Ball BallStatus::getBall(){
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
