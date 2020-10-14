#include "pokemon.hpp"
#include <iostream>
#include <fstream>
using namespace std;

Pokemon::Pokemon(string species)
{
    this->species = species;

    ifstream inp("../data/pokemon.txt");
    if(!inp.is_open())
    {
        cout << "Error: Could not find pokemon.txt.\n";
        exit(0);
    }

    string stat_line;
    bool error = true;
    while(getline(inp, stat_line))
    {
        if(species + " " == stat_line.substr(0, species.length() + 1))
        {
            error = false;
            break;
        }
    }
    if(error)
    {
        cout << "Error: Could not find the pokemon \"" + species + "\" in pokemon.txt.";
        exit(0);
    }

    string type_info = stat_line.substr(species.length() + 1, 5);
    types.push_back((Type)stoi(type_info.substr(0, 2)));
    if(type_info[3] != 'X')
    {
        types.push_back((Type)stoi(type_info.substr(3, 2)));
    }

    for(int i = species.length() + 7; i < stat_line.length(); i+=4)
    {
        base_stats.push_back(stoi(stat_line.substr(i, 3)));
    }
}

void Pokemon::calc_final_stats()
{
    current_HP = HP = ((2 * base_stats[0] + IVs[0] + EVs[0]/4) * LEVEL)/100 + LEVEL + 10;

    vector<int*> calcHandler = {&ATK, &DEF, &SP_ATK, &SP_DEF, &SPD};
    for(int i = 1; i < 6; i++)
    {
        *calcHandler[i-1] = ((2 * base_stats[i] + IVs[i] + EVs[i]/4) * LEVEL)/100 + 5;
    }

    if(NAT % 5 != NAT / 5)
    {
        *calcHandler[NAT % 5] *= 0.9;
        *calcHandler[NAT / 5] *= 1.1;
    }
}