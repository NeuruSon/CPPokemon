#define _HAS_STD_BYTE 0
#pragma once
#include <string>
#include "Skill.h"
using namespace std;

class Pokemon {
    bool active;
    string name; //포켓몬 이름(디폴트: 종)
    int experience; //경험치로 하려고 했는데 사정상 레벨로 사용함 
    int f_hitPoint; //최대 체력
    int hitPoint; //체력
    int attackPoint; //공격
    int defencePoint; //방어 
    int speed;
    string type[2];
    Skill skill[4]; //기술 라인 번호
    string master; //마스터 이름

    public:
        Pokemon();
        Pokemon(string nm, int exp, int fhp, int atk, int def, int spd, string type[2], Skill* skill[4], string mst);
        Pokemon(string nm, int exp, int fhp, int atk, int def, int spd, string type[2], Skill s1, Skill s2, Skill s3, Skill s4, string mst);
        Pokemon(string nm, int exp, int fhp, int atk, int def, int spd, string type1, string type2, Skill s1, Skill s2, Skill s3, Skill s4, string mst);

        void setName(string nm);
        void setExp(int exp);
        void setFHp(int fhp);
        void setHp(int hp);
        void setAtk(int atk);
        void setDef(int def);
        void setSpd(int spd);
        void setMaster(string mst);

        void setActive();
        void setDeactive();

        string getName();
        int getExp(); 
        int getFHp();
        int getHp();
        int getAtk();
        int getDef();
        int getSpd();
        string getMaster();
        Skill getSkill(int num);

        bool isActive();

        void addExp(int exp); //경험치 획득
        void addFHp(int fhp); //최대 체력 증가
        void addHp(int hp); //체력 회복
        void addAtk(int atk); //공격력 증가
        void addDef(int def); //방어력 증가
        void addSpd(int spd); //스피드 증가, 일정 턴 후 종료

        void damaged(int d); //대미지

        void printInfo();
        void coloredName();
};