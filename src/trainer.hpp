#pragma once

#include "pokemon.hpp"
#include "main.hpp"
#include <vector>

class Trainer
{
public:
    Trainer(string input);
    Pokemon* get_active_pokemon() {return &Team[active_pokemon];}
    void switch_active_pokemon(int num) {active_pokemon = num;}
    void calc_damage(Pokemon *defender, int move);
private:
    vector<Pokemon> Team;
    int active_pokemon;
};