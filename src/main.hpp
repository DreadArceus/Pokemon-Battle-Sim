#pragma once
#include <vector>
#define MAX_PARTY_SIZE 6
#define LEVEL 50

enum gender
{
    Male, Female,
    Genderless
};

enum nature
{
    //Attack Up
    Hardy, Lonely, Adamant, Naughty, Brave,
    //Defense Up
    Bold, Docile, Impish, Lax, Relaxed,
    //Sp. Attack Up
    Modest, Mild, Bashful, Rash, Quiet,
    //Sp. Defense Up
    Calm, Gentle, Careful, Quirky, Sassy,
    //Speed Up
    Timid, Hasty, Jolly, Naive, Serious
};

enum Type
{
    Normal, Fighting, Flying, Poison, Ground, Rock, Bug, Ghost, Steel, Fire,
    Water, Grass, Electric, Psychic, Ice, Dragon, Dark, Fairy
};
std::vector<std::vector<float>> matchups;

enum Category
{
    Physical, Special, Status
};