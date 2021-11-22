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
    PokemonType::type type1, type2;
    Skill skill[4]; //기술 라인 번호
    string master; //마스터 이름
    float typeChart[17][17] = {
        //NOR-FIR-WAT-ELE-GRA/ICE-FIG-POI-GRO-FLY/PSY-BUG-ROC-GHO-DRA/DAR-STE  DEF // ATK
            1,1,1,1,1,          1,1,1,1,1,          1,1,0.5,0,1,        1,0.5,      //NORMAL
            1,0.5,0.5,1,2,      2,1,1,1,1,          1,2,0.5,1,0.5,      1,2,        //FIRE
            1,2,0.5,1,0.5,      1,1,1,2,1,          1,1,2,1,0.5,        1,1,        //WATER
            1,1,2,0.5,0.5,      1,1,1,0,2,          1,1,1,1,0.5,        1,1,        //ELECTRIC
            1,0.5,2,1,0.5,      1,1,0.5,2,0.5,      1,0.5,2,1,0.5,      1,0.5,      //GRASS
            1,0.5,0.5,1,2,      0.5,1,1,2,2,        1,1,1,1,2,          1,0.5,      //ICE
            2,1,1,1,1,          2,1,0.5,1,0.5,      0.5,0.5,2,0,1,      2,2,        //FIGHTING
            1,1,1,1,2,          1,1,0.5,0.5,1,      1,1,0.5,0.5,1,      1,0,        //POISON
            1,2,1,2,0.5,        1,1,2,1,0,          1,0.5,2,1,1,        1,2,        //GROUND
            1,1,1,0.5,2,        1,2,1,1,1,          1,2,0.5,1,1,        1,0.5,      //FLYING
            1,1,1,1,1,          1,2,2,1,1,          0.5,1,1,1,1,        0,0.5,      //PSYCHIC
            1,0.5,1,1,2,        1,0.5,0.5,1,0.5,    2,1,1,0.5,1,        2,0.5,      //BUG
            1,2,1,1,1,          2,0.5,1,0.5,2,      1,2,1,1,1,          1,0.5,      //ROCK
            0,1,1,1,1,          1,1,1,1,1,          2,1,1,2,1,          0.5,0.5,    //GHOST
            1,1,1,1,1,          1,1,1,1,1,          1,1,1,1,2,          1,0.5,      //DRAGON
            1,1,1,1,1,          1,0.5,1,1,1,        2,1,1,2,1,          0.5,0.5,    //DARK
            1,0.5,0.5,0.5,1,    2,1,1,1,1,          1,1,2,1,1,          1,0.5       //STEEL

    };

    public:
        Pokemon();
        Pokemon(string nm, int exp, int fhp, int atk, int def, int spd, PokemonType::type t1, PokemonType::type t2, Skill* skill[4], string mst);
        Pokemon(string nm, int exp, int fhp, int atk, int def, int spd, PokemonType::type t1, PokemonType::type t2, Skill s1, Skill s2, Skill s3, Skill s4, string mst);

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

        float typeSnW(PokemonType::type t); //타입 상성 Strength and Weakness
        void damaged(int d); //대미지

        void displayHP(int d);
        void coloredName();
};