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
    unsigned int inputDimension;
    unsigned int outputDimension;
    unsigned int hidDimension;

public:
    Network( unsigned int indim, unsigned int outdim, unsigned int hidim ) : outLayer(outdim, hidim+1),
        hidLayer( hidim, indim+1)
    {
      inputDimension = indim;
      outputDimension = outdim;
      hidDimension = hidim;
    }

    vector<double> getOutput( ){
       return outLayer.getOutputs();
    }

    void learnBackPro( Dataset trset, Dataset testset, int times ){
        /*Initialization*/
        srand (time(NULL));
        hidLayer.Initialize();
        outLayer.Initialize();
        int epoca = 0;

        /*Iteration*/
        while ( epoca < times ){
            for( unsigned int i = 0; i < trset.data.size(); i ++ ){
                vector<double> input = trset.data[i].inputs;
                input.push_back(1.0);
                hidLayer.setInputs(input);
                vector<double> outHidden = hidLayer.getOutputs();
                outHidden.push_back(1.0);
                outLayer.setInputs(outHidden);

                vector<double> outLayer_deltas = outLayer.Update_Weights(trset.data[i].outputs);

                /*calcoli per i deltas dell'hidden*/
                vector<double> deltas;

                for(unsigned int i = 0; i < hidDimension; i++){
                    double delta = 0.0;
                    for( unsigned int j = 0; j < outputDimension; j++ ){
                        double d = outLayer.getUnit(j).get_weight(i);
                        delta += outLayer_deltas[j] * d;
                    }
                    deltas.push_back(delta);
                }

                hidLayer.Update_Weights(deltas);
                deltas.clear();
            }

            epoca += 1;

            /* calcolo errore */

            double error_test = error_MEE(testset);
            double error_training = error_MEE(trset);
            cout << epoca << " " << error_training  << " " << error_test << endl;
            //cout << epoca << " " << error_training  <<  endl;

        }
    }


    double cross_validation( Dataset ds, unsigned int fold ){


        return 0.0;
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
            cout << "Pattern:" << i << "missed:" << missed << endl;
            Pattern pattern = test.data[i];
            vector<double> outs = Classify(pattern.inputs);
            cout << "Pattern( " << pattern << " ) ( "  ;
            bool wrong = false;
            for( unsigned int j = 0; j < outs.size(); ++j ){
                cout << outs[j] << " ";
                if( fabs( outs[j] - pattern.outputs[j] ) > treshold )
                    wrong = true;
            }
            if(wrong) missed ++;

            cout << " ) error: " << wrong << endl;
        }

        cout << "missed " << missed << " total " << test.data.size( ) << endl;
        return  (double( missed ) / double( test.data.size( ) )) * 100 ;
    }


    void Print_Weights( ){
        cout << "/////     HiddenLayer     //////" << endl;
        hidLayer.print( );
        cout << "/////     OutputLayer     //////" << endl;
        outLayer.print( );
    }

    double error_MSE(Dataset test){
        /***computes the Mean Squared Error
            detto anche:  the LMS error, oppure loss dell'LMS cit.Micheli
            MSE = 1/N ( Sum_p ||o_p - t_p|| ^ 2 )
        ***/

        double sum = 0.0;

        for(unsigned int i = 0; i<test.data.size(); i++){
            Pattern pattern = test.data.at(i);
            vector<double> outs = Classify(pattern.inputs);
            if( outs.size() != pattern.outputs.size() )
                cerr << "error_MSE: wrong dimensions" << endl;
            Pattern pattern_classified(pattern.inputs, outs);

            test.descale(pattern);
            test.descale(pattern_classified);

            outs = pattern_classified.outputs;
            vector<double> targets = pattern.outputs;
            // vettore differenza e norma
            vector<double> diff;
            diff.assign(pattern.outputs.size(), 0);
            double norma_2 = 0.0;
            for(unsigned int j=0; j< outs.size(); j++)
                diff.at(j) = targets[j] - outs[j];
            for(unsigned int j = 0; j<diff.size(); j++)
                norma_2 += diff.at(j) * diff.at(j);

            sum = sum + norma_2;

            test.scale(pattern);
        }
        return sum / ( 2 * test.data.size() );
    }


    double error_MEE(Dataset test){
        /***computes the Mean Euclidean Error
            MEE = 1/N ( Sum_p ||o_p - t_p||  )
        ***/

        double sum = 0.0;

        for(unsigned int i = 0; i<test.data.size(); i++){
            Pattern pattern = test.data.at(i);
            vector<double> outs = Classify(pattern.inputs);
            if( outs.size() != pattern.outputs.size() )
                cerr << "error_MSE: wrong dimensions" << endl;
            Pattern pattern_classified(pattern.inputs, outs);

            test.descale(pattern);
            test.descale(pattern_classified);

            outs = pattern_classified.outputs;
            vector<double> targets = pattern.outputs;
            // vettore differenza e norma
            vector<double> diff;
            diff.assign(pattern.outputs.size(), 0);
            double norma_2 = 0.0;
            for(unsigned int j=0; j< outs.size(); j++)
                diff.at(j) = targets[j] - outs[j];
            for(unsigned int j = 0; j<diff.size(); j++)
                norma_2 += diff.at(j) * diff.at(j);

            sum += sqrt (norma_2);

            test.scale(pattern);
        }
        return sum / ( 2 * test.data.size() );
    }



};



#endif // NETWORK_H

