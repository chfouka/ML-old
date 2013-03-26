#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H

#include<vector>
#include<sigmoidalunit.h>
#include<Pattern.h>

using namespace std;

class HiddenLayer
{
    int inputdimension;
    vector<SigmoidalUnit> units;
    vector<double> inputs;

public:
    HiddenLayer( int dim, int inputdim ){
        inputdimension = inputdim;
        for(int i = 0; i < dim; i++ ){
            units.push_back(SigmoidalUnit(inputdimension));
        }
    }

    void setInputs(vector<double> in){
        if( in.size() != inputdimension )
            cerr << "HiddenLayer: wrong input dimension"
                 <<  "must: " << inputdimension
                 << " is:" << in.size() << endl;

        else{
            inputs = in;
            for(unsigned int i = 0; i < units.size(); i++ )
                units[i].setInputs(in);
        }
    }

    vector<double> getOutputs( ){
        vector<double> outs;
        for(unsigned int i = 0 ; i<units.size(); i++ )
            outs.push_back(units[i].getOutput());
        return outs;
    }

    void Initialize( ){
        for( int i = 0; i < units.size() ; i++ ){
           units[i].Initialize();
        }
    }

    void Update_Weights( vector<double> deltas ){
        if(deltas.size() != units.size() )
            cerr << "HiddenLayer error: deltas dimension wrong" << endl;
        else{

            for(unsigned int i = 0; i<units.size(); i++)
                units[i].Update_Weights(deltas[i]);

        }
    }

    void print (){
        for(unsigned int i = 0; i<units.size(); i++ ){
            cout << "**** unit H" << i << " ****";
            units.at(i).print_weights();
            cout << endl;
        }

    }

    /*void Update_Weights(vector<Util> outLayer_deltas){
        for( int i = 0; i < dimension; i++)
            units[i].Update_weights(outLayer_deltas, i);
    }*/

};

#endif // HIDDENLAYER_H
