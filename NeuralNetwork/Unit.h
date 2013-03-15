#ifndef UNIT_H
#define UNIT_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include <chrono>


using namespace std;

class Unit
{
    int dimension;
    vector<double> weights;
    vector<double> inputs;
    //double output;

public:
   // Unit();
    Unit( int dim, vector<double>& in ){
        dimension = dim;
        inputs = in;
    }



    void setInputs( vector<double>& in ){
        inputs = in;
    }

    void setWeights( vector<double>& w ){
        weights = w;
    }

    double getNet(){
        double net = 0.0;
        for( int i = 0; i < inputs.size(); i++ ){
            net += weights[i] * inputs[i];
        }
        return net;
    }

    double getOutput();


    void Initialize( ){

        srand (time(NULL));
        for (int i = 0; i < weights.size(); i++){
            double f = (double)rand() / RAND_MAX;
            weights[i] = -0.7 + f * (0.7 - 0.7);
            cout << weights[i];
        }
    }
};

#endif // UNIT_H
