#ifndef OUTPUTLAYER_H
#define OUTPUTLAYER_H

#include<vector>
#include<sigmoidalunit.h>
#include<Pattern.h>

using namespace std;

class OutputLayer
{
    //int dimension;
    int hiddendimension;
    vector<SigmoidalUnit> units;
    vector<double> inputs;
    //vector<double> outputs;


public:
    OutputLayer();

    OutputLayer(int dim, int hid){
        cout << "OUTPUT LAYER CREATED, #Units = " << dim << "dim Unit = "<< hid <<endl;

        //dimension = dim;
        hiddendimension = hid;
        for(int i = 0; i < dim ; i++ ){
            cout << "Unit "<< i << "created" << endl;
            units.push_back(SigmoidalUnit(hiddendimension));
        }
    }

    void setInputs( vector<double>& in ){
        if(in.size() != hiddendimension )
            cerr << "OutputLayer: input wrong dimension" << endl;
        else{
            inputs = in;
            for(unsigned int i = 0; i < units.size(); i++ )
                units[i].setInputs(in);
        }
    }

    vector<double> getOutputs( ){
        vector<double> outs;
        for( unsigned int i = 0 ; i < units.size(); i++ ){
            outs.push_back( units[i].getOutput( ) );
        }
        return outs;

    }

    SigmoidalUnit getUnit( int index ){
        return units[index];
    }

    void Initialize( ){
        for( unsigned int i = 0; i < units.size(); i++ ){
            units[i].Initialize();
        }
    }

    vector<double> Update_Weights( vector<double>& targets ){
        if( targets.size() != units.size() )
            cerr << "OutLayer: wrong target size" << endl;
        else{
            vector<double> deltas;

            for(unsigned int i = 0; i < units.size() ; i++ ){
                double delta = targets[i] - units[i].getOutput();
                double d = units[i].Update_Weights(delta);
                deltas.push_back(d);
            }

            return deltas;

        }
    }


    void print (){
        for(unsigned int i = 0; i<units.size(); i++ ){
            cout << "**** unit O" << i << " ****";
            units.at(i).print_weights();
            cout << endl;
        }

    }

    /*vector<Util> Update_weights( Pattern pattern ){
        vector<Util> deltas;

        for( int i = 0; i < dimension; i++ ){
            Util delta = units[i].Update_weights( pattern );
            deltas.push_back(delta);
        }

        return deltas;
    }*/

};

#endif // OUTPUTLAYER_H
