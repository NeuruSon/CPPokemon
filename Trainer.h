#define _HAS_STD_BYTE 0
#pragma once
#include <string>
#include "Pokemon.h"
using namespace std;

namespace TrainerType {
	enum type {
		PLAYER = 3, //플레이어 
		CHAMPION, //챔피언
		TRAINER, //상대 트레이너
		NONTRAINER //야생 포켓몬
	};
}

class Trainer {
	string name = "";
	int money = 0; //소지금 
	Pokemon pokemon[6] = {}; //빈칸 처리 잘하기 
	TrainerType::type trainerType;

public: 
	Trainer() {};
	Trainer(string nm, int mny, Pokemon pkm[6], TrainerType::type typ) : name(nm), money(mny) {
		pokemon[0] = pkm[0];
		pokemon[1] = pkm[1];
		pokemon[2] = pkm[2];
		pokemon[3] = pkm[3];
		pokemon[4] = pkm[4];
		pokemon[5] = pkm[5];
		trainerType = typ;
	};
	~Trainer() {};

	string getName() { return name; }
	int getMny() { return money; }
	//Pokemon getPkm(int n) { return pokemon[n]; }
	Pokemon* getPkm(int n) { return &pokemon[n]; }
	
	void setName(string nm) { name = nm; }
	void setMny(int mny) { money = mny; }
	void setPkm(Pokemon pkm, int n) { pokemon[n] = pkm; }

	void changeMny(int mny) { money += mny; }
	int getAlivePkmCount() {
		int count = 6;
		for (int i = 0; i < 6; ++i) {
			if (pokemon[i].isActive() == false) { --count; }
		}
		return count;
	}
};
