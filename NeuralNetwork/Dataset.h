#ifndef DATASET_H
#define DATASET_H

#include<fstream>
#include <iostream>
#include"Pattern.h"

using namespace std;

class Dataset
{
public:
    int numpatterns;
    int numinputs;
    int numoutputs;
    vector<Pattern> data;



public:
    Dataset(){}
    Dataset(char* filename, int inputs, int outputs, int tot){

        numinputs = inputs;
        numoutputs = outputs;
        numpatterns = tot;

        ifstream datafile(filename);

        //datafile.open(filename);
        if( ! datafile.is_open() )
        {cout << "file not opened" << endl ; return;}

        double d;
        for( int r = 0; r < numpatterns; r++ ){
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

            data.push_back(Pattern(in,out));
        }
    }

    friend ostream& operator << (ostream& out, Dataset& d){
        for(unsigned int i = 0; i<d.data.size(); i++)
            out << d.data[i];

        return out;
    }

};

#endif // DATASET_H
