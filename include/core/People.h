#ifndef __PEOPLE__H__
#define __PEOPLE__H__
#include "comm.h"

// the default value range is 0 ~ 20
typedef struct Bas_Atr {
	uint32_t age;
	uint32_t height;	// cm 
	uint32_t weight;	//kg
	uint32_t country_id;
} Bas_Atr;

class People {
	public:
		People(Bas_Atr b):bas_atr(b) {} 
		~People() {}
    private:
		Bas_Atr bas_atr;
};

// the default value range is 0 ~ 20
typedef struct Phy_Atr {
	uint32_t pace;		// speed
	uint32_t strength;
	uint32_t jump;
	uint32_t stamina;	// can insist how long
	uint32_t acceleration;	// can speed in a short time
	uint32_t health;	// health firness
	//....
} Phy_Atr;

typedef struct Men_Atr {
	uint32_t bravery;
	uint32_t influence;

	uint32_t creativity;
	uint32_t off_ball;	// off the ball

	uint32_t position;
	uint32_t concentration;
	uint32_t judge;
	//...
} Men_Atr;

typedef struct Tec_Atr {
	uint32_t dribbling;	// run with the ball
	uint32_t finishing;
	uint32_t crossing;
	uint32_t heading;
	uint32_t passing;
	uint32_t corners;
	uint32_t throwers;
	uint32_t free_kick;
	uint32_t point;
	uint32_t touch;		// touch and stop the ball
	uint32_t long_shoot;

	uint32_t marking;
	uint32_t tracking;	// get the ball from opposite side

} Tec_Atr;

typedef struct Kee_Atr {
	uint32_t command;	// command for the defence
	uint32_t handing;	// keep the goal in the hands
	uint32_t kicking;	// kick a long ball with foot
	uint32_t air_control;	// contral the air
	uint32_t one2one;	// one to one
	uint32_t throwing;	// throw the ball
	uint32_t rush_out;	// get out of the ...
	uint32_t reaction;	// response ability  
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
} Play_Pos;

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
