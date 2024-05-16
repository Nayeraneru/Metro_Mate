#include "Train.h"
#include"Station.h"
#include <chrono>
#include <thread>
#include "Admin.h"

Train::Train(int id, int cap, vector<Station*> route, int ln)
    : trainID(id), capacity(cap), route(route),line(ln){}

Train::Train(int id, int cap, int ln)
    : trainID(id), capacity(cap), line(ln) {}

void Train::setBreakdown(bool isBroken) {
    isBreakdown = isBroken;
    if (isBroken) {
        cout << "Train " << trainID << " has broken down!" << endl;
    }

}

void Train::write(ofstream* f)
{
   
    (*f) << to_string(trainID) << "," << to_string(capacity) << "," << to_string(line);
    (*f) << "\n";
}


