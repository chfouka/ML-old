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


    char name[] = "./item/monkts";
    Dataset tr (name, 6 , 1 , 300);
    //cout << tr;

   Network net = Network (6, 1, 4);
   net.learnBackPro( tr, 6 );

   vector<double> pattern_nc ;
   pattern_nc.push_back(1);
   pattern_nc.push_back(2);
   pattern_nc.push_back(1);
   pattern_nc.push_back(1);
   pattern_nc.push_back(1);
   pattern_nc.push_back(2);

   //vector<double> out ;
   //out.push_back(1);
   //Pattern in = Pattern(in, out); 1 2 1 1 1 2 --> 1


   vector<double> result = net.Classify(pattern_nc);
   for( unsigned int i = 0; i<result.size(); i++)
       cout << "outTest: " << result[i] << endl;

   return 0;

}
