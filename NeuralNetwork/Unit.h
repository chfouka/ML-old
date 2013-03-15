#ifndef UNIT_H
#define UNIT_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include <stdlib.h>
#include <time.h>


using namespace std;

class Unit
{
protected:
    int dimension;
    vector<double> weights;
    vector<double> inputs;
    //double output;

public:
    Unit();
    Unit( int dim ){
        dimension = dim;
        for( int i = 0 ; i< dimension ; i++){
            weights[i] = 0.0;
            cout << weights[i] << endl;
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
        for( int i = 0; i < inputs.size(); i++ ){
            net += weights[i] * inputs[i];
        }

        return net;
    }

    double getOutput();


    void Initialize( ){
        cout << "Unit initialize" << endl;
        cout << "dimension" << dimension << endl;
        srand (time(NULL));
        cout << "srand done" << endl;
        for (int i = 0; i < dimension ; i++){
            cout << weights[i] << endl;
            cout << "for unit inizializza" << i << endl;
            double f = (double)rand() / RAND_MAX;
            cout << f << endl;
            weights[i] = -0.7 + f * (0.7 + 0.7);
            cout << weights[i] << endl;
        }
    }
};

#endif // UNIT_H
