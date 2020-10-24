#pragma once
#include <vector>
#include <string>
#include "trainer.hpp"
using namespace std;

class Battle
{
public:
    Battle(string input1, string input2);
    void take_commands();
    void turn(int x);
    bool faint_check(int x);
    string active_pkmn_name(int x) {return t[x].get_active_pokemon()->get_species();}
    string active_pkmn_img(int x) {return "img/Battlers/" + t[x].get_active_pokemon()->get_dex_num() + ((x == 0) ? "b" : "") + ".png";}
    int active_pkmn_hp_percent(int x) {return (t[x].get_active_pokemon()->get_current_HP() * 100) / t[x].get_active_pokemon()->get_HP();}
private:
    vector<Trainer> t;
    vector<vector<float>> matchups;
    vector<string> commands;
    void initialise_type_matchups();
};