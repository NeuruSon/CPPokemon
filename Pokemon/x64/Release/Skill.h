#define _HAS_STD_BYTE 0
#pragma once
#include <string>
using namespace std;

class Skill {
	string name = "";
	string type = "";
	int power = 0;
	int hit = 0;
	int pp = 0;
	int priority = 0;
	string additionalEffect = "";

public:
	Skill() {};
	Skill(string nm, string typ, int pw, int h, int p, int pr, string ae) :
		name(nm), type(typ), power(pw), hit(h), pp(p), priority(pr), additionalEffect(ae) {};
	~Skill() {};

	void setName(string nm) { name = nm; }
	void setType(string typ) { type = typ; }
	void setPw(int p) { power = p; }
	void setHit(int h) { hit = h; }
	void setPP(int p) { pp = p; }
	void setPr(int pr) { priority = pr; }
	void setAe(string ae) { additionalEffect = ae; }

	string getName() { return name; }
	string getType() { return type; }
	int getPw() { return power; }
	int getHit() { return hit; }
	int getPP() { return pp; }
	int getPr() { return priority; }
	string getAe() { return additionalEffect; }
};