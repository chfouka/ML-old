#ifndef LINEARUNIT_H
#define LINEARUNIT_H

#include<Unit.h>

using namespace std;

class LinearUnit: public Unit
{
public:

    LinearUnit();
    LinearUnit(int dim ){
        this->dimension = dim;
        for( int i = 0 ; i< this->dimension ; i++){
            this->weights[i] = 0.0;
            cout << this->weights[i] << endl;
        }
    }

    double getOutput(){
        return getNet();
    }

};

#endif // LINEARUNIT_H
