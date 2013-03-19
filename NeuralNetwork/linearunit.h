#ifndef LINEARUNIT_H
#define LINEARUNIT_H

#include<Unit.h>
#include<Pattern.h>
#include<util.h>

using namespace std;

class LinearUnit: public Unit
{
public:

    //LinearUnit();
    LinearUnit(int dim ) : Unit(dim) {
        //this->dimension = dim;
    }

    double getOutput(){
        return getNet();
    }

    Util Update_weights(Pattern pattern ){
        double delta;
        vector<double> old_weights = weights;
        double out = this->getOutput();
        for( unsigned int i = 0; i < dimension; i++ ){
            // deltaK = ( dk - Ok ) * f'(net)
            delta = pattern.outputs[i] - out ;
            weights[i] = weights[i] + ETA * delta * out;
        }

        return Util(old_weights, delta);
    }

};

#endif // LINEARUNIT_H
