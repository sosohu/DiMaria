#include "RealStatus.h"
#include "Conversion.h"
#include "Print.h"
#include "Math.h"
#include "Environment.h"
#include <cmath>

void RealStatus::ComputeStatus()
{
	int32_t len = player.size();
	// compute the distance_boy
	// for player to player
	for(int32_t i = 0; i < len - 1; i++){
		for(int32_t j = i + 1; j < len; j++){
			si.distance_boy[i][j][0] = player[j].getPositionX() 
										- player[i].getPositionX(); 
			si.distance_boy[i][j][1] = player[j].getPositionY() 
										- player[i].getPositionY(); 
			si.distance_boy[j][i][0] = -si.distance_boy[i][j][0];
			si.distance_boy[j][i][1] = -si.distance_boy[i][j][1];
		}
	}
	// for keeper to palyer
	/*
	for(int32_t i = 0; i < len; i++){
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
	*/

	// compute the around_boys
	for(int32_t i = 0; i < 10; i++){
		si.around_boys[i]	=	0;
		si.around_boys[i + 10]	=	0;
		// player to player
		for(int32_t j = 10; j < 20; j++){
				if(	(std::abs(si.distance_boy[i][j][0]) <= FREE_DIS) ||
					(std::abs(si.distance_boy[i][j][1]) <= FREE_DIS) ){
					si.around_boys[i]++;
					si.around_boys[j]++;
				}
			}	
		// player to keeper
		if(	(std::abs(si.distance_boy[i][21][0]) <= FREE_DIS) ||
			(std::abs(si.distance_boy[i][21][1]) <= FREE_DIS) ){
			si.around_boys[i]++;
			si.around_boys[21]++;
		}
		// player to keeper
		if(	(std::abs(si.distance_boy[i + 10][20][0]) <= FREE_DIS) ||
			(std::abs(si.distance_boy[i + 10][20][1]) <= FREE_DIS) ){
			si.around_boys[i + 10]++;
			si.around_boys[20]++;
		}
	}

	// compute the distance to the offside 's gate
	// for up side
	for(int32_t i = 0; i < 10; i++){
		si.distance_gate[i][0] = FIELD_WIDTH/2 - player[i].getPositionX();	
		si.distance_gate[i][1] = player[i].getPositionY();	
	}
	si.distance_gate[20][0] = FIELD_WIDTH/2 - player[20].getPositionX();
	si.distance_gate[20][1] = player[20].getPositionY();	
	// for down side
	for(int32_t i = 10; i < 20; i++){
		si.distance_gate[i][0] = FIELD_WIDTH/2 - player[i].getPositionX();	
		si.distance_gate[i][1] = FIELD_LENGTH - player[i].getPositionY();	
	}
	si.distance_gate[21][0] = FIELD_WIDTH/2 - player[21].getPositionX();
	si.distance_gate[21][1] = FIELD_LENGTH - player[21].getPositionY();	
	// compute the distance to the ball
	int ball_x = ball.getPositionX();
	int ball_y = ball.getPositionY();
	for(int32_t i = 0; i < NUM_BOYS; i++){
		si.distance_ball[i][0] = ball_x - player[i].getPositionX();
		si.distance_ball[i][1] = ball_y - player[i].getPositionY();
	}

	// compute wheather the ball is controled and who control it
	BallControl = false;
	for(int32_t i = 0; i< NUM_BOYS; i++){
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
int32_t RealStatus::NextStatus()
{				
	ball.setPositionMove(ball.getSpeed());
	if(!BallControl){
		pass_t--;
		Modify(ball);
	}
	//ball.weaken();
	PRINT_MSG("ball position: %d %d",ball.getPositionX(), ball.getPositionY());
	PRINT_MSG("ball speed: %d %d",ball.getSpeed().get_x_speed(), ball.getSpeed().get_y_speed());
	ComputeStatus(); // compute the StatusInfo	
	if(BallControl){
		// for catch boy
		SmartCatch(catch_boy);
		// for forward boy
		SmartAttack(catch_boy);
		// for steal boy
		SmartDefend(catch_boy);
		return CON_STATUS;
	}else{
		int32_t ret = 0;
		//ball.setPositionMove(ball.getSpeed());
		//ball.weaken();

		if(ball.getPositionIs_goal()){
			ret = GOAL_STATUS;
		}
		else{
			if(ball.getPositionIs_corner()){
				ret = CORNER_STATUS;
			}else if(ball.getPositionIs_outside()){
				ball.setPositionRecover_Outside();
				ball.setSpeed(0,0);
				ret = CORNER_STATUS;   // notify corner
			}
		}

		switch(ret){
			case CORNER_STATUS: status_comment = "We are the corner."; break;
			case OUT_STATUS: status_comment = "The goal is outside."; break;
			case GOAL_STATUS: status_comment = "Goooooooooal!!!!!"; break;
			default: SmartDefend(catch_boy); 
					SmartAttack(catch_boy); 
					return CON_STATUS;
			//default: status_comment = "continue...";	return CON_STATUS;
		}
		//return ret;
		return OVER_STATUS; // version 0.0.1, only one round.
	}
}

int32_t RealStatus::SmartSelect(int32_t id){
	bool up = id < 10? true : false;
	if(id == 20)	up = true;
	int32_t posx = player[id].getPositionX();
	int32_t posy = player[id].getPositionY();
	// compute every reason the make the decision
	TacticsInfo &ti = up? ti_up : ti_down;
	int decision = 0; 
	if((up && posy > FIELD_LENGTH/2) || (!up && posy < FIELD_LENGTH/2)){
		// id is in attack field
		if((ti.detail == Shoot_More && std::abs(si.distance_gate[id][1]) < FIELD_LENGTH/3)
		|| (Distance(si.distance_gate[id][0],si.distance_gate[id][1]) < FIELD_LENGTH / 4)
		|| (getFreePlayerForward(id).empty() && player[id].getPlayer().getPlay_Pos() == ST)){ 
			// shoot more
			decision = SHOOT_CHOOSE;	
		}else{
			if(ti.detail == Break_More)
				decision = DRI_CHOOSE;
			else
				decision = PASS_CHOOSE;
		}
	}else{
		// id is in defend field
		if(ti.total == DEFEND && std::abs(si.distance_gate[id][1] < FIELD_LENGTH/3)){
			decision = PASS_CHOOSE;
		}else{
			if(ti.detail == Break_More)
				decision = DRI_CHOOSE;
			else
				decision = PASS_CHOOSE;
		}
	}
	return decision;
}

int32_t RealStatus::PassSelect(int32_t id){
	// compute every reason to make decision
	bool up = id < 10? true : false;
	TacticsInfo &ti = up? ti_up : ti_down;
	int32_t pass_decision = PASS_FORWARD; 
	if(ti.total == DEFEND || getFreePlayerForward(id).empty())	
		pass_decision = PASS_BACK;
	return pass_decision;
}

// id is player/keeper's id who catch the ball
void RealStatus::SmartCatch(int32_t id) 
{
	int32_t decision = SmartSelect(id);
	PRINT_MSG("decision: %d", decision);
	switch(decision){
		case SHOOT_CHOOSE:	MakeShoot(id);	break;
		case SIEGE_CHOOSE:	MakeSiege(id);	break;
		case PASS_CHOOSE:	MakePass(id);	break;
		case DRI_CHOOSE:	MakeDri(id);	break;
		default:; 
	}
}

// smart choose for the attack side player
void RealStatus::SmartDefend(int32_t id){
	int start = id < 10? 10 : 0;
	if(id == 20)	start = 10;
	int min = FIELD_LENGTH, index, cur;
	for(int32_t i = start; i < start + 10; i++){
		if((cur = sqrt(si.distance_boy[i][id][0]*si.distance_boy[i][id][0]
				+ si.distance_boy[i][id][1]*si.distance_boy[i][id][1])) < min){
			min = cur;
			index = i;
		}
	}
	if(min < STEAL_DIS){
		// steal success or not
		bool success = player[index].getPlayerTec_Atr().tracking > player[id].getPlayerTec_Atr().dribbling? true : false;
		if(success){
			ball.setSpeed(0,0);
			catch_boy = index;
			BallControl = true;
		}
	}
}

// smart choose for the attack side player
void RealStatus::SmartAttack(int32_t id){
	//default
	if(BallControl){
		// none
	}else{
		int32_t min = MAX_INT;
		int32_t tmp = 0;
		int32_t index = 0;
		bool up = isUpSide(id);
		int32_t start = up? 0 : 10;
		for(int32_t i = start; i < start + 10; i++){
			if((tmp = Distance(si.distance_ball[i][0], si.distance_ball[i][1])) < min){
				min = tmp;
				index = i;
			}
		}
		PRINT_MSG("the nearest id : %d, distance is %d", index, min);
		PRINT_MSG("id is %d, get_boy is %d", id, get_boy);
		if(min < GET_DIS && id != index && index == get_boy){
			PRINT_MSG("%d catch the ball", index);
			BallControl = true;
			catch_boy = index;
			ball.setSpeed(0, 0);
			player[index].setPosition(ball.getPositionX(), ball.getPositionY());
		}else{
			MoveForMeet(get_boy); // get_boy need to meet the ball
			// other attack run
			for(int32_t i = start; i < start + 10; i++){
				if(i != id && i != get_boy){
					MoveForward(i);
				}
			}
		}
	}
}

// when the goal, notify.
void RealStatus::NotifyGoal(){
	//default
}

// reset the status after the goal.
void RealStatus::ResetStatus(bool up){
	// reset player
	for(int32_t i = 0; i < NUM_BOYS; i++){
		player[i].setPosition(init_position[i].get_x(), init_position[i].get_y());
		player[i].setSpeed(0, 0);
	}
	// reset ball
	ball.setPosition(init_ball.get_x(), init_ball.get_y());

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

// return the comment of match by the Status.
std::string RealStatus::TextComment(){
	return status_comment;
}

BallStatus RealStatus::getBallStatus(){
	return ball;
}

void RealStatus::MakeShoot(int32_t id){
	int strength = player[id].getPlayerPhy_Atr().strength;
	int speed = strength; // 1 ~ 20 m/s
	assert(si.distance_gate[id][1] != 0);
	ball.setSpeed(si.distance_gate[id][0] * speed / si.distance_gate[id][1], speed);
	BallControl = false;
	status_comment = "He is shooting !!!";
}

void RealStatus::MakeSiege(int32_t id){
	outside = true;
	int posx = player[id].getPositionX();
	int posy = player[id].getPositionY();
	int x = posx < FIELD_WIDTH/2 ? 0 : FIELD_WIDTH;
	ball.setPosition(x, posy);
	BallControl = false;
	status_comment = "He is siegeing ...";
}

void RealStatus::MakePass(int32_t id){
	int32_t pass_decision = PassSelect(id);
	//PRINT_MSG("pass_decision: %d", pass_decision);
	// if pass forward
	if(pass_decision == PASS_FORWARD)
	{
		MakePassForward(id);
		return;
	}
	// if pass back
	if(pass_decision == PASS_BACK)
	{
		MakePassBack(id);
		return;
	}
}

void RealStatus::MakeDri(int32_t id){
	status_comment = "He is getting break !!"; // will construct
}

void RealStatus::MakePassForward(int32_t id){
	int posy = player[id].getPositionY();
	bool up = isUpSide(id);
	int32_t start = up ? 0 : 10;
	int32_t index = -1 , count = 11;
	for(int32_t i = start; i < start + 10; i++){
		if(i != id){ 
			if(start == 10 && player[i].getPositionY() > posy){
				if(si.around_boys[i] < count){
					count = si.around_boys[i];
					index = i;
				}
			}
			if(start == 0 && player[i].getPositionY() < posy){
				if(si.around_boys[i] < count){
					count = si.around_boys[i];
					index = i;
				}
			}
		}
	}
	int32_t strength = player[id].getPlayerPhy_Atr().strength;
	int32_t speed = GenSpeed(strength); // 1 ~ 20 m/s

	int32_t dis = Distance(si.distance_boy[id][index][0], 
							si.distance_boy[id][index][1]);
	PRINT_MSG("id %d, index %d", id, index);
	PRINT_MSG("id x %d, y %d", player[id].getPositionX(), player[id].getPositionY());
	PRINT_MSG("index x %d, y %d", player[index].getPositionX(), player[index].getPositionY());
	assert(dis != 0);
	int32_t speedx = si.distance_boy[id][index][0] * speed / dis;
	int32_t speedy = si.distance_boy[id][index][1] * speed / dis;
	ball.setSpeed( speedx, speedy);
	BallControl = false;
	get_boy = index;
	meet_x = player[index].getPositionX();
	meet_y = player[index].getPositionY();
	pass_t = dis / speed;
	//status_comment = "He is passing forward !";
	status_comment = Int2Str(id) + " is passing forward to " + 
					Int2Str(index) + " by the speed of " + 
					Int2Str(speed) + " !";
}

void RealStatus::MakePassBack(int32_t id){
	int posy = player[id].getPositionY();
	bool up = isUpSide(id);
	int32_t start = up ? 0 : 10;
	int32_t index = -1 , count = 11;
	for(int32_t i = start; i < start + 10; i++){
		if(i != id){ 
			if(!up  && player[i].getPositionY() < posy){
				if(si.around_boys[i] < count){
					count = si.around_boys[i];
					index = i;
				}
			}
			if(up && player[i].getPositionY() > posy){
				if(si.around_boys[i] < count){
					count = si.around_boys[i];
					index = i;
				}
			}
		}
	}
	int32_t strength = player[id].getPlayerPhy_Atr().strength;
	int32_t speed = GenSpeed(strength); // 1 ~ 20 m/s
	int32_t dis = Distance(si.distance_boy[id][index][0], 
							si.distance_boy[id][index][1]);
	assert(dis != 0);
	int32_t speedx = si.distance_boy[id][index][0] * speed / dis ;
	int32_t speedy = si.distance_boy[id][index][1] * speed / dis ;
	ball.setSpeed( speedx, speedy);
	BallControl = false;
	get_boy = index;
	meet_x = player[index].getPositionX();
	meet_y = player[index].getPositionY();
	pass_t = dis / speed;
	status_comment = Int2Str(id) + " is passing back to " + 
					Int2Str(index) + " by the speed of " + 
					Int2Str(speed) + " .";
}

void RealStatus::MoveForward(int32_t id){
	bool up = isUpSide(id);
	Scope s;
	if(up){
		for(int32_t i = 0; i < 10; i++){
			if(i != id && i != get_boy){
				s = scope_pos[player[i].getPlayer().getPlay_Pos()];
				s = tran2UpScope(s);
				// we assume that each player should be in its scope
				// and do not get out of its scope
				if(isInScope(player[i].getPosition(), s)){
					// in the scope
					// smartly move forward for the no-player zone

				}else{
					// out off the scope
					// stand and not move
					;
				}
			}
		}
	}else{

	}
}

void RealStatus::MoveForMeet(int32_t id){
	int32_t posx = player[id].getPositionX();
	int32_t posy = player[id].getPositionY();
	if(posx != meet_x || posy != meet_y){
		int32_t disx = meet_x - posx;
		int32_t disy = meet_y - posy;
		int32_t dis = Distance(disx, disy);
		assert(dis != 0);
		int32_t strength = player[id].getPlayerPhy_Atr().strength;
		int32_t speed = GenSpeed(strength);
		posx = posx + disx * speed / dis;
		posy = posy + disy * speed / dis;
		player[id].setPosition(posx, posy);
	}
}

std::vector<int32_t> RealStatus::getFreePlayer(int32_t id){
	std::vector<int32_t> data;
	std::vector<int32_t> fdata = getFreePlayerForward(id);
	std::vector<int32_t> bdata = getFreePlayerBack(id);
	std::vector<int32_t> pdata = getFreePlayerPara(id);
	data.insert(data.end(), fdata.begin(), fdata.end());
	data.insert(data.end(), bdata.begin(), bdata.end());
	data.insert(data.end(), pdata.begin(), pdata.end());
	return data;
}

std::vector<int32_t> RealStatus::getFreePlayerForward(int32_t id){
	bool up = isUpSide(id);
	int32_t start = up? 0 : 10;
	int32_t posy = player[id].getPositionY();
	std::vector<int32_t> data;
	for(int32_t i = start; i < start + 10; i++){
		if(up && player[i].getPositionY() < posy){
			data.push_back(i);
		}
		if(!up && player[i].getPositionY() > posy){
			data.push_back(i);
		}
	}
	PRINT_MSG("return data size: %d", data.size());
	return data;
}

std::vector<int32_t> RealStatus::getFreePlayerBack(int32_t id){
	bool up = isUpSide(id);
	int32_t start = up? 0 : 10;
	int posy = player[id].getPositionY();
	std::vector<int32_t> data;
	for(int32_t i = start; i < start + 10; i++){
		if(up && player[i].getPositionY() > posy){
			data.push_back(i);
		}
		if(!up && player[i].getPositionY() < posy){
			data.push_back(i);
		}
	}
	data.push_back(up? 20 : 21);
	return data;
}

std::vector<int32_t> RealStatus::getFreePlayerPara(int32_t id){
	bool up = isUpSide(id);
	int32_t start = up? 0 : 10;
	int posy = player[id].getPositionY();
	std::vector<int32_t> data;
	for(int32_t i = start; i < start + 10; i++){
		if(player[i].getPositionY() == posy){
			data.push_back(i);
		}
	}
	return data;
}

void RealStatus::Modify(BallStatus &bs){
	int32_t speedx = bs.getSpeed().get_x_speed(); // 1 ~ 20 m/s
	int32_t speedy = bs.getSpeed().get_y_speed(); // 1 ~ 20 m/s
	int32_t dis = Distance(meet_x - bs.getPositionX(), 
							meet_y - bs.getPositionY());
	if(dis == 0)	return;
	if(pass_t == 0){ 
		ball.setPosition(meet_x, meet_y);
		return;
	}
	int32_t speed = dis / pass_t;
	int32_t new_speedx = (meet_x - bs.getPositionX()) * speed / dis;
	int32_t new_speedy = (meet_y - bs.getPositionY()) * speed / dis;
	ball.setSpeed( new_speedx, new_speedy);
}
