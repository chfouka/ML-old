#ifndef SIGMOIDALUNIT_H
#define SIGMOIDALUNIT_H

#include<math.h>
#include<Unit.h>
#include<Pattern.h>
#include<vector>


//#define ALPHA 0.5
//#define PORTION 0.0000

class SigmoidalUnit: public Unit
{
    double Sigmoide(double in ){
        return  1.0 / ( 1.0 + exp( -ALPHA * in ) ) ;
    }

    double SigmoidePrim( double in ){
        return exp( -in ) * Sigmoide( in ) * Sigmoide( in );
    }

public:

    SigmoidalUnit( int dim ) : Unit( dim ){

    }

    double getOutput( ){
       return Sigmoide( this->getNet( ) );
    }

    double Update_Weights( double delta ){
        double net = this->getNet( );
        for( unsigned int i = 0; i < weights.size( ); i++ ){
            /* double deltaweight = ETA_S * delta * SigmoidePrim( net ) * inputs[i] + MOM * old_deltaweights[i];
            weights[i] += ETA_S * delta * SigmoidePrim( net ) * inputs[i] + MOM * old_deltaweights[i];
            old_deltaweights[i] = deltaweight;
            */

            double deltaweight = ETA_S *
                    ( (delta * SigmoidePrim( net ) * inputs[i])  - LAMBDA * weights[i] ) +
                    MOM * old_deltaweights[i];
            weights[i] += ETA_S *
                    ( (delta * SigmoidePrim( net ) * inputs[i])  - LAMBDA * weights[i] ) +
                    MOM * old_deltaweights[i];
            old_deltaweights[i] = deltaweight;

        }
        return delta * SigmoidePrim(net);
    }

    double get_weight(unsigned int i){
        return weights[i];
    }

};

#endif // SIGMOIDALUNIT_H
