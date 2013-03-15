#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H

#include<vector>
#include<sigmoidalunit.h>

using namespace std;

class HiddenLayer
{
    int dimension;
    vector<SigmoidalUnit> units;
    vector<double> inputs;

public:
    HiddenLayer();
    HiddenLayer( int dim ){
        dimension = dim;
        for(int i = 0; i < dim; i++ )
            units.push_back(SigmoidalUnit());
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
        cout << "Hidden Initialize called";
        for( int i = 0; i < units.size(); i++ )
            units[i].Initialize();
    }
};

#endif // HIDDENLAYER_H
