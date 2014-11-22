#include "DiMaria/core.h"
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <string>
#include <cassert>


bool spliteAtr(std::string &data, Bas_Atr &ba, Phy_Atr &pa, Men_Atr &ma, 
				Tec_Atr &ta, Kee_Atr &ka, Play_Pos &pp){
	int len = data.length();
	int pos = 0;
	while(pos < len && data[pos] == ' '){
		pos++;
	}	
	if(pos == len)	return false;
	int start = pos;
	std::vector<std::string> bucket(NUM_ATR, "");
	int index = 0;
	while(pos < len){
		while(pos < len && data[pos] != ' ')	{
			pos++;
		}
		bucket[index++] = data.substr(start, pos - start);
		if(pos == len)	break;
		pos++;
		start = pos;
	}
	assert(index == NUM_ATR);
	std::vector<std::string>::iterator it_start;
	std::vector<std::string>::iterator it_end;
	it_start = bucket.begin();
	it_end = bucket.end();
	ba.setValue(std::vector<std::string>(it_start, it_end), 6);
	for(uint32_t i = 0; i < 6; i++)
		it_start++;
	pa.setValue(std::vector<std::string>(it_start, it_end), 6);
	for(uint32_t i = 0; i < 6; i++)
		it_start++;
	ma.setValue(std::vector<std::string>(it_start, it_end), 7);
	for(uint32_t i = 0; i < 7; i++)
		it_start++;
	ta.setValue(std::vector<std::string>(it_start, it_end), 13);
	for(uint32_t i = 0; i < 13; i++)
		it_start++;
	ka.setValue(std::vector<std::string>(it_start, it_end), 8);
	setPlay_Pos(pp, *it_start);
	//PRINT_MSG("PASS");
}

void Init_Position(std::vector<Position> &init_position, Position &init_ball){
	uint32_t size = init_position.size();
	assert(size == NUM_BOYS);
	// init up
	init_position[20].set_x(34);
	init_position[20].set_y(106);
	init_position[20].set_side(true);
	init_position[0].set_x(10);
	init_position[0].set_y(96);
	init_position[0].set_side(true);
	init_position[1].set_x(24);
	init_position[1].set_y(96);
	init_position[1].set_side(true);
	init_position[2].set_x(38);
	init_position[2].set_y(96);
	init_position[2].set_side(true);
	init_position[3].set_x(56);
	init_position[3].set_y(96);
	init_position[3].set_side(true);
	init_position[4].set_x(18);
	init_position[4].set_y(52);
	init_position[4].set_side(true);
	init_position[5].set_x(34);
	init_position[5].set_y(52);
	init_position[5].set_side(true);
	init_position[6].set_x(60);
	init_position[6].set_y(52);
	init_position[6].set_side(true);
	init_position[7].set_x(18);
	init_position[7].set_y(20);
	init_position[7].set_side(true);
	init_position[8].set_x(34);
	init_position[8].set_y(20);
	init_position[8].set_side(true);
	init_position[9].set_x(60);
	init_position[9].set_y(20);
	init_position[9].set_side(true);
	// init down
	init_position[21].set_x(34);
	init_position[21].set_y(0);
	init_position[21].set_side(true);
	init_position[10].set_x(10);
	init_position[10].set_y(10);
	init_position[10].set_side(true);
	init_position[11].set_x(24);
	init_position[11].set_y(10);
	init_position[11].set_side(true);
	init_position[12].set_x(38);
	init_position[12].set_y(10);
	init_position[12].set_side(true);
	init_position[13].set_x(56);
	init_position[13].set_y(10);
	init_position[13].set_side(true);
	init_position[14].set_x(18);
	init_position[14].set_y(52);
	init_position[14].set_side(true);
	init_position[15].set_x(34);
	init_position[15].set_y(52);
	init_position[15].set_side(true);
	init_position[16].set_x(60);
	init_position[16].set_y(52);
	init_position[16].set_side(true);
	init_position[17].set_x(18);
	init_position[17].set_y(86);
	init_position[17].set_side(true);
	init_position[18].set_x(34);
	init_position[18].set_y(86);
	init_position[18].set_side(true);
	init_position[19].set_x(60);
	init_position[19].set_y(86);
	init_position[19].set_side(true);
	// init ball
	init_ball.set_x(34);
	init_ball.set_y(52);
	init_ball.set_side(true);
}

int main(int argc, char** argv)
{
	Bas_Atr ba;
	Phy_Atr pa;
	Men_Atr ma;
	Tec_Atr ta;
	Kee_Atr ka;
	Play_Pos pp;

	// read attitude from file
	if(argc < 2){
		std::cout<<"ERROR: MISS INPUT"<<std::endl;
		exit(MISS_INPUT);
	}
	const char *path = argv[1];
	std::ifstream file(path);

	if(file.fail()){
		std::cout<<"ERROR: OPEN FILE FAILED"<<std::endl;
		exit(OPEN_FAILED);
	}
	
	char data[ATR_MAX_LEN];
	file.getline(data, ATR_MAX_LEN);


	std::string tmp = data;
	spliteAtr(tmp, ba, pa, ma, ta, ka, pp);


	// prepare for RealStatus object
	std::vector<Player> players(NUM_BOYS, Player(ba, pa, ma, ta, ka, pp));
	std::vector<Position> init_position(NUM_BOYS, Position(0,0,true));
	Bal_Atr bal_atr = {0xc1, 0x01}; // blue, middle
	Ball ball(bal_atr);
	Position init_ball(0,0,true);
	Init_Position(init_position, init_ball);
	Speed sp(0, 0);

	std::vector<PlayerStatus> ps;
	for(uint32_t i = 0; i < NUM_BOYS; i++){
		ps.push_back(PlayerStatus(players[i], init_position[i], sp));
	}
	BallStatus bs(ball, init_ball, sp);

	TacticsInfo ti_up = {ATTACK, ForWard_More};
	TacticsInfo ti_down = {DEFEND, Back_More};
	
	// create RealStatus object
	RealStatus rl(ps, bs, ti_up, ti_down, init_position, init_ball); 
	
	uint32_t ret = 0;
	while(ret != OVER_STATUS){
		ret = rl.NextStatus();
		std::cout<<rl.TextComment()<<std::endl;
		rl.print_pos();
		//std::cout<<"ball position: "<<rl.getBallStatus().getPositionX()<<" , "
		//		<<rl.getBallStatus().getPositionY()<<std::endl;
	}
	
	return 0;
}
