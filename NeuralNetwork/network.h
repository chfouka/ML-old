#ifndef NETWORK_H
#define NETWORK_H

#include<hiddenlayer.h>
#include<outputlayer.h>
#include<Dataset.h>
#include<math.h>
#include<vector>

using namespace std;

class Network
{
    OutputLayer outLayer;
    HiddenLayer hidLayer;
    int inputDimension;
    int outputDimension;
    int hidDimension;

public:
    Network( int indim, int outdim, int hidim ) : outLayer(outdim, hidim+1),
        hidLayer( hidim, indim+1)
    {
      inputDimension = indim;
      outputDimension = outdim;
      hidDimension = hidim;
    }

    vector<double> getOutput( ){
       return outLayer.getOutputs();
    }

    void learnBackPro( Dataset trset, int times ){
        /*Initialization*/
        hidLayer.Initialize();
        outLayer.Initialize();

        while ( times != 0 ){
            for( int i = 0; i < trset.data.size(); i ++ ){
                vector<double> input = trset.data[i].inputs;
                input.push_back(1.0);
                hidLayer.setInputs(input);
                vector<double> outHidden = hidLayer.getOutputs();
                outHidden.push_back(1.0);
                outLayer.setInputs(outHidden);

                vector<double> outLayer_deltas = outLayer.Update_Weights(trset.data[i].outputs);

                /*calcoli per i deltas dell'hidden*/
                vector<double> deltas;

                for(unsigned int i = 0; i<hidDimension; i++){
                    double delta = 0.0;
                    for( unsigned int j = 0; j < outputDimension; j++ ){
                        double d = outLayer.getUnit(j).get_weight(i);
                        delta += outLayer_deltas[j] * d;
                        cout << "delta: " << delta << endl;
                    }

                    deltas.push_back(delta);
                }

                hidLayer.Update_Weights(deltas);
            }
            times -= 1;
        }

    }


    vector<double> Classify(vector<double> inputs){
        inputs.push_back(1.0);
        hidLayer.setInputs(inputs);
        vector<double> outHidden = hidLayer.getOutputs();
        outHidden.push_back(1.0);
        outLayer.setInputs(outHidden);
        vector<double> outs = outLayer.getOutputs();
        return outs;
    }


    double ClassifyTst( Dataset test, double treshold ){
        // return error
        unsigned int missed = 0;

        for(unsigned int i = 0; i < test.data.size(); ++i ){

            Pattern pattern = test.data[i];
            vector<double> outs = Classify(pattern.inputs);
            cout << "Pattern( " << pattern << " ) ( "  ;
            bool wrong = false;
            for( unsigned int j = 0; j < outs.size(); ++j ){
                cout << outs[j] << " ";
                if( fabs( outs[j] - pattern.outputs[j] ) > treshold )
                    wrong = true;
            if(wrong) missed ++;
            }
            cout << " ) error: " << wrong << endl;
        }

        cout << "missed " << missed << " total " << test.data.size( ) << endl;
        return  double( missed ) / double( test.data.size( ) ) ;
    }


    void Print_Weights( ){
        cout << "/////     HiddenLayer     //////" << endl;
        hidLayer.print( );
        cout << "/////     OutputLayer     //////" << endl;
        outLayer.print( );
    }

};

#endif // NETWORK_H
