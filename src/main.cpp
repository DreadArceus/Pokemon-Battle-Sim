//To-Do: Items, Abilities, Status Moves/Modifiers/Conditions, GUI
#include <iostream>
#include <vector>
#include "main.hpp"
#include "pokemon.cpp"
#include "trainer.cpp"
#include "move.cpp"
using namespace std;

void inintialise_type_matchups()
{
    for(int i = 0; i < 18; i++)
    {
        vector<float> v(18, 1);
        matchups.push_back(v);
    }
    //Normal:
    matchups[0][5] = matchups[0][8] = 0.5;
    matchups[0][7] = 0;
    //Fighting:
    matchups[1][0] = matchups[1][5] = matchups[1][8] = matchups[1][14] = matchups[1][16] = 2;
    matchups[1][2] = matchups[1][3] = matchups[1][6] = matchups[1][13] = matchups[1][17] = 0.5;
    matchups[1][7] = 0;
    //Flying:
    matchups[2][1] = matchups[2][6] = matchups[2][11] = 2;
    matchups[2][5] = matchups[2][8] = matchups[2][12] = 0.5;
    //Poison:
    matchups[3][11] = matchups[3][17] = 2;
    matchups[3][3] = matchups[3][4] = matchups[3][5] = matchups[3][7] = 0.5;
    matchups[3][8] = 0;
    //Ground:
    matchups[4][3] = matchups[4][5] = matchups[4][8] = matchups[4][9] = matchups[4][12] = 2;
    matchups[4][6] = matchups[4][11] = 0.5;
    matchups[4][2] = 0;
    //Rock:
    matchups[5][2] = matchups[5][6] = matchups[5][9] = matchups[5][14] = 2;
    matchups[5][1] = matchups[5][4] = matchups[5][8] = 0.5;
    //Bug:
    matchups[6][11] = matchups[6][13] = matchups[6][16] = 2;
    matchups[6][1] = matchups[6][2] = matchups[6][3] = matchups[6][7] = matchups[6][8] = matchups[6][9] = matchups[6][17] = 0.5;
    //Ghost:
    matchups[7][7] = matchups[7][13] = 2;
    matchups[7][16] = 0.5;
    matchups[7][0] = 0;
    //Steel:
    matchups[8][5] = matchups[8][14] = matchups[8][17] = 2;
    matchups[8][8] = matchups[8][9] = matchups[8][10] = matchups[8][12] = 0.5;
    //Fire:
    matchups[9][6] = matchups[9][8] = matchups[9][11] = matchups[9][14] = 2;
    matchups[9][5] = matchups[9][9] = matchups[9][10] = matchups[9][15] = 0.5;
    //Water:
    matchups[10][4] = matchups[10][5] = matchups[10][9] = 2;
    matchups[10][10] = matchups[10][11] = matchups[10][15] = 0.5;
    //Grass:
    matchups[11][4] = matchups[11][5] = matchups[11][10] = 2;
    matchups[11][2] = matchups[11][3] = matchups[11][6] = matchups[11][8] = matchups[11][9] = matchups[11][11] = matchups[11][15] = 0.5;
    //Electric:
    matchups[12][2] = matchups[12][10] = 2;
    matchups[12][11] = matchups[12][12] = matchups[12][15] = 0.5;
    matchups[12][4] = 0;
    //Psychic:
    matchups[13][1] = matchups[13][3] = 2;
    matchups[13][8] = matchups[13][13] = 0.5;
    matchups[13][16] = 0;
    //Ice:
    matchups[14][2] = matchups[14][4] = matchups[14][11] = matchups[14][15] = 2;
    matchups[14][8] = matchups[14][9] = matchups[14][10] = 0.5;
    //Dragon:
    matchups[15][15] = 2;
    matchups[15][8] = 0.5;
    matchups[15][17] = 0;
    //Dark:
    matchups[16][7] = matchups[16][13] = 2;
    matchups[16][1] = matchups[16][16] = matchups[16][17] = 0.5;
    //Fairy:
    matchups[17][1] = matchups[17][15] = matchups[17][16] = 2;
    matchups[17][3] = matchups[17][8] = matchups[17][9] = 0.5;
}

vector<Trainer> ts = {Trainer("trainer1.txt"), Trainer("trainer2.txt")};
vector<Pokemon*> APs = {ts[0].get_active_pokemon(), ts[1].get_active_pokemon()};

void turn(int t, string command)
{
    if(APs[t]->get_current_HP() > 0)
    {
        if(command[0] == 'M')
        {
            ts[t].calc_damage(APs[((t == 0) ? 1 : 0)], command[1] - '0' - 1);
        }
        if(command[0] == 'S')
        {
            ts[t].switch_active_pokemon(command[1] - '0' - 1);
            APs[t] = ts[t].get_active_pokemon();
        }
    }
}

bool faint_check(int t)
{
    if(APs[t]->get_current_HP() <= 0)
    {
        cout << "\nFainted, choose next: ";
        int x = 0;
        cin >> x;
        ts[t].switch_active_pokemon(x - 1);
        APs[t] = ts[t].get_active_pokemon();
        return true;
    }
    return false;
}

int main()
{
    inintialise_type_matchups();

    string command0, command1;
    while(true)
    {
        do
        {
            system("clear");
            cout << APs[0]->get_species() << ", HP: " << APs[0]->get_current_HP() << "/" << APs[0]->get_HP() << "\nvs.\n";
            cout << APs[1]->get_species() << ", HP: " << APs[1]->get_current_HP() << "/" << APs[1]->get_HP() << "\n";
        } while (faint_check(0) || faint_check(1)); 
/*  This is to make sure the players only give commands when both pokemon are alive, 
    while also ensuring they are prompted to switch pokemon with the fainted ones on screen */

        cout << "Trainer 1: ";
        cin >> command0;
        cout << "Trainer 2: ";
        cin >> command1;

        if(command1[0] != 'S' && (APs[0]->get_SPD() > APs[1]->get_SPD() || command0[0] == 'S')) //deciding turn order
        {
            turn(0, command0);
            turn(1, command1);
        }
        else
        {
            turn(1, command1);
            turn(0, command0);
        }
    }
}