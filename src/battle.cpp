#include <iostream>
#include <string>
#include <vector>
#include "battle.hpp"
#include "trainer.hpp"
using namespace std;

void Battle::initialise_type_matchups()
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

Battle::Battle(string input1, string input2)
{
    initialise_type_matchups();
    this->t = {Trainer("trainer1.txt"), Trainer("trainer2.txt")};
    this->commands.resize(2);
}

void Battle::take_commands()
{
    if(faint_check(0) || faint_check(1))
    {
        return;
    }
    cout << "Trainer 1: ";
    cin >> commands[0];
    cout << "Trainer 2: ";
    cin >> commands[1];
    if(commands[1][0] != 'S' && (t[0].get_active_pokemon()->get_SPD() > t[1].get_active_pokemon()->get_SPD() || commands[0][0] == 'S')) //deciding turn order
    {
        turn(0);
        turn(1);
    }
    else
    {
        turn(1);
        turn(0);
    }
}

void Battle::turn(int x)
{
    if(t[x].get_active_pokemon()->get_current_HP() > 0)
    {
        if(commands[x][0] == 'M')
        {
            t[x].calc_damage(t[((x == 0) ? 1 : 0)].get_active_pokemon(), commands[x][1] - '0' - 1, matchups);
        }
        if(commands[x][0] == 'S')
        {
            t[x].switch_active_pokemon(commands[x][1] - '0' - 1);
        }
    }
}

bool Battle::faint_check(int x)
{
    if(t[x].get_active_pokemon()->get_current_HP() <= 0)
    {
        cout << "\nCurrent Pokemon is Fainted, choose another: ";
        int n = 0;
        cin >> n;
        t[x].switch_active_pokemon(n - 1);
        return true;
    }
    return false;
}