#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H

#include<vector>
#include<sigmoidalunit.h>
#include<Pattern.h>
#include<util.h>

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
        cout << "HIDDEN LAYER CREATED, #Units = " << dim << " dimUnit = "<< inputdim <<endl;
        dimension = dim;
        indim = inputdim;
        for(int i = 0; i < dimension; i++ ){
            cout << "Unit "<< i << "created" << endl;
            units.push_back(SigmoidalUnit(indim));
        }
    }

    void setInputs(vector<double>& in){
        inputs = in;
        for(unsigned int i = 0; i < units.size(); i++ )
            units[i].setInputs(in);
    }

    vector<double> getOutputs( ){
        vector<double> outs;
        for(unsigned int i = 0 ; i<units.size(); i++ )
            outs.push_back(units[i].getOutput());
        return outs;
    }

    void Initialize( ){
        for( int i = 0; i < dimension ; i++ ){
           cout << "Hidden: initialize unit" << i <<endl;
           units[i].Initialize();
        }
    }

    void Update_weights(vector<Util> outLayer_deltas, Pattern pattern){
        for( unsigned int i = 0; i < dimension; i++)
            units[i].Update_weights(outLayer_deltas, pattern);
    }

};

#endif // HIDDENLAYER_H
