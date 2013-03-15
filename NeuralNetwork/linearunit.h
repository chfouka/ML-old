#ifndef LINEARUNIT_H
#define LINEARUNIT_H

#include<Unit.h>

using namespace std;

class LinearUnit: public Unit
{
public:

    LinearUnit();

    double getOutput(){
        return getNet();
    }

};

#endif // LINEARUNIT_H
