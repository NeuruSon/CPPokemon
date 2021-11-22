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
    cout << endl << name << "은(는) " << exp << "의 경험치를 획득했다!" << endl;
}
void Pokemon::addFHp(int fhp) {
    f_hitPoint += fhp;
    cout << endl << name << "의 최대 체력이 " << fhp << " 증가했다!" << endl;
}
void Pokemon::addHp(int hp) {
    if (hitPoint + hp > f_hitPoint) { //회복 후 체력이 최대 체력을 넘을 경우 최대 체력으로 고정.. 하려고 했으나 확인도 할 겸 회복 가능량을 hp로 대체해 그만큼만 회복케 함.  
        hp = f_hitPoint - hitPoint;
        hitPoint += hp;
    }
    else { hitPoint += hp; }    
    cout << endl << name << "의 체력이 " << hp << " 회복됐다!" << endl;
}
void Pokemon::addAtk(int atk) {
    attackPoint += atk;
    cout << endl << name << "의 공격이 " << atk << " 올랐다!" << endl;
}
void Pokemon::addDef(int def) {
    defencePoint += def;
    cout << endl << name << "의 방어가 " << def << " 올랐다!" << endl;
}
void Pokemon::addSpd(int spd) {
    speed += spd;
    cout << endl << name << "의 스피드가 " << spd << " 올랐다!" << endl;
}

float Pokemon::typeSnW(PokemonType::type t) {
    return ((type1 != PokemonType::NONE) ? typeChart[t][type1] : 1) * ((type2 != PokemonType::NONE) ? typeChart[t][type2] : 1);
}

void Pokemon::damaged(int d) {
    if (hitPoint - d < 0) {
        hitPoint = 0;
    }
    else { hitPoint -= d; }
    cout << endl << name << "은(는) " << d << "의 대미지를 입었다!" << endl;

    if (hitPoint <= 0) {
        setDeactive();
    }
}

void Pokemon::displayHP(int d) { //양수일 경우 회복, 음수일 경우 대미지 
    const int fullHP = f_hitPoint;
    int HP = hitPoint; 

    const char bar = '-';
    const char blank = ' ';
    const int len = 20;
    const int speed = 50;
    int dest = HP + d; //목표치 
    float tick = (float)100 / len;
    int destBarCount;
    int curBarCount;
    float percent;

    if (dest > fullHP) { dest = fullHP; }
    else if (dest < 0) { dest = 0; }

    percent = (float)dest / fullHP * 100;
    if (percent > 0 && percent < 1) { percent = 1; } //1 미만 0 초과의 값을 0으로 표기하지 않도록 
    destBarCount = percent / tick;
    curBarCount = ((float)HP / fullHP * 100) / tick;
    if (curBarCount == 0 && HP > 0) { curBarCount = 1; }

    //cout << dest << " " << fullHP << " " << percent << " " << tick << " " << destBarCount << " " << curBarCount << endl;

    cout << name << "    [";
    //베이스 출력 
    if (curBarCount > len * 0.9) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //Green
    }
    else if (curBarCount > len * 0.51) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); //Light Green
    }
    else if (curBarCount > len * 0.35) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //Light Yellow
    }
    else if (curBarCount > len * 0.25) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //Yellow
    }
    else if (curBarCount > len * 0.15) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //Light Red
    }
    else if (curBarCount > 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //Red
    }
    else if (curBarCount <= 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); //Gray
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); //Gray
    }
    for (int i = 0; i < len; ++i) {
        if (i < curBarCount) { cout << bar; }
        else { cout << blank; }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "]";

    //cout << "       " << curBarCount << "/" << destBarCount << "       ";

    while (curBarCount != destBarCount) {
        cout << "\r";
        if (curBarCount > destBarCount) {
            //감소 
            --curBarCount;
        }
        else if (curBarCount < destBarCount) {
            //증가 
            ++curBarCount;
        }
        else { /*동일*/ }

        cout << name << "    [";
        
        if (curBarCount > len * 0.9) { 
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //Green
        }
        else if (curBarCount > len * 0.51) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); //Light Green
        }
        else if (curBarCount > len * 0.35) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //Light Yellow
        }
        else if (curBarCount > len * 0.25) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); //Yellow
        }
        else if (curBarCount > len * 0.15) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //Light Red
        }
        else if (curBarCount > 0) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //Red
        }
        else if (curBarCount <= 0) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); //Gray
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); //Gray
        }
        for (int i = 0; i < len; ++i) {
            if (i < curBarCount) { cout << bar; }
            else { cout << blank; }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "]";
        //cout << "       " << curBarCount << "/" << destBarCount << "       ";
        Sleep(500);
    }
    HP = dest;
}

void Pokemon::coloredName() {
    if (hitPoint > f_hitPoint * 0.9) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //Green
        cout << name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    else if (hitPoint > f_hitPoint * 0.51) {
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