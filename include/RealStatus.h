#ifndef __REALSTATUS__H__
#define __REALSTATUS__H__

class PlayerStatus
{
	public:
		PlayerStatus(){
		}
		
		~PlayerStatus(){
		}

	private:
		Player player;
		Position	position;
		Speed	speed;
};

class KeeperStatus
{
	public:
		KeeperStatus(){
		}
		
		~KeeperStatus(){
		}

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

	private:
		Ball ball;
		Position position;
		Speed speed;
};

class RealStatus
{
	public:
		RealStatus(){
		}

		~RealStatus(){
		}

		void NextStatus(){ // next second's status
		}

	private:
		PlayerStatus* player;  // 20 palyer
		KeeperStatus* keeper;  // 2 keeper
		BallStatus	 ball;	  // one ball
};



#endif
