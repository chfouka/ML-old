#ifndef DATASET_H
#define DATASET_H

#include<fstream>
#include <limits>
#include <float.h>
#include <iostream>
#include"Pattern.h"


using namespace std;

class Dataset
{
public:
    unsigned int numinputs;
    unsigned int numoutputs;
    vector<Pattern> data;

    vector<double> maxInputs;
    vector<double> minInputs;
    vector<double> maxOutputs;
    vector<double> minOutputs;



public:
    Dataset(){}
    Dataset(vector<Pattern> patterns, unsigned int inputs, unsigned int outputs){
        for(unsigned int i = 0; i<patterns.size(); i++)
            data.push_back(patterns.at(i));

        numinputs = inputs;
        numoutputs = outputs;

    }

    Dataset(char* filename, unsigned int inputs, unsigned int outputs){

        numinputs = inputs;
        numoutputs = outputs;

        maxInputs.assign(numinputs, - std::numeric_limits<double>::max() );
        minInputs.assign(numinputs, std::numeric_limits<double>::max() );
        maxOutputs.assign(numoutputs, - std::numeric_limits<double>::max());
        minOutputs.assign(numoutputs, std::numeric_limits<double>::max());


        ifstream datafile(filename);
        double d;        

        while( datafile.good() ){
            vector<double> in;
            vector<double> out;
            for(unsigned int c = 0; c < numinputs; c++){
                datafile >> d;
                if (datafile.eof())
                    break;

                in.push_back(d);               

                if(d > maxInputs.at(c))
                    maxInputs.at(c) = d;
                if( d < minInputs.at(c) )
                    minInputs.at(c) = d;
            }

            for(unsigned int c = 0; c < numoutputs; c++){
                datafile >> d;
                if (datafile.eof())
                    break;
                out.push_back(d);

                if(d > maxOutputs.at(c))
                    maxOutputs.at(c) = d;
                if( d < minOutputs.at(c) )
                    minOutputs.at(c) = d;
            }

            if (datafile.eof())
                break;

            if(in.size()!= numinputs || out.size() != numoutputs){
                cerr << "Training set not good" <<  endl;
                break;
            }

            data.push_back(Pattern(in,out));

        }
    }

    void split( Dataset* training, Dataset* validation ){
        unsigned int size = data.size();
        unsigned int i;
        for(i = 0; i<2*size/3; i++)
            training->data.push_back(data.at(i));
        for(;i<size; i++)
            validation->data.push_back(data.at(i));
        training->maxInputs = maxInputs;
        training->maxOutputs = maxOutputs;
        training->minInputs = minInputs;
        training->minOutputs = minOutputs;

        validation->maxInputs = maxInputs;
        validation->maxOutputs = maxOutputs;
        validation->minInputs = minInputs;
        validation->minOutputs = minOutputs;

    }

    void scale( ){
        for( unsigned int j = 0; j < this->data.size(); j++){
            Pattern* p = &data.at(j);
            for(unsigned int i = 0; i<data.at(j).inputs.size(); i++ ){
                double average = ( maxInputs[i] + minInputs[i] ) / 2.0;
                double coef = 2 / ( maxInputs[i] - minInputs[i] );
                p->inputs.at(i) = ( p->inputs.at(i) - average ) * coef;                
            }
            for(unsigned int i = 0; i<data.at(j).outputs.size(); i++ ){
                double average = ( maxOutputs[i] + minOutputs[i] ) / 2.0;
                double coef = 2 / ( maxOutputs[i] - minOutputs[i] );                
                p->outputs.at(i) = ( p->outputs.at(i) - average ) * coef;                
            }
        }
    }

    void scale(Pattern p){
        for(unsigned int i = 0; i<p.inputs.size(); i++ ){
            double average = ( maxInputs[i] + minInputs[i] ) / 2.0;
            double coef = 2 / ( maxInputs[i] - minInputs[i] );
            p.inputs.at(i) = ( p.inputs.at(i) - average ) * coef;
        }
        for(unsigned int i = 0; i<p.outputs.size(); i++ ){
            double average = ( maxOutputs[i] + minOutputs[i] ) / 2.0;
            double coef = 2 / ( maxOutputs[i] - minOutputs[i] );
            p.outputs.at(i) = ( p.outputs.at(i) - average ) * coef;
        }

    }

    void descale(){
        for( unsigned int j = 0; j < this->data.size(); j++){
            for(unsigned int i = 0; i<data.at(j).inputs.size(); i++ ){
                double average = ( maxInputs[i] + minInputs[i] ) / 2;
                double coef = 2 / ( maxInputs[i] - minInputs[i] );
                data.at(j).inputs.at(i) = ( data.at(j).inputs.at(i) / coef ) + average;
            }
            for(unsigned int i = 0; i<data.at(j).outputs.size(); i++ ){
                double average = ( maxOutputs[i] + minOutputs[i] ) / 2;
                double coef = 2 / ( maxOutputs[i] - minOutputs[i] );
                data.at(j).outputs.at(i) = ( data.at(j).outputs.at(i) / coef ) + average;
            }
        }
    }

    void descale( Pattern p ){
        for(unsigned int i = 0; i<p.inputs.size(); i++ ){
            double average = ( maxInputs[i] + minInputs[i] ) / 2;
            double coef = 2 / ( maxInputs[i] - minInputs[i] );
            p.inputs.at(i) = ( p.inputs.at(i) / coef ) + average;
        }

        for(unsigned int i = 0; i<p.outputs.size(); i++ ){
            double average = ( maxOutputs[i] + minOutputs[i] ) / 2;
            double coef = 2 / ( maxOutputs[i] - minOutputs[i] );
            p.outputs.at(i) = ( p.outputs.at(i) / coef ) + average;
        }
    }

    void print_maxminvals( ){
        for( unsigned int i = 0; i< numinputs; i++ )
            cout << "(" <<  minInputs.at(i) << " " << maxInputs.at(i) << ") " << endl;


        for(unsigned int i = 0; i< numoutputs; i++)
            cout << "(" <<  minOutputs.at(i) << " " << maxOutputs.at(i) << ") " << endl;

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
