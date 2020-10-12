#pragma once

#include <vector>
#include <string>
#include "main.hpp"
using namespace std;

class Pokemon_Species
{
public:
    Pokemon_Species(string species);
private:
    string species;
    int HP;
    int ATK;
    int SP_ATK;
    int DEF;
    int SP_DEF;
    int SPD;
    vector<string> possibleAbilities;
};

class Pokemon : private Pokemon_Species
{
public:
    Pokemon();
private:
    string ability;
    nature NAT;
    gender GEN;
};