#define _HAS_STD_BYTE 0
#pragma once
#include <string>
using namespace std;

namespace PokemonType {
	enum type {
		NORMAL = 0, //노말
		FIRE, //불꽃
		WATER, //물
		ELECTRIC, //전기
		GRASS, //풀
		ICE, //얼음
		FIGHTING, //격투
		POISON, //독
		GROUND, //땅
		FLYING, //비행 
		PSYCHIC, //에스퍼
		BUG, //벌레
		ROCK, //바위
		GHOST, //고스트
		DRAGON, //드래곤
		DARK, //악
		STEEL, //강철
		NONE //없음
	};
}

class Skill {
	string name = "";
	PokemonType::type type;
	int power = 0;
	int hit = 0;
	int pp = 0;
	int priority = 0;
	string additionalEffect = "";

public:
	Skill() {};
	Skill(string nm, PokemonType::type typ, int pw, int h, int p, int pr, string ae) :
		name(nm), type(typ), power(pw), hit(h), pp(p), priority(pr), additionalEffect(ae) {};
	~Skill() {};

	void setName(string nm) { name = nm; }
	void setType(PokemonType::type typ) { type = typ; }
	void setPw(int p) { power = p; }
	void setHit(int h) { hit = h; }
	void setPP(int p) { pp = p; }
	void setPr(int pr) { priority = pr; }
	void setAe(string ae) { additionalEffect = ae; }

	string getName() { return name; }
	PokemonType::type getType() { return type; }
	int getPw() { return power; }
	int getHit() { return hit; }
	int getPP() { return pp; }
	int getPr() { return priority; }
	string getAe() { return additionalEffect; }
};