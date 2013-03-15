#ifndef OUTPUTLAYER_H
#define OUTPUTLAYER_H

#include<vector>
#include<linearunit.h>

using namespace std;

class OutputLayer
{
    int dimension;
    int hiddendim;
    vector<LinearUnit> units;
    vector<double> inputs;
    //vector<double> outputs;


public:
    OutputLayer();

    OutputLayer(int dim, int hid){
        cout << "OUTPUT LAYER CREATED, #Unita = " << dim << " Unita dim = "<< hid <<endl;

        dimension = dim;
        hiddendim = hid;
        for(int i = 0; i < dimension ; i++ ){
            cout << "unita' creata: " << i << endl;
            units.push_back(LinearUnit(hiddendim));
        }
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
        cout << "Output Initialize called" << endl;
        for( int i = 0; i < units.size()    ; i++ ){
            cout << "Outlayer: initialize unit:" << i << endl;
            units[i].Initialize();
        }
    }

};

#endif // OUTPUTLAYER_H
