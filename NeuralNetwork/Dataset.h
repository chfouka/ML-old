#ifndef DATASET_H
#define DATASET_H

#include<fstream>
#include <iostream>
#include"Pattern.h"

using namespace std;

class Dataset
{
public:
    int numinputs;
    int numoutputs;
    vector<Pattern> data;



public:
    Dataset(){}
    Dataset(char* filename, int inputs, int outputs){

        numinputs = inputs;
        numoutputs = outputs;

        ifstream datafile(filename);

        //datafile.open(filename);
        /*if( ! datafile.is_open() )
        {cout << "file not opened" << endl ; return;}
        */

        double d;

        while( datafile.good() ){
            vector<double> in;
            vector<double> out;
            for(int c = 0; c < numinputs; c++){
                datafile >> d;
                in.push_back(d);
            }
            for(int c = 0; c < numoutputs; c++){
                datafile >> d;
                out.push_back(d);
            }

            if(in.size()!= numinputs || out.size() != numoutputs){
                cerr << "Training set not good" <<  endl;
                break;
            }

            data.push_back(Pattern(in,out));
        }

        data.pop_back();


    }

    friend ostream& operator << (ostream& out, Dataset& d){
        for(unsigned int i = 0; i<d.data.size(); i++){
            out << d.data[i];
            out << endl;
    }
        return out;
    }

};

#endif // DATASET_H
