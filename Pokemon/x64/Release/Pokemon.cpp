#define _HAS_STD_BYTE 0
#include "Pokemon.h"
#include "Skill.h"
#include <string>
#include <iostream>
#include <windows.h>
using namespace std;

Pokemon::Pokemon() : name("이름"), experience(0), f_hitPoint(0), hitPoint(0), attackPoint(0), defencePoint(0), master("없음") {}
Pokemon::Pokemon(string nm, int exp, int fhp, int atk, int def, int spd, PokemonType::type t1, PokemonType::type t2, Skill* skill[4], string mst) :
    name(nm), experience(exp), f_hitPoint(fhp), hitPoint(fhp), attackPoint(atk), defencePoint(def), speed(spd), type1(t1), type2(t2), master(mst) {
    active = true;
}
Pokemon::Pokemon(string nm, int exp, int fhp, int atk, int def, int spd, PokemonType::type t1, PokemonType::type t2, Skill s1, Skill s2, Skill s3, Skill s4, string mst) :
    name(nm), experience(exp), f_hitPoint(fhp), hitPoint(fhp), attackPoint(atk), defencePoint(def), speed(spd), type1(t1), type2(t2), master(mst) {
    active = true;
    skill[0] = s1;
    skill[1] = s2;
    skill[2] = s3;
    skill[3] = s4;
}

void Pokemon::setName(string nm) {
    name = nm;
}
void Pokemon::setExp(int exp) {
    experience = exp;
}
void Pokemon::setFHp(int fhp) {
    f_hitPoint = fhp;
}
void Pokemon::setHp(int hp) {
    hitPoint = hp;
}
void Pokemon::setAtk(int atk) {
    attackPoint = atk;
}
void Pokemon::setDef(int def) {
    defencePoint = def;
}
void Pokemon::setSpd(int spd) {
    speed = spd;
}
void Pokemon::setMaster(string mst) {
    master = mst;
}

void Pokemon::setActive() {
    active = true;
}
void Pokemon::setDeactive() {
    active = false;
    cout << name << "은(는) 쓰러졌다!" << endl;
}

string Pokemon::getName() {
    return name;
}
int Pokemon::getExp() {
    return experience;
}
int Pokemon::getFHp() {
    return f_hitPoint;
}
int Pokemon::getHp() {
    return hitPoint;
}
int Pokemon::getAtk() {
    return attackPoint;
}
int Pokemon::getDef() {
    return defencePoint;
}
int Pokemon::getSpd() {
    return speed;
}
string Pokemon::getMaster() {
    return master;
}
Skill Pokemon::getSkill(int num) {
    return skill[num];
}

bool Pokemon::isActive() {
    return active;
}

void Pokemon::addExp(int exp) {
    experience += exp;
    cout << name << "은(는) " << exp << "의 경험치를 획득했다!" << endl;
}
void Pokemon::addFHp(int fhp) {
    f_hitPoint += fhp;
    cout << name << "의 최대 체력이 " << fhp << " 증가했다!" << endl;
}
void Pokemon::addHp(int hp) {
    if (hitPoint + hp > f_hitPoint) { //회복 후 체력이 최대 체력을 넘을 경우 최대 체력으로 고정.. 하려고 했으나 확인도 할 겸 회복 가능량을 hp로 대체해 그만큼만 회복케 함.  
        hp = f_hitPoint - hitPoint;
        hitPoint += hp;
    }
    else { hitPoint += hp; }    
    cout << name << "의 체력이 " << hp << " 회복됐다!" << endl;
}
void Pokemon::addAtk(int atk) {
    attackPoint += atk;
    cout << name << "의 공격이 " << atk << " 올랐다!" << endl;
}
void Pokemon::addDef(int def) {
    defencePoint += def;
    cout << name << "의 방어가 " << def << " 올랐다!" << endl;
}
void Pokemon::addSpd(int spd) {
    speed += spd;
    cout << name << "의 스피드가 " << spd << " 올랐다!" << endl;
}

float Pokemon::typeSnW(PokemonType::type t) {
    return ((type1 != PokemonType::NONE) ? typeChart[t][type1] : 1) * ((type2 != PokemonType::NONE) ? typeChart[t][type2] : 1);
}

void Pokemon::damaged(int d) {
    if (hitPoint - d < 0) {
        hitPoint = 0;
    }
    else { hitPoint -= d; }
    cout << name << "은(는) " << d << "의 대미지를 입었다!" << endl;

    if (hitPoint <= 0) {
        setDeactive();
    }
}

void Pokemon::printInfo() {
    cout  << "이  름: " << name << endl << "경험치: " << experience << endl << "체  력: " << hitPoint << " / " << f_hitPoint << endl << "공  격: " << attackPoint << endl << "방  어: " << defencePoint << endl << "마스터: " << master << endl << endl;
}
void Pokemon::coloredName() {
    if (hitPoint > f_hitPoint * 0.9) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //Green
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > f_hitPoint * 0.5) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); //Light Green
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > f_hitPoint * 0.35) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //Light Yellow
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > f_hitPoint * 0.25) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //Yellow
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > f_hitPoint * 0.15) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //Light Red
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //Red
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint <= 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); //Gray
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); //Gray
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
}