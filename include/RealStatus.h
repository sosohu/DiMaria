#ifndef __REALSTATUS__H__
#define __REALSTATUS__H__

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
