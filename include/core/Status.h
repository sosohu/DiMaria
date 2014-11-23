#ifndef __STATUS__H__
#define __STATUS__H__

#include "comm.h"
#include "People.h"
#include "Position.h"
#include "Ball.h"

class Status
{
	public:
		Status(Position p, Speed s):position(p),speed(s){}

		virtual	~Status(){}
		
		virtual void NextStatus() const {}

		void setPosition(int32_t x, int32_t y);

		void setPositionMove(Speed sp);

		void setPositionRecover_Outside();

		void setSpeed(int32_t x, int32_t y);

		Position getPosition();

		int32_t getPositionX();

		int32_t getPositionY();

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
		Player player;
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
	int32_t x_speed;
	int32_t y_speed;
	bool	valid;
}	Kicked;

class BallStatus : public Status
{
	public:
		BallStatus(Ball ball, Position p, Speed s) : ball(ball),Status(p, s){
		}

		~BallStatus(){
		}

		int32_t NextStatus();

		void weaken();

		Ball getBall();

	private:
		Ball ball;
		//Kicked kicked;
};

#endif
