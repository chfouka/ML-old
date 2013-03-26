#ifndef SIGMOIDALUNIT_H
#define SIGMOIDALUNIT_H

#include<math.h>
#include<Unit.h>
#include<Pattern.h>
#include<vector>


#define ALPHA 1

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
        double out = this->getOutput( );
        for( unsigned int i = 0; i < weights.size( ); i++ ){
            weights[i] = weights[i] + ETA * delta * SigmoidePrim( net ) * out;
        }
        return delta * SigmoidePrim(net);
    }


    double get_weight(unsigned int i){
        return weights[i];
    }

    /*void Update_weights( vector<Util> outLayer_deltas, int index){
        double out = this->getOutput();
        double net = this->getNet();
        double delta = 0.0;
        for(unsigned  int k = 0; k < outLayer_deltas.size(); k++)
            delta += outLayer_deltas[k].delta * outLayer_deltas[k].weights[index];
        for( int j = 0; j < dimension; j++){
            weights[j] = weights[j] + ETA * delta * exp(-net) * out * out * out;
        }
    }*/
};

#endif // SIGMOIDALUNIT_H
