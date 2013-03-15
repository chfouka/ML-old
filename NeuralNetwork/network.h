#ifndef NETWORK_H
#define NETWORK_H

#include<hiddenlayer.h>
#include<outputlayer.h>
#include<Dataset.h>
#include<vector>

using namespace std;

class Network
{
    HiddenLayer hidLayer;
    OutputLayer outLayer;
    int inputDimension;
    int outputDimension;
    int hidDimension;

public:
    Network();
    Network( int indim, int outdim, int hidim ){
      inputDimension = indim;
      outputDimension = outdim;
      hidDimension = hidim;
      outLayer = OutputLayer(outputDimension, hidDimension);
      hidLayer = HiddenLayer(hidDimension, inputDimension);
    }

    vector<double> getOutput(){
       return outLayer.getOutputs();
    }

    void learnBackPro( Dataset trset ){
        /*Initialization*/
        hidLayer.Initialize();
        outLayer.Initialize();

    }
};

#endif // NETWORK_H
