#define _HAS_STD_BYTE 0
#include "Pokemon.h"
#include "Skill.h"
#include <string>
#include <iostream>
#include <windows.h>
using namespace std;

Pokemon::Pokemon() : name("이름"), experience(0), f_hitPoint(0), hitPoint(0), attackPoint(0), defencePoint(0), master("없음") {}
Pokemon::Pokemon(string nm, int exp, int fhp, int atk, int def, int spd, string type[2], Skill* skill[4], string mst) :
    name(nm), experience(exp), f_hitPoint(fhp), hitPoint(fhp), attackPoint(atk), defencePoint(def), speed(spd), master(mst) {
    active = true;
}
Pokemon::Pokemon(string nm, int exp, int fhp, int atk, int def, int spd, string type[2], Skill s1, Skill s2, Skill s3, Skill s4, string mst) :
    name(nm), experience(exp), f_hitPoint(fhp), hitPoint(fhp), attackPoint(atk), defencePoint(def), speed(spd), master(mst) {
    active = true;
    skill[0] = s1;
    skill[1] = s2;
    skill[2] = s3;
    skill[3] = s4;
}
Pokemon::Pokemon(string nm, int exp, int fhp, int atk, int def, int spd, string type1, string type2, Skill s1, Skill s2, Skill s3, Skill s4, string mst) :
    name(nm), experience(exp), f_hitPoint(fhp), hitPoint(fhp), attackPoint(atk), defencePoint(def), speed(spd), master(mst) {
    active = true;
    type[0] = type1;
    type[1] = type2;
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
    cout << name << "는 " << exp << "의 경험치를 획득했다!" << endl;
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

void Pokemon::damaged(int d) {
    if (hitPoint - d < 0) {
        hitPoint = 0;
    }
    else { hitPoint -= d; }
    cout << name << "은(는) " << d << "의 대미지를 입었다!" << endl;
}

void Pokemon::printInfo() {
    cout  << "이  름: " << name << endl << "경험치: " << experience << endl << "체  력: " << hitPoint << " / " << f_hitPoint << endl << "공  격: " << attackPoint << endl << "방  어: " << defencePoint << endl << "마스터: " << master << endl << endl;
}
void Pokemon::coloredName() {
    // cout << "\x1b[42m" << " " << "\x1b[102m" << " " << "\x1b[103m" << " " << "\x1b[43m" << " " << "\x1b[101m" << " " << "\x1b[41m" << " " << "\x1b[0m";
    if (hitPoint > f_hitPoint * 0.9) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > f_hitPoint * 0.7) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > f_hitPoint * 0.55) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > f_hitPoint * 0.3) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > f_hitPoint * 0.1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
}