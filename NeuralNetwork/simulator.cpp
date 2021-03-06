#include<iostream>
#include<Dataset.h>

#include<network.h>
#include<hiddenlayer.h>
#include<outputlayer.h>
#include<Unit.h>
#include <boost/program_options.hpp>
using namespace boost::program_options;

using namespace std;


double cross_validation( int numInput, int numOutput, int numUnits, Dataset ds, unsigned int folds, unsigned int epochs,
                         double etas, double etal, double lambda, double alpha, bool earlystop){
    /** restituisce una stima di rischio media
     * della NN corrente eseguendo una k-folds c.v
     **/

    vector<double> errors;
    double error;
    unsigned int beg = 0;
    unsigned int end = 0;

    vector<Pattern> whole = ds.data;
    for(unsigned int i = folds; i != 0; --i ){
        cerr << "fold: " << i << " ";

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


        //Creo datasets su cui fare backpro
        Dataset train_set(train, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
        Dataset validation_set(test, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs, ds.minOutputs);

        Network net = Network (numInput , numOutput, numUnits);

        error = net.learnBackPro(train_set, validation_set, epochs, etas, etal, lambda, alpha, earlystop);
        errors.push_back( error );
        cerr << "error estimated " << error << endl << endl;
    }

    double mean_error = 0.0;
    for(unsigned int i = 0; i<folds; i++)
        mean_error += errors[i];

    return mean_error / folds;
}

int main(int argc, char** argv)
{
    int numUnits = 10;
    double lambda = 0.0;
    double alpha = 0.0;
    double etas = 0.01;
    double etal = 0.004;
    int epochs = 20000;
    string dataset;
    string testset;
    string normvalues;
    int numInput;
    int numOutput;
    bool riskEstimation = 0;
    double p = 0.75;
    bool simpleValidation = false;
    bool crossValidation = false;
    bool normalize = true;
    bool earlytstop = true;
    int folds = 10;

{
    // Declare the supported program options
    options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce this help message")
            ("lambda,l", value<double>(&lambda), "weight decay constant")
            ("alpha,a", value<double>(&alpha), "moment constant, default 0.02")
            ("etaS,S", value<double>(&etas), "sigmoidal learning rate, default 0.01")
            ("etaL,L",value<double>(&etal), "linear learning rate, default 0.004")
            ("epochs,e",value<int>(&epochs), "training epochs, default 20000")
            ("numUnits,u", value<int>(&numUnits), "number of hidden units, required")
            ("earlystop,E", value<bool>(&earlytstop), "enable early stop, default 1")

            ("datasetPath,d",value<string>(&dataset), "dataset path,required")
            ("normalize,z",value<bool>(&normalize), "enable normalization, default 1" )
            ("normvaluesPath,n",value<string>(&normvalues), "max min values path, required for normalization")

            ("input,i",value<int>(&numInput), "number of input units, required")
            ("output,o",value<int>(&numOutput), "number of output units, required")

            ("riskEstimation,r", value<bool>(&riskEstimation), "enable a risk estimation, default 0")
            ("testsetPath,t",value<string>(&testset), "testset path for risk estimation")

            ("fraction,p", value<double>(&p), "fraction of dataset for training")
            ("simpleValidation,v", value<bool>(&simpleValidation), "simulate with a simple validation, default 0")
            ("crossValidation,c", value<bool>(&crossValidation), "simulate with cross validation, default 0")
            ("folds,f", value<int>(&folds), "number of folds, default 10")
            ;

    variables_map vm;

    try {
        store(parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            cerr << desc << "\n";
            exit( 1 );
        }

        notify(vm);
    } catch ( error& e ) {
        cerr << desc << endl;
        cerr << e.what() << endl;
        exit( 1 );
    }

    if (!vm.count("input")) {
        cerr << desc << endl;
        cerr << "option --input is required.\n";
        exit( 1 );
    }

    if (!vm.count("output")) {
        cerr << desc << endl;
        cerr << "option --output is required.\n";
        exit( 1 );
    }

    if (!vm.count("datasetPath")) {
        cerr << desc << endl;
        cerr << "option --dataset is required.\n";
        exit( 1 );
    }

    if (!vm.count("normvaluesPath")) {
        if(normalize) {
            cerr << desc << endl;
            cerr << "option --max min values are required for normalization.\n";
            exit( 1 );
        }
    }


    if(!vm.count("simpleValidation") && !vm.count("crossValidation")){
        cerr << desc << endl;
        cerr << "option -- a validation mode is required (simple or cross).\n" ;
        exit( 1 );
    }

    if(riskEstimation && !vm.count("testsetPath")){
        cerr << desc << endl;
        cerr << "option -- a test set for risk estimation is required.\n" ;
        exit( 1 );
    }

}
    /*variabile dataset*/
    Dataset ds;

    /*i seguenti vettori sono significativi solo nel caso della normalizazzione*/
    vector<double> maxInputs;
    vector<double> minInputs;
    vector<double> maxOutputs;
    vector<double> minOutputs;

    if(normalize){
        // leggo i valori max min dal file
        ifstream normvaluesfile(normvalues);
        double d;
        if( ! normvaluesfile.good() ){
            cerr << "max min values file not good" << endl;
            exit( 1 );
        }


        for( int c = 0; c < numInput; c++){
            normvaluesfile >> d;
            maxInputs.push_back(d);
        }

        for( int c = 0; c < numInput; c++){
            normvaluesfile >> d;
            minInputs.push_back(d);
        }

        for( int c = 0; c < numOutput; c++){
            normvaluesfile >> d;
            maxOutputs.push_back(d);
        }

        for( int c = 0; c < numOutput; c++){
            normvaluesfile >> d;
            minOutputs.push_back(d);
        }

        ds= Dataset(dataset.c_str(), numInput, numOutput, maxInputs, minInputs, maxOutputs, minOutputs);
        ds.scale();

    }

    else
        ds = Dataset(dataset.c_str(), numInput, numOutput);



    /*Preparo la rete e variabili errore*/
    //Network net = Network (numInput, numOutput, numUnits);
    double validation_error = 0.0;
    double risk = 0.0;

    /*Alleno con simple oppure corss validation*/
    if( simpleValidation ){
        int runs = 1;


        double error = 0.0 ;
        for(int times = 0; times < runs; times ++){
            ds.shuffle();

            /*Preparo i dati per il learning con BP: suddivido in training e validation*/
            vector<Pattern> valid_patt;
            vector<Pattern> train_patt;
            Dataset BP_validation (valid_patt, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
            Dataset BP_training (train_patt, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
            ds.split(&BP_training, &BP_validation, p);

            Network net = Network (numInput, numOutput, numUnits);

            error += net.learnBackPro( BP_training, BP_validation, epochs,
                                        etas, etal, lambda, alpha, earlytstop) / runs;
        }

        //cerr << "Simple validation: mean MS " << error << endl;
        cout << error;
    }

    if( crossValidation ){
        //cerr << "cross " << endl;
        validation_error = cross_validation( numInput, numOutput, numUnits, ds, folds, epochs, etas, etal, lambda, alpha, earlytstop );
        //cerr << "Cross validation: MSE " << validation_error << endl;
        cout << validation_error << endl;
    }


    /*Se voluto faccio risk estimation dal file di test specificato*/
    if( riskEstimation ){
        Dataset test;
        if(normalize){
            test = Dataset(testset.c_str(), numInput, numOutput, maxInputs, minInputs, maxOutputs, minOutputs);
            test.scale();
        }
        else
            test = Dataset(testset.c_str(), numInput, numOutput);
        Network net(numInput, numOutput, numUnits);

        vector<Pattern> valid_patt;
        vector<Pattern> train_patt;
        Dataset BP_validation (valid_patt, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
        Dataset BP_training (train_patt, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
        ds.split(&BP_training, &BP_validation, p);

        net.learnBackPro(BP_training, BP_validation, epochs, etas, etal, lambda, alpha, earlytstop );
        risk = net.error_MSE( test );
        cerr << "Risk Estimation: test MSE "  << risk << endl;
    }

    return 0;
}

