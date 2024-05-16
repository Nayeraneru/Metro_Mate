#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "user.h"
#include<fstream>
using namespace std;

class Station;

class Train
{

public:

    int trainID;
    int capacity;
    int breakdownDelay = 10;
    int line;
    vector<Station*> route;
    Train(int id, int cap, vector<Station*> route , int ln);
    bool isBreakdown = false;
    void setBreakdown(bool isBroken);
    void write(ofstream* f);
    Train(int id, int cap, int ln);
};