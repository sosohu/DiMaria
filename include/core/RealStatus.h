#ifndef __REALSTATUS__H__
#define __REALSTATUS__H__
#include "Status.h"
#include <string>
#include <vector>

typedef struct	
{
	int32_t	x_start;
	int32_t	x_end;
	int32_t	y_start;
	int32_t	y_end;
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
	int32_t distance_boy[NUM_BOYS][NUM_BOYS][2]; 
	/* the value declares the num of opposide's plyer who is around(3 m X 3 m)
	   the value equal 0 means the boy is freedom */
	int32_t around_boys[NUM_BOYS]; 
	// distance of boys and opposide's gate with x distance and y distance
	int32_t distance_gate[NUM_BOYS][2];
	// distance of boys and ball with x distance and y distance
	int32_t distance_ball[NUM_BOYS][2];
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
		int32_t NextStatus();

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

		// return BallStatus
		BallStatus getBallStatus();

	private:
		
		// id is player/keeper's id who catch the ball
		void SmartCatch(int32_t id);
		void SmartDefend(int32_t id);
		void SmartAttack(int32_t id);

		// detail, select which way: shoot, siege, pass or dribbling
		int32_t SmartSelect(int32_t id);
		// detail, select how to pass: pass forward or pass back
		int32_t PassSelect(int32_t id);
		
		// detail, exe the choose
		void MakeShoot(int32_t id);
		void MakeSiege(int32_t id);
		void MakePass(int32_t id);
		void MakeDri(int32_t id);
		void MakePassForward(int32_t id);
		void MakePassBack(int32_t id);

		// move;
		void MoveForward(int32_t id);
		void MoveForMeet(int32_t id);
		void Modify(BallStatus &bs);

		// return the free player
		std::vector<int32_t>	getFreePlayer(int32_t id);
		std::vector<int32_t>	getFreePlayerForward(int32_t id);
		std::vector<int32_t>	getFreePlayerBack(int32_t id);
		std::vector<int32_t>	getFreePlayerPara(int32_t id);

	private:
		// 0~9 is up side, 10~19 is down side, 20 is up keeper, 21 is down keeper
		std::vector<PlayerStatus> player;  // 20 palyer
		//std::vector<KeeperStatus> *keeper;  // 2 keeper
		BallStatus	 ball;	  // one ball

		bool	BallControl;  // when is ture, the ball is catched by one boy
		/* 
			the id of the boy who catch the ball, 0 ~ 9 is the up side's player,
			10 ~ 19 is the down side's player, 20 is the up side's keeper and 21
			is the down side's keeper
		*/
		int32_t	catch_boy; // only valid when BallControl is true
		int32_t	get_boy; // catch_boy pass ball to get_boy, -1 is NULL
		int32_t meet_x; // the x position will the get_boy meet the ball
		int32_t meet_y;	// the y position will the get_boy meet the ball
		int32_t pass_t; // the time should be cost for pass ball from catch_boy to get_ball

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
