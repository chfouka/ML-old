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

    double cross_validation( Dataset ds, unsigned int folds, unsigned int epochs,
                             double etas, double etal, double lambda, double alpha){
        /** restituisce una stima di rischio media
         * della NN corrente eseguendo una k-folds c.v
         **/
        ds.scale();

        vector<double> errors;
        double error;
        unsigned int beg = 0;
        unsigned int end = 0;

        vector<Pattern> whole = ds.data;
        for(unsigned int i = folds; i != 0; --i ){
            cout << "fold: " << i << " ";

            beg = end; // la prima volta e' 0, quindi ok
            end = beg + (whole.size() - beg) / i; // il numero di elementi rimanenti diviso
                                                  // le partizioni rimanenti

            vector<Pattern> test;
            vector<Pattern> train;
            for ( unsigned int j = 0; j < whole.size(); ++j ) {
                if ( j >= beg && j < end )
                    test.push_back( whole[j] );
                else
                    train.push_back( whole[j] );
            }

            // splitto ulteriormente il TRAIN set in VALIDATION e TRAIN
            // commenta la prossima riga se vuoi evitare di prendere il validation a caso
            //random_shuffle( train.begin(), train.end() );
            // prendo gli ultimi (train.size() / 4) elementi e li metto nel validation
            //vector<Pattern> validation( train.end() - train.size() / 4, train.end() );
            // poi li rimuovo dal TRAIN
            //train.erase( train.end() - train.size() / 4, train.end() );

            //Creo datasets su cui fare backpro
            Dataset train_set(train, inputDimension, outputDimension, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
            Dataset validation_set(test, inputDimension, outputDimension, ds.maxInputs, ds.minInputs, ds.maxOutputs, ds.minOutputs);
            //Dataset test_set(test, inputDimension, outputDimension, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);

         //   learnBackPro(train_set, validation_set, epochs, etas, etal, lambda, alpha);
            error = error_MSE(validation_set);
            errors.push_back( error );
            cout << "error estimated " << error << endl;
        }

        double mean_error = 0.0;
        for(unsigned int i = 0; i<folds; i++)
            mean_error += errors[i];
        return mean_error / folds;
   }


    void learnBackPro( Dataset training, Dataset validation, Dataset test, unsigned int times,
                       double etas, double etal, double lambda, double alpha  ){
        /**
         * Si usa l'early stopping come criterio di arresto (oltre un maxnum di epoche)
         * Ad ogni 15 epoche viene valutato l'errore MSE sul validation set, se questo non
         * decresce rispetto all'ultima valutazione allora si stoppa il training in quanto
         * questo potrebbe essere un sintomo di overfitting.
         **/

        unsigned int epoca = 0;
        //double current_validationError;
        double avg_verror = 0;
        double minavg_verror = std::numeric_limits<double>::max();;
        unsigned int minEpoch = 0;
        //double last_validationError = std::numeric_limits<double>::max();

        /*Initialization*/
        srand (time(NULL));
        hidLayer.Initialize();
        outLayer.Initialize();

        /*Iteration*/
        while ( epoca < times ){
            for( unsigned int i = 0; i < training.data.size(); i ++ ){
                vector<double> input = training.data[i].inputs;
                input.push_back(1.0);
                hidLayer.setInputs(input);
                vector<double> outHidden = hidLayer.getOutputs();
                outHidden.push_back(1.0);
                outLayer.setInputs(outHidden);

                vector<double> outLayer_deltas =
                        outLayer.Update_Weights(training.data[i].outputs, training.data.size(), etal, lambda, alpha);

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

                hidLayer.Update_Weights(deltas, training.data.size(), etas, lambda, alpha);
                deltas.clear();
            }

            /*controllo per early stopping*/

            /*
            if( ( epoca % 100 ) == 0){
                current_validationError = error_MSE( validation );
                if(current_validationError > last_validationError ){
                    cerr << "EARLY STOP, EPOCH: " << epoca << "  " << endl;
                    //break;
                }
                else
                    last_validationError = current_validationError;
            }

            current_validationError += error_MSE(validation);
            if( epoca  )
            */

            double validation_error = error_MSE(validation);
            double training_error = error_MSE(training);            
            double test_error = error_MSE(test);

            avg_verror += validation_error / 10 ;

            if( epoca != 0 && (epoca % 10 ) == 0 ){
                if(avg_verror < minavg_verror){
                    minavg_verror = avg_verror;
                    minEpoch = epoca;
                }
                else{
                    if( epoca - minEpoch > 1000 ){
                        cerr << minEpoch << " EARLY STOP" << endl;
                        // break;
                    }
                }

                avg_verror = 0;
            }



            cout << epoca << " "
                 << training_error << " "
                 << validation_error << " "
                 << test_error << endl;

            epoca += 1;
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
       /** computes the Mean Squared Error
        * detto anche:  the LMS error, oppure loss dell'LMS cit.Micheli
        * MSE = 1/N ( Sum_p ||o_p - t_p|| ^ 2 )
        **/
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

