#pragma once

#include <vector>
#include <string>
#include "pokemon.hpp"

class Trainer
{
public:
    Trainer(string input);
    Pokemon* get_active_pokemon() {return &Team[active_pokemon];}
    void switch_active_pokemon(int num) {active_pokemon = num;}
    void calc_damage(Pokemon *defender, int move, vector<vector<float>> matchups);
private:
    vector<Pokemon> Team;
    int active_pokemon;
};