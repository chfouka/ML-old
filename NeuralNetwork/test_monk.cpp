#include<iostream>
#include<Dataset.h>

#include<network.h>
#include<hiddenlayer.h>
#include<outputlayer.h>
#include<Unit.h>

using namespace std;

int main()
{
    cout.precision(5);
    cout << fixed;


    char training[] = "./item/monk/monkNormTR3";

    char test[] = "./item/monk/monkNormTR3";


    Dataset tr (training, 17 , 1);
    Dataset ts (test, 17 , 1);


    Network net = Network (17, 1, 3);
    net.learnBackPro( tr, ts, 1000 );


  //  double error = net.error_MSE(ts);
  //  cout << "Error MSE: " << error << endl;




//    double error = net.ClassifyTst(ts, 0.25);
//    cout << " Error(%): " << error << endl;

    return 0;
}

