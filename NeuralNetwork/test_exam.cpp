#include<iostream>
#include<Dataset.h>

#include<network.h>
#include<hiddenlayer.h>
#include<outputlayer.h>
#include<Unit.h>

#define ETA_L 0.004       /*su monk1 0.8 e 400 iterazioni va ok*/
#define ETA_S 0.01
#define ALPHA 1.0
#define MOM 0.2
#define LAMBDA 0.01


using namespace std;

int main()
{
    //cout.precision(6);
    // cout << fixed;


    char dataset[] = "./item/exam.training";

    Dataset ds (dataset, 6 , 2);
    /*
    Network net = Network (6, 2, 60);

    double mean_error = net.cross_validation(ds, 10, 15000);

    cout << mean_error << endl;
    */




    ds.scale();
    vector<Pattern> valid_patt;
    vector<Pattern> train_patt;
    vector<Pattern> test_patt;
    vector<Pattern> finvalid_patt;
    Dataset validation (valid_patt, 6, 2, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
    Dataset training (train_patt, 6, 2, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
    Dataset test (test_patt, 6, 2, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);
    Dataset finvalidation (finvalid_patt, 6, 2, ds.maxInputs, ds.minInputs, ds.maxOutputs,ds.minOutputs);

    ds.split(&training, &validation);
    validation.split(&finvalidation,&test);


   //cout << "Train: " << training << endl << endl;
   //cout << "Validation: " << finvalidation << endl;
   //cout << "Test: " <<  test << endl;


    Network net = Network (6, 2, 60);
    net.learnBackPro( training, finvalidation, 15000, ETA_S, ETA_L, LAMBDA, MOM );
//

    cout << "net" << net.error_MSE(test) << endl;

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
