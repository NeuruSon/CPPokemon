#define _HAS_STD_BYTE 0
#pragma once
#include <string>
#include "Pokemon.h"
using namespace std;

class Trainer {
	string name = "";
	int money = 0; //家瘤陛 
	Pokemon pokemon[6] = {}; //后沫 贸府 肋窍扁 

public: 
	Trainer() {};
	Trainer(string nm, int mny, Pokemon pkm[6]) : name(nm), money(mny) {
		pokemon[0] = pkm[0];
		pokemon[1] = pkm[1];
		pokemon[2] = pkm[2];
		pokemon[3] = pkm[3];
		pokemon[4] = pkm[4];
		pokemon[5] = pkm[5];
	};
	~Trainer() {};

	string getName() { return name; }
	int getMny() { return money; }
	Pokemon getPkm(int n) { return pokemon[n]; }
	
	void setName(string nm) { name = nm; }
	void setMny(int mny) { money = mny; }
	void setPkm(Pokemon pkm, int n) { pokemon[n] = pkm; }

	void changeMny(int mny) { money += mny; }
};
