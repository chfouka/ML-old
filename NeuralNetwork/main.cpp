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

    char name[] = "./item/monkts";
    Dataset tr (name, 6 , 1 , 124);
    //cout << tr;

   Network net = Network (6, 1, 4);
   // net.learnBackPro( tr );

    return 0;

}
