#pragma once

#include <string>
#include"pokemon.hpp"
using namespace std;

class Move
{
public:
    Move(string name);

    Type get_type() {return type;}
    Category get_CAT() {return CAT;}
    int get_POW() {return POW;}
    int get_ACC() {return ACC;}
private:
    string name;
    Type type;
    Category CAT;
    int POW;
    int ACC;
};