﻿#define _HAS_STD_BYTE 0
#include "Pokemon.h"
#include "Trainer.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#pragma comment(lib, "Winmm.lib")
using namespace std;

enum State {
    //얼마나 세분화? 
    //진행, 수 고민중, 끝?
    STATE_BATTLE,
    STATE_BATTLE_END
};

enum TrainerType {
   TRAINERTYPE_PLAYER, //플레이어 
   TRAINERTYPE_CHAMPION, //챔피언
   TRAINERTYPE_VILLAIN, //빌런
   TRAINERTYPE_VILLAINMASTER, //빌런 우두머리
   TRAINERTYPE_TRAINER, //일반 포켓몬 트레이너
   TRAINERTYPE_NONTRAINER //야생 포켓몬
};

enum PokemonType {
    POKEMONTYPE_NORMAL, //노말
    POKEMONTYPE_FIRE, //불꽃
    POKEMONTYPE_WATER, //물
    POKEMONTYPE_GRASS, //풀
    POKEMONTYPE_ELECTRIC, //전기
    POKEMONTYPE_ICE, //얼음
    POKEMONTYPE_FIGHTING, //격투
    POKEMONTYPE_POISON, //독
    POKEMONTYPE_FLYING, //비행 
    POKEMONTYPE_PSYCHIC, //에스퍼
    POKEMONTYPE_BUG, //벌레
    POKEMONTYPE_ROCK, //바위
    POKEMONTYPE_GHOST, //고스트
    POKEMONTYPE_DRAGON, //드래곤
    POKEMONTYPE_DARK, //악
    POKEMONTYPE_STEEL //강철
};

//수정한 대미지 = (((레벨*2/5)+2)*위력*공격/50)/방어*랜덤수/100
int damage(Pokemon* a, Pokemon* na, int p) { 
    int d = 0;
    int randNum = rand()%16 + 85; // 85~100
    d = (((a->getExp() * 2 / 5) + 2) * p * a->getAtk() / 50) / na->getDef() * randNum / 100;
    return d;
}

//포켓몬 교체
Pokemon* changePkm(Trainer &t, Pokemon* p) {
    int changeNum = -1;
    while (changeNum == -1) {
        cout << endl << "누구를 내보낼까?" << endl;
        cout << "  [1] "; t.getPkm(0)->coloredName();
        cout << "  [2] "; t.getPkm(1)->coloredName();
        cout << "  [3] "; t.getPkm(2)->coloredName();
        cout << "  [4] "; t.getPkm(3)->coloredName();
        cout << "  [5] "; t.getPkm(4)->coloredName();
        cout << "  [6] "; t.getPkm(5)->coloredName();
        cout << endl << "  >>> ";
        cin >> changeNum;

        if (changeNum > 6 || changeNum < 1) {
            cout << endl << "오박사: " << t.getName() << ", " << changeNum << "은(는) 잘못된 수같다!" << endl; 
            Sleep(1000);
            cout << "데리고 있는 포켓몬 중에서 내보내렴." << endl;
            Sleep(1000);
            changeNum = -1;
            continue;
        }
        else if (t.getPkm(changeNum-1)->isActive() == false) {
            cout << t.getPkm(changeNum-1)->getName() << "은(는) 움직일 수 없다!" << endl;
            Sleep(1000);
            changeNum = -1;
            continue;
        }
    }

    cout << endl << p->getName() << " 돌아와!" << endl;
    Sleep(1500);
    cout << "가랏! " << t.getPkm(changeNum-1)->getName() << "!" << endl;
    Sleep(1000);
    return t.getPkm(changeNum-1);
}

Pokemon* changePkm_cham(Trainer &c, Pokemon* cp, int n) {
    int changeNum = n;
    Sleep(1500);
    cout << endl << c.getName() << "은(는) " << c.getPkm(changeNum-1)->getName() << "을(를) 내보냈다!" << endl;
    Sleep(1000);
    return c.getPkm(changeNum-1);
}

void knockdown(Pokemon* p1, Pokemon* p2, Trainer& t, Trainer& c) {
    Sleep(1000);
    if (t.getAlivePkmCount() > 0 && c.getAlivePkmCount() > 0) {
        if (p1->isActive() == false) {
            Sleep(1000);
            p1 = changePkm(t, p1);
        }
        if (p2->isActive() == false) {
            Sleep(1000);
            p2 = changePkm_cham(c, p2, 5);
        }
    }
    else {
        return;
    }
}

//행동
void action(Trainer &t, Pokemon* a, Pokemon* na, int n) {
    if (n < 5 && n > 0) {
        string skillName = a->getSkill(n-1).getName();
        int power = a->getSkill(n-1).getPw();

        if (a->getHp() > 0 && na->getHp() > 0) {
            Sleep(1000);
            cout << endl << a->getName() << "의 " << skillName << "!" << endl;
            Sleep(1000);
            na->damaged(damage(a, na, power));
        }
    }
    else if (n == 5) {
        cout << endl << t.getName() << "은(는) 풀 상처약을 사용했다!" << endl; //item의 경우 무조건 선제 사용 
        a->addHp(a->getFHp());
    }
    //else if (n == 6) { //포켓몬 교체
    //    a = changePkm(t, a); 
    //}
    //else if (n == 7) { //챔피언 포켓몬 교체 
    //    cout << t.getName() << "은(는) " << a->getName() << "을(를) 넣어버렸다!" << endl;
    //    //챔피언 포켓몬 교체 알고리즘
    //    a = changePkm_cham(t, a, 3);
    //}
    else {} //n = 0
}

//전반적인 모든 것 처리. 특히 우선도 관련. 
void battle(Trainer &t, Trainer &c) {
    Pokemon* p = t.getPkm(0);
    Pokemon* cp = c.getPkm(0);
    int pPr, cpPr;

    {
        PlaySound(TEXT("2_67.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        cout << c.getName() << "이 승부를 걸어왔다!" << endl;
        Sleep(3000);
        cout << c.getName() << "은 " << cp->getName() << "을(를) 내보냈다!" << endl;
        Sleep(1000);
        cout << "가랏! " << p->getName() << "!" << endl;
        Sleep(1000);
    }

    int todoNum = 9;
    while (p->getHp() > 0 && cp->getHp() > 0) { //조건: 둘 다 전투가능 상태라면 계속 진행 
        char todo = '9';
        Sleep(1000);
        cout << endl; p->coloredName();
        cout << " " << p->getHp() << " / " << p->getFHp() << "\t\t"; cp->coloredName();
        cout << endl << p->getName() << "은(는) 무엇을 할까?" << endl <<
            "[0] " << "도망간다" <<
            "  [1] " << p->getSkill(0).getName() <<
            "  [2] " << p->getSkill(1).getName() <<
            "  [3] " << p->getSkill(2).getName() <<
            "  [4] " << p->getSkill(3).getName() <<
            "  [5] " << "회복" <<
            "  [6] " << "포켓몬교체" <<
            endl << "  >>> ";
        cin >> todo; 

        pPr = 0; cpPr = 0;

        switch (todo) {
        case '0': //quit
            cout << t.getName() << ", 배틀에서 등을 보일 수는 없어!" << endl;
            continue;
        case '1': case '2': case '3': case '4': case '5': case '6':
            todoNum = todo - '0';
            break;
        default:
            cout << t.getName() << ", 포기하지 말고 정정당당히 배틀에 임하자!" << endl;
            continue;
        }

        //선제판단 및 액션
        bool isPFirst = false;

        //챔피언 행동 알고리즘 
        int cTodoNum = 0;
        float cpHP_f = cp->getHp();
        if (cpHP_f / cp->getFHp() < 0.15) { //체력이 어느정도 떨어지면 포켓몬당 1회 회복 or 교체
            cTodoNum = 5;
            //수정 필요!!
        }
        else { //체력 충분할 때는 공격만 
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> randomNum(1, 4);
            cTodoNum = randomNum(rd);
        }

        //플레이어 우선도 
        if (todoNum < 5 && todoNum > 0) { pPr += p->getSkill(todoNum - 1).getPr(); }
        else if (todoNum == 5 || todoNum == 6) { pPr += 6; }
        else {}

        //챔피언 우선도 
        if (cTodoNum < 5 && cTodoNum > 0) { cpPr += cp->getSkill(cTodoNum - 1).getPr(); }
        else if (cTodoNum == 5 || cTodoNum == 6) { cpPr += 6; }
        else {}

        //우선도 비교
        if (pPr == cpPr) { //같으면 
            if (p->getSpd() > cp->getSpd()) { isPFirst = true; } //스피드 비교 
            else { isPFirst = false; } //플레이어의 스피드가 느리거나 둘이 같다면 챔피언 선제
        }
        else if (pPr > cpPr) { isPFirst = true; } //플레이어가 우선이라면 
        else { isPFirst = false; } //챔피언이 우선이라면 

        //턴 전반
        if (isPFirst == true && p->isActive() == true) { //플레이어 선공
            if (todoNum < 6) { action(t, p, cp, todoNum); }
            else { p = changePkm(t, p); }
        } 
        else if (isPFirst == false && cp->isActive() == true) { //챔피언 선공 
            if (cTodoNum < 6) { action(c, cp, p, cTodoNum); }
            else { 
                //챔피언 포켓몬 교체 알고리즘 
                cp = changePkm_cham(c, cp, 3); 
            }
        } 
        p->coloredName(); cout << " " << p->getHp() << " / " << p->getFHp() << "\t\t"; cp->coloredName(); cout << endl;

        //쓰러졌다면 교체
        knockdown(p, cp, t, c);

        //턴 후반
        if (isPFirst == false && p->isActive() == true) { //플레이어 후공
            if (todoNum < 6) { action(t, p, cp, todoNum); }
            else { p = changePkm(t, p); }
        }
        else if (isPFirst == true && cp->isActive() == true) { //챔피언 후공
            if (cTodoNum < 6) { action(c, cp, p, cTodoNum); }
            else {
                //챔피언 포켓몬 교체 알고리즘 
                cp = changePkm_cham(c, cp, 3);
            }
        }
        p->coloredName(); cout << " " << p->getHp() << " / " << p->getFHp() << "\t\t"; cp->coloredName(); cout << endl;

        //쓰러졌다면 교체 
        knockdown(p, cp, t, c);
    }

    //승패
    if (t.getAlivePkmCount() > 0 && c.getAlivePkmCount() <= 0) { //승리 
        PlaySound(TEXT("2_68.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        cout << c.getName() << "과의 승부에서 이겼다!" << endl << endl; Sleep(2000);
        cout << "… 조금 전까지 너는 최강의 도전자였다" << endl; Sleep(2000);
        cout << "그리고 지금은 최고의 포켓몬 트레이너로서 챔피언이 된 거야" << endl; Sleep(3000);
        cout << "축하해 새로운 챔피언 " << t.getName() << endl; Sleep(3000);
        t.changeMny(12500);
        cout << endl << t.getName() << "은(는) 상금으로 12500원을 손에 넣었다!" << endl << endl; 
        cout << endl << endl << endl << "----------------------------------------------------------" << endl << "끝까지 난천을 이겨보질 못해서 만들어봤습니다 감사합니다" << endl << endl << endl;
        system("pause");
    }
    else if (t.getAlivePkmCount() > 0 && c.getAlivePkmCount() <= 0) { //패배 
        cout << t.getName() << "에게는 싸울 수 있는 포켓몬이 없다!" << endl; Sleep(1000);
        int money = t.getMny();
        if (money >= 6250) { money = 6250; } //소지금이 지불금 이상이면 money를 지불금으로 변화
        t.changeMny(-1 * money); //지불
        cout << t.getName() << "은(는) 상금으로 " << money << "원을 지불했다" << endl; Sleep(1000);
        cout << "… … … …" << endl; Sleep(1000);
        cout << t.getName() << "은(는) 눈앞이 캄캄해졌다!" << endl << endl; Sleep(1000);
    }
    else { cout << "몬가... 몬가 잘못댓슴......" << endl; }
}

void loadSkills(Skill s[38]) {
    //줄별로 읽고, 해당 줄에서 다시 나눠주기. 
    string ta[7];
    string temp;
    int i = 0;
    ifstream skillsCSV("skillTable.csv", ios::in | ios::out);
    if (!skillsCSV.is_open()) {
        cout << "none" << endl;
    }
    else { 
        cout << "loading skills..." << endl;
        while (!skillsCSV.eof()) {
            getline(skillsCSV, temp);
            stringstream tempSS(temp);
            int j = 0;
            while (getline(tempSS, temp, ',')) {
                ta[j] = temp;
                j++;
            }
            if (ta[2] == "-") { ta[2] = "0"; }
            if (ta[3] == "-") { ta[3] = "100"; }
            s[i] = Skill(ta[0], ta[1], stoi(ta[2]), stoi(ta[3]), stoi(ta[4]), stoi(ta[5]), ta[6]);
            ++i;
        }
        cout << "skill load complete..." << endl;
        skillsCSV.close();
    }
}

void loadPokemon(Pokemon p[6], string code, Skill s[]) {
    if (code == "챔피언 난천") {
        p[0] = Pokemon("화강돌", 61, 143, 92, 108, 35, "고스트", "악", s[19], s[15], s[26], s[1], "챔피언 난천");
        p[1] = Pokemon("로즈레이드", 60, 152, 70, 55, 90, "풀", "독", s[17], s[16], s[22], s[20], "챔피언 난천");
        p[2] = Pokemon("토게키스", 60, 182, 50, 95, 80, "노말", "비행", s[33], s[21], s[11], s[28], "챔피언 난천");
        p[3] = Pokemon("루카리오", 63, 173, 110, 70, 90, "격투", "강철", s[33], s[24], s[30], s[15], "챔피언 난천");
        p[4] = Pokemon("밀로틱", 63, 204, 60, 79, 81, "물", "-", s[11], s[12], s[5], s[32], "챔피언 난천");
        p[5] = Pokemon("한카리아스", 66, 231, 130, 95, 102, "드래곤", "땅", s[6], s[30], s[3], s[2], "챔피언 난천");
    }
    else {
        p[0] = Pokemon("초염몽", 72, 206, 104, 71, 108, "불꽃", "격투", s[14], s[37], s[8], s[35], code);
        p[1] = Pokemon("펄기아", 56, 176, 120, 100, 100, "물", "드래곤", s[0], s[11], s[25], s[7], code);
        p[2] = Pokemon("루카리오", 60, 164, 120, 80, 89, "격투", "강철", s[13], s[33], s[27], s[24], code);
        p[3] = Pokemon("라프라스", 61, 240, 85, 80, 60, "물", "얼음", s[5], s[36], s[11], s[10], code);
        p[4] = Pokemon("포푸니라", 59, 162, 120, 65, 125, "악", "얼음", s[3], s[19], s[9], s[29], code);
        p[5] = Pokemon("갸라도스", 70, 227, 125, 79, 81, "물", "비행", s[23], s[26], s[31], s[34], code);
    }
}

string& trim(string& s, const char* t = " ") {
    s = s.erase(0, s.find_first_not_of(t));
    s = s.erase(s.find_last_not_of(t) + 1);
    return s;
}

int main() {
    Skill skills[38];
    loadSkills(skills);
    Pokemon p1[6]; 
    Pokemon p2[6];

    string playerName = "플레이어";

    {
        PlaySound(TEXT("2_66.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        cout << "[플레이 방법]" << endl << " []안의 숫자를 입력 후 엔터를 누르면 진행됩니다" << endl << "----------------------------------------------------------" << endl << endl;
        Sleep(1000);

        cout << "난천: 잘 있었어?" << endl; Sleep(1000);
        cout << "맞다 천관산에서 있었던 일은 고맙게 생각하고 있어" << endl; Sleep(1000);
        cout << "어떤 어려움에 부딪혀도 포켓몬과 함께 이겨냈구나" << endl; Sleep(1000);
        cout << "그것은 언제나 자기 자신을 이겨왔다는 것" << endl; Sleep(1000);
        cout << "그렇게 해서 강해졌다는 걸 너희들에게서 느낄 수 있어!" << endl; Sleep(1000);
        cout << "자 그럼! 여기에 온 목적은 알고 있어!" << endl; Sleep(1000);
        cout << "용맹한 트레이너, 네 이름을 여기 적어줘." << endl; Sleep(1000);
    }
    cout << endl << "당신의 이름은?" << endl << "  >>> ";
    getline(cin, playerName);
    {
        playerName = trim(playerName);
        Sleep(1000);
        cout << endl << "좋아, 준비는 끝났네." << endl; Sleep(1000);
        cout << playerName << ", 포켓몬리그 챔피언으로서 너와 시합하겠어!" << endl << endl; Sleep(2000);
    }

    loadPokemon(p1, playerName, skills);
    loadPokemon(p2, "챔피언 난천", skills);

    Trainer t(playerName, 12000, p1);
    Trainer c("챔피언 난천", 14000, p2);

    battle(t, c);

    return 0;
}