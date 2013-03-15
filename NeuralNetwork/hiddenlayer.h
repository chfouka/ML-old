#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H

#include<vector>
#include<sigmoidalunit.h>

using namespace std;

class HiddenLayer
{
    int dimension;
    int indim;
    vector<SigmoidalUnit> units;
    vector<double> inputs;

public:
    HiddenLayer();
    HiddenLayer( int dim, int inputdim ){
        cout << "HIDDEN LAYER CREATED, #Unita = " << dim << "Unita dim = "<< inputdim <<endl;
        dimension = dim;
        indim = inputdim;
        for(int i = 0; i < dimension; i++ ){
            cout << "unita' creata: " << i << endl;
            units.push_back(SigmoidalUnit(indim));
        }
    }

    void setInputs(vector<double>& in){
        inputs = in;
        for( int i = 0; i < units.size(); i++ )
            units[i].setInputs(in);
    }

    vector<double> getOutputs(){
        vector<double> outs;
        for( int i = 0 ; i<units.size(); i++ )
            outs.push_back(units[i].getOutput());
        return outs;
    }

    void Initialize( ){
        cout << "Hidden Initialize called" << endl;
        for( int i = 0; i < dimension ; i++ ){
           cout << "Hidden: initialize unit" << i <<endl;
           units[i].Initialize();
        }
    }
};

#endif // HIDDENLAYER_H
