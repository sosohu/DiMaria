#ifndef __REALSTATUS__H__
#define __REALSTATUS__H__
#include "comm.h"
#include "People.h"
#include "Position.h"
#include "Ball.h"
#include <string>
#include <vector>

class Status
{
	public:
		Status(Position p, Speed s):position(p),speed(s){}
		virtual	~Status(){}
		
		virtual void NextStatus() const {}

		void setPosition(uint32_t x, uint32_t y);

		void setPositionMove(Speed sp);

		void setPositionRecover_Outside();

		void setSpeed(uint32_t x, uint32_t y);

		Position getPosition();

		uint32_t getPositionX();

		uint32_t getPositionY();

		bool getPositionIs_goal();

		bool getPositionIs_outside();

		bool getPositionIs_corner();
		
		Speed getSpeed();
	private:
		Position	position;
		Speed	speed;
};

class PlayerStatus : public Status
{
	public:
		PlayerStatus(Player pl, Position ps, Speed sp) : player(pl), Status(ps, sp){
		}
		
		~PlayerStatus(){
		}

		void	NextStatus();

		Player getPlayer();

		Phy_Atr getPlayerPhy_Atr();

		Men_Atr getPlayerMen_Atr();

		Tec_Atr getPlayerTec_Atr();

		Kee_Atr getPlayerKee_Atr();

	private:
		Player &player;
		//bool	catch_ball;
};

/*
class KeeperStatus : public Status
{
	public:
		KeeperStatus(){
		}
		
		~KeeperStatus(){
		}

		void NextStatus();

		Keeper getPlayer();

	private:
		Keeper &player;
		//bool	catch_ball;
};
*/

typedef struct
{
	uint32_t x_speed;
	uint32_t y_speed;
	bool	valid;
}	Kicked;

class BallStatus : public Status
{
	public:
		BallStatus(Ball ball, Position p, Speed s) : ball(ball),Status(p, s){
		}

		~BallStatus(){
		}

		uint32_t NextStatus();

		void weaken();

		Ball getBall();

	private:
		Ball ball;
		//Kicked kicked;
};

typedef struct	
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
	/* the value declares the num of opposide's plyer who is around(3 m X 3 m)
	   the value equal 0 means the boy is freedom */
	uint32_t around_boys[NUM_BOYS]; 
	// distance of boys and opposide's gate with x distance and y distance
	uint32_t distance_gate[NUM_BOYS][2];
	// distance of boys and ball with x distance and y distance
	uint32_t distance_ball[NUM_BOYS][2];
}	StatusInfo;

enum Tac_Total{
	ATTACK, // attack like the Dortmund
	DEFEND, // defend like the Chelsea
	CONTROL // control like the FCB
};

enum Tac_Detail{
	Slide_Pass,// pass ball to the middle from the side
	Short_Pass, // short pass penetration
	Shoot_More, // shoot at any chance
	ForWard_More, // forward more to attack
	Break_More, // break througth more

	Back_More,  // pull back to defend
	Steal_More, // more steal to defend
	Offside_Trap // make the offside trap
};

typedef struct TacticsInfo
{
	enum Tac_Total total;

	enum Tac_Detail detail;
}	TacticsInfo;

class RealStatus
{
	public:
		RealStatus(std::vector<PlayerStatus> ps, BallStatus bs, 
					TacticsInfo ti_up,TacticsInfo ti_down, 
					std::vector<Position> &init_position,
					Position &init_ball) : player(ps), ball(bs), ti_up(ti_up),
					ti_down(ti_down), init_position(init_position), 
					init_ball(init_ball){
			ResetStatus();
		}

		~RealStatus(){

		}

		// next status, core func and have the effect on the game.
		uint32_t NextStatus();

		// when the goal, notify.
		void NotifyGoal();

		// reset the status after the goal.
		void ResetStatus(bool up = true);

		// start corner.
		void StartCorner();

		// start freeball.
		void StartFree();

		// start outside
		void StartOutside(); 

		// compute the status each times and perpare for the Status.
		void ComputeStatus();

		// return the comment of match by the Status.
		std::string TextComment();

	private:
		
		// id is player/keeper's id who catch the ball
		void SmartSelect(uint32_t id);

		//	
		void SmartDefend(uint32_t id);

		void SmartAttack(uint32_t id);
	private:
		// 0~9 is up side, 10~19 is down side, 20 is up keeper, 21 is down keeper
		std::vector<PlayerStatus> &player;  // 20 palyer
		//std::vector<KeeperStatus> *keeper;  // 2 keeper
		BallStatus	 &ball;	  // one ball

		bool	BallControl;  // when is ture, the ball is catched by one boy
		/* 
			the id of the boy who catch the ball, 0 ~ 9 is the up side's player,
			10 ~ 19 is the down side's player, 20 is the up side's keeper and 21
			is the down side's keeper
		*/
		uint32_t	catch_boy; // only valid when BallControl is true

		/* the ball is outside and turn to the outside ball status
			judge the position by the ball's position
		*/
		bool outside;

		/* the ball is turn to the corner status
			judge the position by the ball's position
		*/
		bool corner;

		StatusInfo	si;
		TacticsInfo &ti_up, &ti_down;

		// record the comment of game
		std::string status_comment;
		// init position
		std::vector<Position> init_position;
		Position init_ball;
};



#endif
