#ifndef __REALSTATUS__H__
#define __REALSTATUS__H__

class PlayerStatus
{
	public:
		PlayerStatus(Player& pl, Position& ps, Speed& sp) : player(pl), position(ps), speed(sp){
		}
		
		~PlayerStatus(){
		}

		uint32_t NextStatus();

	private:
		Player& player;
		Position&	position;
		Speed&	speed;
};

class KeeperStatus
{
	public:
		KeeperStatus(){
		}
		
		~KeeperStatus(){
		}

		void NextStatus();

	private:
		Keeper keeper;
		Position	position;
		Speed	speed;
};

class BallStatus
{
	public:
		BallStatus(){
		}

		~BallStatus(){
		}

		void NextStatus();

	private:
		Ball ball;
		Position position;
		Speed speed;
};

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

	private:
		std::vector<PlayerStatus>* player;  // 20 palyer
		std::vector<KeeperStatus>* keeper;  // 2 keeper
		BallStatus*	 ball;	  // one ball
		bool	BallControl;
};



#endif
