#ifndef __PEOPLE__H__
#define __PEOPLE__H__
#include "comm.h"
#include <string>
#include <cstdlib>
#include <cassert>
#include <vector>

// the default value range is 0 ~ 20
// num = 6
typedef struct Bas_Atr {
	std::string name;
	std::string id;
	int32_t age;
	int32_t height;	// cm 
	int32_t weight;	//kg
	std::string country;
	//
	void setValue(std::vector<std::string> data, int32_t num){
		char *end;
		assert(data.size() >= num);
		assert(num == 6);
		name  = data[0];
		id = data[1];
		age = static_cast<int32_t>(strtol(data[2].c_str(),&end,10));
		height = static_cast<int32_t>(strtol(data[3].c_str(), &end, 10));
		weight = static_cast<int32_t>(strtol(data[4].c_str(), &end, 10));
		country = data[5];
	}
} Bas_Atr;

class People {
	public:
		People(Bas_Atr b):bas_atr(b) {} 
		~People() {}
    private:
		Bas_Atr bas_atr;
};

// the default value range is 0 ~ 20
// num = 6
typedef struct Phy_Atr {
	int32_t pace;		// speed
	int32_t strength;
	int32_t jump;
	int32_t stamina;	// can insist how long
	int32_t acceleration;	// can speed in a short time
	int32_t health;	// health firness
	//....

	void setValue(std::vector<std::string> data, int32_t num){
		char *end;
		assert(data.size() >= num);
		assert(num == 6);
		pace = static_cast<int32_t>(strtol(data[0].c_str(), &end, 10));
		strength = static_cast<int32_t>(strtol(data[1].c_str(), &end, 10));
		jump = static_cast<int32_t>(strtol(data[2].c_str(), &end, 10));
		stamina = static_cast<int32_t>(strtol(data[3].c_str(), &end, 10));
		acceleration = static_cast<int32_t>(strtol(data[4].c_str(), &end, 10));
		health = static_cast<int32_t>(strtol(data[5].c_str(), &end, 10));
	}
} Phy_Atr;

// num = 7
typedef struct Men_Atr {
	int32_t bravery;
	int32_t influence;

	int32_t creativity;
	int32_t off_ball;	// off the ball

	int32_t position;
	int32_t concentration;
	int32_t judge;
	//...

	void setValue(std::vector<std::string> data, int32_t num){
		char *end;
		assert(data.size() >= num);
		assert(num == 7);
		bravery = static_cast<int32_t>(strtol(data[0].c_str(), &end, 10));
		influence = static_cast<int32_t>(strtol(data[1].c_str(), &end, 10));
		creativity = static_cast<int32_t>(strtol(data[2].c_str(), &end, 10));
		off_ball = static_cast<int32_t>(strtol(data[3].c_str(), &end, 10));
		position = static_cast<int32_t>(strtol(data[4].c_str(), &end, 10));
		concentration = static_cast<int32_t>(strtol(data[5].c_str(), &end, 10));
		judge = static_cast<int32_t>(strtol(data[6].c_str(), &end, 10));
	}
} Men_Atr;

// num = 13
typedef struct Tec_Atr {
	int32_t dribbling;	// run with the ball
	int32_t finishing;
	int32_t crossing;
	int32_t heading;
	int32_t passing;
	int32_t corners;
	int32_t throwers;
	int32_t free_kick;
	int32_t point;
	int32_t touch;		// touch and stop the ball
	int32_t long_shoot;

	int32_t marking;
	int32_t tracking;	// get the ball from opposite side
	
	void setValue(std::vector<int32_t> data, int32_t num){
		assert(data.size() >= num);
		assert(num == 13);
		dribbling = data[0];
		finishing = data[1];
		crossing = data[2];
		heading = data[3];
		passing = data[4];
		corners = data[5];
		throwers = data[6];
		free_kick = data[7];
		point = data[8];
		touch = data[9];	
		long_shoot = data[10];
		marking = data[11];
		tracking = data[12];	
	}

	void setValue(std::vector<std::string> data, int32_t num){
		assert(data.size() >= num);
		assert(num == 13);
		char *end;
		dribbling = static_cast<int32_t>(strtol(data[0].c_str(), &end, 10));
		finishing = static_cast<int32_t>(strtol(data[1].c_str(), &end, 10));
		crossing = static_cast<int32_t>(strtol(data[2].c_str(), &end, 10));
		heading = static_cast<int32_t>(strtol(data[3].c_str(), &end, 10));
		passing = static_cast<int32_t>(strtol(data[4].c_str(), &end, 10));
		corners = static_cast<int32_t>(strtol(data[5].c_str(), &end, 10));
		throwers = static_cast<int32_t>(strtol(data[6].c_str(), &end, 10));
		free_kick = static_cast<int32_t>(strtol(data[7].c_str(), &end, 10));
		point = static_cast<int32_t>(strtol(data[8].c_str(), &end, 10));
		touch = static_cast<int32_t>(strtol(data[9].c_str(), &end, 10));	
		long_shoot = static_cast<int32_t>(strtol(data[10].c_str(), &end, 10));
		marking = static_cast<int32_t>(strtol(data[11].c_str(), &end, 10));
		tracking = static_cast<int32_t>(strtol(data[12].c_str(), &end, 10));	
	}
} Tec_Atr;

// num = 8
typedef struct Kee_Atr {
	int32_t command;	// command for the defence
	int32_t handing;	// keep the goal in the hands
	int32_t kicking;	// kick a long ball with foot
	int32_t air_control;	// contral the air
	int32_t one2one;	// one to one
	int32_t throwing;	// throw the ball
	int32_t rush_out;	// get out of the ...
	int32_t reaction;	// response ability  
	//
	void setValue(std::vector<std::string> data, int32_t num){
		assert(data.size() >= num);
		assert(num == 8);
		char *end;
		command = static_cast<int32_t>(strtol(data[0].c_str(), &end, 10));
		handing = static_cast<int32_t>(strtol(data[1].c_str(), &end, 10));
		kicking = static_cast<int32_t>(strtol(data[2].c_str(), &end, 10));
		air_control = static_cast<int32_t>(strtol(data[3].c_str(), &end, 10));
		one2one = static_cast<int32_t>(strtol(data[4].c_str(), &end, 10));
		throwing = static_cast<int32_t>(strtol(data[5].c_str(), &end, 10));
		rush_out = static_cast<int32_t>(strtol(data[6].c_str(), &end, 10));
		reaction = static_cast<int32_t>(strtol(data[7].c_str(), &end, 10));
	}
} Kee_Atr;

typedef enum Play_Pos
{
	ST,
	AMC,
	AML,
	AMR,
	MC,
	ML,
	MR,
	DM,
	DC,
	DL,
	DR,
	WL,
	WR,
	GK
} Play_Pos;


void setPlay_Pos(Play_Pos &pp, std::string data);

class Player : public People {
      public:
	Player(Bas_Atr b, Phy_Atr p, Men_Atr m, Tec_Atr t, Kee_Atr k, Play_Pos pos)
			:People(b),phy_atr(p),men_atr(m),tec_atr(t),kee_atr(k),pos(pos) {
	} 
	~Player() {
	}

	Phy_Atr getPhy_Atr();

	Men_Atr getMen_Atr();

	Tec_Atr getTec_Atr();

	Kee_Atr getKee_Atr();

	Play_Pos getPlay_Pos();

      private:
	Phy_Atr phy_atr;
	Men_Atr men_atr;
	Tec_Atr tec_atr;
	Kee_Atr kee_atr;
	Play_Pos pos;   // which pos can play, 
};

/*
class Keeper : public People {
      public:
	Keeper() {
	} ~Keeper() {
	}
      private:
	Kee_Atr kee_atr;
};
*/

#endif
