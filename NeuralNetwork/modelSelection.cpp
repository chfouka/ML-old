#include<iostream>
#include<Dataset.h>

#include<network.h>
#include<hiddenlayer.h>
#include<outputlayer.h>
#include<Unit.h>
#include <boost/program_options.hpp>
using namespace boost::program_options;

/*su monk1 0.8 e 400 iterazioni va ok*/


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
    int numInput;
    int numOutput;


    // Declare the supported program options
    options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce this help message")
            ("lambda,l", value<double>(&lambda), "")
            ("alpha,a", value<double>(&alpha), "")
            ("etaS,S", value<double>(&etas), "sigmoidal learning rate")
            ("etaL,L",value<double>(&etal), "linear learning rate")
            ("epochs,e",value<int>(&epochs), "training epochs")
            ("dataset,d",value<string>(&dataset), "dataset path")
            ("input,i",value<int>(&numInput), "number of input units")
            ("output,o",value<int>(&numOutput), "number of output units")
            ("numUnits,n", value<int>(&numUnits), "number of hidden units")
            ;

    variables_map vm;

    try {
        store(parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            cout << desc << "\n";
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

    if (!vm.count("dataset")) {
        cerr << desc << endl;
        cerr << "option --dataset is required.\n";
        exit( 1 );
    }


    Network net = Network (numInput, numOutput, numUnits);

    Dataset ds(dataset.c_str(), numInput, numOutput);

    ds.scale();

    ds.shuffle();

    vector<Pattern> valid_patt;
    vector<Pattern> train_patt;
    vector<Pattern> test_patt;
    vector<Pattern> finvalid_patt;
    Dataset validation (valid_patt, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
    Dataset training (train_patt, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
    Dataset test (test_patt, numInput, numOutput , ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
    Dataset finvalidation (finvalid_patt, numInput, numOutput, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);

    ds.split(&training, &validation, 0.5 );
    validation.split(&finvalidation,&test, 0.5);


    cerr << "Train size: " << training.data.size() << endl << endl;
    cerr << "Validation size: " << finvalidation.data.size() << endl;
    cerr << "Test size:  " <<  test.data.size() << endl;


    net.learnBackPro( training, finvalidation, test, epochs, etas, etal, lambda, alpha );


    cerr << "net" << net.error_MSE(test) << endl;

    /*
    for(unsigned int i = 0; i < test.data.size(); ++i ){
        Pattern pattern = test.data[i];
        vector<double> outs = net.Classify(pattern.inputs);
        for(unsigned int j = 0; j< outs.size(); ++j)
            cout << pattern.outputs.at(j) << " " << outs.at(j) << endl;
        cout << endl;
    }
    */

    // net.Print_Weights();

    return 0;
}

