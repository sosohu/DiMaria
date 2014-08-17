#ifndef __REALSTATUS__H__
#define __REALSTATUS__H__
#include "include/People.h"
#include "include/Position.h"

class Status
{
	public:
		Status(){}
		virtual	~Status(){}
		
		virtual void NextStatus() const {}
	private:
		Position&	position;
		Speed&	speed;
};

class PlayerStatus : public Status
{
	public:
		PlayerStatus(Player& pl, Position& ps, Speed& sp) : player(pl), position(ps), speed(sp){
		}
		
		~PlayerStatus(){
		}

		void	NextStatus();

	private:
		Player& player;
		bool	catch_ball;
};

class KeeperStatus : public Status
{
	public:
		KeeperStatus(){
		}
		
		~KeeperStatus(){
		}

		void NextStatus();

	private:
		Keeper keeper;
		bool	catch_ball;
};

typedef struct
{
	uint32_t x_speed;
	uint32_t y_speed;
	bool	valid;
}	Kicked;

class BallStatus : public Status
{
	public:
		BallStatus(){
		}

		~BallStatus(){
		}

		uint32_t NextStatus();

		void weaken(Speed& sp);

	private:
		Ball ball;
		Kicked kicked;
};

typedef strcut	
{
	uint32_t	x_start;
	uint32_t	x_end;
	uint32_t	y_start;
	uint32_t	y_end;
}	Scope;

Scope scope_pos[NUM_POS] = {
		{ 0, FIELD_WIDTH, FIELD_LENGTH - 30, FIELD_LENGTH },	//	ST
		{}, //	AMC
		{},	// 	AML
		{},	//	AMR
		{},	//	MC
		{},	//	ML
		{},	//	MR
		{},	//	DM
		{},	//	DC
		{},	//	DL
		{},	//	DR
		{},	//	WL
		{}	//	WR
			//	...
};

typedef	struct StatusInfo
{
	// distance of each two boys,the 3rd dim declares x diraction and y diraction 
	uint32_t distance_boy[NUM_BOYS][NUM_BOYS][2]; 
	// the value declares the num of opposide's plyer who is around(3 m X 3 m)
	// the value equal 0 means the boy is freedom
	uint32_t freedom_boy[NUM_BOYS]; 
	// distance of boys and opposide's gate
	uint32_t distance_gate[NUM_BOYS][2];
	// distance of boys and ball
	uint32_t distance_ball[NUM_BOYS][2];
}	StatusInfo;

typedef struct TacticsInfo
{
	enum Total{
		ATTACK, 
		DEFEND,
		DEFATT, // defend and attack
		CONTROL,
		NORMAL
	} total;

	enum Detail{
		Slide_Pass,// pass ball the middle from the side
		Short_Pass, // short pass penetration
		Shoot_More, // shoot at any chance
		ForWard_More, // foeward more to attack

		Back_More,  // pull back to defend
		Steal_More, // more steal to defend
		Offside_Trap // make the offside trap
	} detail;
}	TacticsInfo;

class RealStatus
{
	public:
		RealStatus(std::vector<PlayerStatus>* pl, std::vector<KeeperStatus>* kp, BallStatus* bl) : player(pl), keeper(kp), ball(bl){

		}

		~RealStatus(){

		}

		void NextStatus();

		void NotifyGoal();

		void ResetStatus();

		void ComputeStatus();

	private:
		// 1 ~ 10 is up side, 11 ~ 20 is down side
		std::vector<PlayerStatus>* player;  // 20 palyer
		// 1 is up side, 2 is down side
		std::vector<KeeperStatus>* keeper;  // 2 keeper
		BallStatus*	 ball;	  // one ball
		bool	BallControl;  // when is ture, the ball is catched by one boy
		/* 
			the id of the boy who catch the ball, 0 ~ 9 is the up side's player,
			10 ~ 19 is the down side's player, 20 is the up side's keeper and 21
			is the down side's keeper
		*/
		uint32_t	catch_boy; // only valid when BallControl is true

		StatusInfo	si;
		TacticsInfo& ti_up, ti_down;
};



#endif
