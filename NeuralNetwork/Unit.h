#ifndef UNIT_H
#define UNIT_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include <stdlib.h>
#include <time.h>

#define ETA 0.2



using namespace std;

class Unit
{
protected:
    int dimension;
    vector<double> weights;
    vector<double> inputs;
    //double output;

public:
    //Unit();
    Unit( int dim ){
        dimension = dim;
        for( int i = 0 ; i< dimension ; i++){
            weights.push_back( 0.0 );
            //cout << weights[i] << endl;
        }
    }

    void setInputs( vector<double>& in ){
        inputs = in;
    }

    void setWeights( vector<double>& w ){
        weights = w;
    }

    double getNet(){
        double net = 0.0;
        for(unsigned int i = 0; i < inputs.size(); i++ ){
            net += weights[i] * inputs[i];
        }

        return net;
    }

    double getOutput();


    void Initialize( ){
        cout << "dimension" << dimension << endl;
        srand (time(NULL));
        for (int i = 0; i < dimension; i++){
            double f = (double)rand() / RAND_MAX;
            weights[i] =  -0.7 + f * (0.7 + 0.7);
            //cout << weights[i] << endl;
        }
    }

};

#endif // UNIT_H
