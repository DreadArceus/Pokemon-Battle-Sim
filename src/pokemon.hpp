#pragma once

#include <vector>
#include <string>
#include "main.hpp"
#include "move.hpp"
using namespace std;

class Pokemon
{
public:
    Pokemon(string species);

    void set_EVs(vector<int> EVs) {this->EVs = EVs;}
    void set_IVs(vector<int> IVs) {this->IVs = IVs;}
    void set_nature(nature NAT) {this->NAT = NAT;}
    void set_move(Move m) {this->moves.push_back(m);}
    void set_gender(gender GEN) {this->GEN = GEN;}
    void calc_final_stats();

    string get_species() {return species;}
    string get_dex_num() {return dex_num;}
    vector<Type> get_types() {return types;}
    vector<int> get_base_stats() {return base_stats;}
    nature get_nature() {return NAT;}
    gender get_gender() {return GEN;}
    int get_HP() {return HP;}
    int get_ATK() {return ATK;}
    int get_DEF() {return DEF;}
    int get_SP_ATK() {return SP_ATK;}
    int get_SP_DEF() {return SP_DEF;}
    int get_SPD() {return SPD;}

    int get_current_HP() {return current_HP;}
    Move get_move(int num) {return moves[num];}
    void take_damage(int dmg) {current_HP -= ((current_HP > dmg) ? dmg : current_HP);}
private:
    string species;
    string dex_num;
    vector<Type> types;
    vector<int> base_stats;

    vector<int> EVs;
    vector<int> IVs;
    nature NAT;
    gender GEN;

    int HP;
    int ATK;
    int DEF;
    int SP_ATK;
    int SP_DEF;
    int SPD;

    int current_HP;
    vector<Move> moves;
};