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
    double getOutput(){
       return Sigmoide( getNet( ) );
    }

};

#endif // SIGMOIDALUNIT_H
