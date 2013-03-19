#ifndef UTIL_H
#define UTIL_H

#include<vector>

using namespace std;

class Util
{
public:
    vector<double> weights;
    double delta;

public:
    //Util();
    Util( vector<double>& w, double d){
        weights = w;
        delta = d;
    }
};

#endif // UTIL_H
