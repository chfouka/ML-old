#ifndef LINEARUNIT_H
#define LINEARUNIT_H

#include<Unit.h>
#include<Pattern.h>

using namespace std;
#define ALPHA 1
#define PORTION 0.0001

class LinearUnit: public Unit
{
public:

    LinearUnit(int dimension ) : Unit(dimension) {

    }

    double getOutput(){
        return  this->getNet();
    }

    double LinearPrime( double in ){
        return 1.0;
    }

    double Update_Weights(double delta){
        double out = this->getOutput();
        double net = this->getNet();

        for( unsigned int i=0; i< weights.size(); i++ ){
            weights[i] = weights[i] + ETA * delta * LinearPrime(net) * out + PORTION * weights[i];
        }

        return delta * LinearPrime(net);

    }


    double get_weight(unsigned int i){
        return weights[i];
    }

    /*Util Update_weights( Pattern pattern ){
        double delta;
        vector<double> old_weights = weights;
        //double net = this->getNet();
        double out = this->getOutput();
        delta = pattern.outputs[0] - out ;  //TBD
        for( int i = 0; i < dimension; i++ ){
            // deltaK = ( dk - Ok ) * f'(net)
            weights[i] = weights[i] + ETA * delta * out;
            //weights[i] = weights[i] + ETA * exp(-net) * out * out * delta * out;

        }

        return Util(old_weights, delta);
    }*/

};

#endif // LINEARUNIT_H
