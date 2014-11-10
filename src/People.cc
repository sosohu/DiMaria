#include "comm.h"
#include "People.h"

Phy_Atr Player::getPhy_Atr(){
	return phy_atr;
}

Men_Atr Player::getMen_Atr(){
	return men_atr;
}

Tec_Atr Player::getTec_Atr(){
	return tec_atr;
}

Kee_Atr Player::getKee_Atr(){
	return kee_atr;
}

void setPlay_Pos(Play_Pos pp, std::string data){
	if(data.compare("ST") == 0){
		pp = ST;
		return;
	}
	if(data.compare("AMC") == 0){
		pp = AMC;
		return;
	}
	if(data.compare("AML") == 0){
		pp = AML;
		return;
	}
	if(data.compare("AMR") == 0){
		pp = AMR;
		return;
	}
	if(data.compare("MC") == 0){
		pp = MC;
		return;
	}
	if(data.compare("ML") == 0){
		pp = ML;
		return;
	}
	if(data.compare("MR") == 0){
		pp = MR;
		return;
	}
	if(data.compare("DM") == 0){
		pp = DM;
		return;
	}
	if(data.compare("DC") == 0){
		pp = DC;
		return;
	}
	if(data.compare("DL") == 0){
		pp = DL;
		return;
	}
	if(data.compare("DR") == 0){
		pp = DR;
		return;
	}
	if(data.compare("WL") == 0){
		pp = WL;
		return;
	}
	if(data.compare("WR") == 0){
		pp = WR;
		return;
	}
	if(data.compare("GK") == 0){
		pp = GK;
		return;
	}
}
