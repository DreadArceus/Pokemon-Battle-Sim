#include "main.hpp"
#include "move.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Move::Move(string name)
{
    this->name = name;

    ifstream inp("data/moves.txt");
    if(!inp.is_open())
    {
        cout << "Error: Could not find moves.txt.\n";
        exit(0);
    }

    string move_line;
    bool error = true;
    while(getline(inp, move_line))
    {
        if(name == move_line.substr(0, move_line.find('/')))
        {
            error = false;
            break;
        }
    }
    if(error)
    {
        cout << "Error: Could not find the move \"" << name << "\" in moves.txt.\n";
        exit(0);
    }

    this->type = (Type)stoi(move_line.substr(name.length()+1,2));
    this->CAT = (Category)stoi(move_line.substr(name.length()+4,1));
    this->POW = stoi(move_line.substr(name.length()+6,3));
    this->ACC = stoi(move_line.substr(move_line.length() - 3, 3));
}