#include<iostream>
#include<Dataset.h>

#include<network.h>
#include<hiddenlayer.h>
#include<outputlayer.h>
#include<Unit.h>

using namespace std;

int main()
{
    cout << "Main" << endl;
    cout.precision(5);
    cout << fixed;


    char training[] = "./item/monkTR1";
    char test[] = "./item/monkTest1";


    Dataset tr (training, 6 , 1);
    Dataset ts( test, 6, 1 );
    Network net = Network (6, 1, 3);
    net.learnBackPro( tr, 2000 );

    double error = net.ClassifyTst(ts, 0.5);
    cout << " Error: " << error << endl;

    net.Print_Weights();

   return 0;

}
