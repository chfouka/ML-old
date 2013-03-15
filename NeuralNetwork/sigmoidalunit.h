#ifndef SIGMOIDALUNIT_H
#define SIGMOIDALUNIT_H

#include<math.h>
#include<Unit.h>

#define ALPHA 1

class SigmoidalUnit: public Unit
{
    double Sigmoide(double in ){
        return ( 1.0 / ( 1.0 + exp(- (ALPHA * in) ) ) );
    }

public:
    SigmoidalUnit();
    SigmoidalUnit( int dim ){
        this->dimension = dim;
        for( int i = 0 ; i< this->dimension ; i++){
            this->weights[i] = 0.0;
            cout << this->weights[i] << endl;
        }
    }

    double getOutput(){
       return Sigmoide( getNet( ) );
    }

};

#endif // SIGMOIDALUNIT_H
