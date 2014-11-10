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
	pa.setValue(std::vector<std::string>(it_start, it_end), 7);
	for(uint32_t i = 0; i < 7; i++)
		it_start++;
	ta.setValue(std::vector<std::string>(it_start, it_end), 13);
	for(uint32_t i = 0; i < 13; i++)
		it_start++;
	ka.setValue(std::vector<std::string>(it_start, it_end), 8);
	setPlay_Pos(pp, *it_end);
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

	std::vector<Player> players(20, Player(ba, pa, ma, ta, ka, pp));
	
	return 0;
}
