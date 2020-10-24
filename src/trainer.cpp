#include "main.hpp"
#include "move.hpp"
#include "pokemon.hpp"
#include "trainer.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
using namespace std;

Trainer::Trainer(string input)
{
    ifstream party("data/" + input);
    if(!party.is_open())
    {
        cout << "Error: Trainer input file \"" + input + "\" not found.\n";
        exit(0);
    }

    for(int i = 0; i < MAX_PARTY_SIZE; i++)
    {
        string info;
        getline(party, info);
        Pokemon x(info.substr(0, info.find(' ')));

        int m = info.find(' ') + 1;
        vector<int> IVs;
        for(int j = 0; j < 6; j++)
        {
            IVs.push_back(stoi(info.substr(m, 2)));
            m += 3;
        }
        x.set_IVs(IVs);

        vector<int> EVs;
        for(int j = 0; j < 6; j++)
        {
            EVs.push_back(stoi(info.substr(m, 3)));
            m += 4;
        }
        x.set_EVs(EVs);

        x.set_nature(nature(stoi(info.substr(m, 2))));

        x.calc_final_stats();

        m += 3;
        int n = m;
        while(m < info.length())
        {
            if(info[m] == '/')
            {
                x.set_move(Move(info.substr(n, m - n)));
                n = m + 1;
            }
            m++;
        }
        if(m == info.length())
        {
            x.set_move(Move(info.substr(n, m - n)));
        }

        Team.push_back(x);
    }

    active_pokemon = 0;
}

void Trainer::calc_damage(Pokemon *defender, int move, vector<vector<float>> matchups)
{
    Move m = Team[active_pokemon].get_move(move);

    srand(time(0));
    if(rand() % 100 + 1 <= m.get_ACC()) //Roll for hitting
    {
        int damage = 0;
        if(m.get_CAT() == 0)
        {
            damage = ((((2 * LEVEL)/5 + 2) * m.get_POW() * Team[active_pokemon].get_ATK())/(defender->get_DEF() * 50)) + 2;
        }
        else if(m.get_CAT() == 1)
        {
            damage = ((((2 * LEVEL)/5 + 2) * m.get_POW() * Team[active_pokemon].get_SP_ATK())/(defender->get_SP_DEF() * 50)) + 2;
        }

        damage *= double(rand() % 16 + 85)/100; //random modifier

        if(rand() % 24 == 0) //1 in 24 or 4.167% chance
        {
            damage *= 1.5; //Critical Hit
        }

        for(Type t : Team[active_pokemon].get_types()) //STAB
        {
            if(t == m.get_type())
            {
                damage *= 1.5;
            }
        }
        for(Type t : defender->get_types()) //For type advantage/disadvantage
        {
            damage *= matchups[m.get_type()][t];
        }

        defender->take_damage(damage);
    }
}