#define _HAS_STD_BYTE 0
#pragma once
#include <string>
using namespace std;

namespace PokemonType {
	enum type {
		NORMAL = 0, //�븻
		FIRE, //�Ҳ�
		WATER, //��
		ELECTRIC, //����
		GRASS, //Ǯ
		ICE, //����
		FIGHTING, //����
		POISON, //��
		GROUND, //��
		FLYING, //���� 
		PSYCHIC, //������
		BUG, //����
		ROCK, //����
		GHOST, //��Ʈ
		DRAGON, //�巡��
		DARK, //��
		STEEL, //��ö
		NONE //����
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