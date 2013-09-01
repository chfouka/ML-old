#include<iostream>
#include<Dataset.h>

#include<network.h>
#include<hiddenlayer.h>
#include<outputlayer.h>
#include<Unit.h>
#include <boost/program_options.hpp>
using namespace boost::program_options;

/*su monk1 0.8 e 400 iterazioni va ok*/

#define normalizationValues_Path "./item/normvalues"

using namespace std;

int main(int argc, char** argv)
{
    int numUnits = 10;
    double lambda = 0.01;
    double alpha = 0.2;
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
            ("alpha,a", value<double>(&alpha), "moment constant")
            ("etaS,S", value<double>(&etas), "sigmoidal learning rate")
            ("etaL,L",value<double>(&etal), "linear learning rate")
            ("epochs,e",value<int>(&epochs), "training epochs")
            ("numUnits,u", value<int>(&numUnits), "number of hidden units")
            ("earlystop,E", value<bool>(&earlytstop), "number of hidden units")

            ("datasetPath,d",value<string>(&dataset), "dataset path")
            ("normalize,z",value<bool>(&normalize), "normalization is needed" )
            ("normvaluesPath,n",value<string>(&normvalues), "max min values path")

            ("input,i",value<int>(&numInput), "number of input units")
            ("output,o",value<int>(&numOutput), "number of output units")

            ("riskEstimation,r", value<bool>(&riskEstimation), "do a risk estimation")
            ("testsetPath,t",value<string>(&testset), "testset path for risk estimation")

            ("fraction,p", value<double>(&p), "fraction of dataset for training")
            ("simpleValidation,v", value<bool>(&simpleValidation), "simulate with a simple validation")
            ("crossValidation,c", value<bool>(&crossValidation), "simulate with cross validation")
            ("folds,f", value<int>(&folds), "number of folds")
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
    Dataset ts; // aggiunta per produrre i grafici necessari x i monks

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

    ds.shuffle();
    ts = Dataset(testset.c_str(), numInput, numOutput);

    /*Preparo i dati per il learning con BP: suddivido in training e validation*/
    vector<Pattern> valid_patt;
    vector<Pattern> train_patt;
    Dataset BP_validation (valid_patt, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
    Dataset BP_training (train_patt, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
    ds.split(&BP_training, &BP_validation, p);

    /*Preparo la rete e variabili errore*/
    Network net = Network (numInput, numOutput, numUnits);
    double validation_error = 0.0;
    double risk = 0.0;

    /*Alleno con simple oppure corss validation*/
    if( simpleValidation ){
        // per il monk sia training che validation metto ds tanto non voglio earlystop, brutto ma non riesco a uniformarlo
        validation_error = net.learnBackPro( ds, ds, epochs, etas, etal, lambda, alpha, earlytstop, ts);
        // sempre per il monk, voglio il missclassification rate
        double accuracy = net.ClassifyTst(ts, 0.5);
        cerr << "accuracy rate " << 100.0 - accuracy << endl;
        cerr << "Simple validation: MSE " << validation_error << endl;
    }

    if( crossValidation ){
        validation_error = net.cross_validation( ds, folds, epochs, etas, etal, lambda, alpha, earlytstop );
        cerr << "Cross validation: MSE " << validation_error << endl;
    }


    /*Se riesco faccio risk estimation dal file di test specificato*/
    if( riskEstimation ){
        Dataset test;
        if(normalize){
            test = Dataset(testset.c_str(), numInput, numOutput, maxInputs, minInputs, maxOutputs, minOutputs);
            test.scale();
        }
        else
            test = Dataset(testset.c_str(), numInput, numOutput);

        net.learnBackPro(BP_training, BP_validation, epochs, etas, etal, lambda, alpha, earlytstop );
        risk = net.error_MSE( test );
        cerr << "Risk Estimation: test MSE "  << risk << endl;
    }

    return 0;
}

