#ifndef OUTPUTLAYER_H
#define OUTPUTLAYER_H

#include<vector>
#include<linearunit.h>

using namespace std;

class OutputLayer
{
    int dimension;
    vector<LinearUnit> units;
    vector<double> inputs;
    //vector<double> outputs;


public:
    OutputLayer();

    OutputLayer( int dim){
        dimension = dim;
        for(int i = 0; i < dim; i++ )
            units.push_back(LinearUnit());
    }

    void setInputs( vector<double>& in ){
        inputs = in;
        for(int i = 0; i < units.size(); i++ )
            units[i].setInputs(in);
    }

    vector<double> getOutputs(){
        vector<double> outs;
        for(int i = 0 ; i < units.size(); i++ ){
            outs.push_back( units[i].getOutput( ) );
        }
        return outs;

    }

    void Initialize( ){
        cout << "Output Initialize called";
        for( int i = 0; i < units.size(); i++ )
            units[i].Initialize();
    }

};

#endif // OUTPUTLAYER_H
