#ifndef __PEOPLE__H__
#define __PEOPLE__H__

class people
{
	public:
		people(){}
		~people(){}		
	private:
		uint32_t age;    
		uint32_t height; // cm 
		uint32_t weight; //kg
		uint32_t country_id; 	
};

// the default value range is 0 ~ 100
typedef struct Phy_Atr 
{
	uint32_t pace;    // speed
	uint32_t strength;
	uint32_t jump;
	uint32_t stamina;   // can insist how long
	uint32_t acceleration;   // can speed in a short time
	uint32_t health;    // health firness
	//....
} Phy_Atr;

typedef struct Men_Atr
{
	uint32_t bravery;
	uint32_t influence;

	uint32_t creativity;
	uint32_t off_ball;  // off the ball

	uint32_t position;
	uint32_t concentration;
	uint32_t judge;
	//...
} Men_Atr;

typedef struct Tec_Atr
{
	uint32_t dribbling;  // run with the ball
	uint32_t finishing;
	uint32_t crossing;
	uint32_t heading;
	uint32_t passing;
	uint32_t corners;
	uint32_t throwers;
	uint32_t free_kick;
	uint32_t point;
	uint32_t touch;     // touch and stop the ball
	uint32_t long_shoot;

	uint32_t marking;
	uint32_t tracking;   // get the ball from opposite side
	
} Tec_Atr;

typedef struct Kee_Atr
{
	uint32_t command;  // command for the defence
	uint32_t handing;  // keep the goal in the hands
	uint32_t kicking;  // kick a long ball with foot
	uint32_t air_control; // contral the air
	uint32_t one2one;  // one to one
	uint32_t throwing; // throw the ball
	uint32_t rush_out; // get out of the ...
	uint32_t reaction;  // response ability  
} Kee_Atr;

class player : people
{
	public:
		player(){}
		~player(){}
	private:
		Phy_Atr phy_atr;
		Men_Atr men_atr;
		Tec_Atr tec_atr;
};

class keeper : people
{
	public:
		keeper(){}
		~keeper(){}
	private:
		Kee_Atr kee_atr;
};



#endif
