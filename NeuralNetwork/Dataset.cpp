#include "Dataset.h"

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

/*
   Dataset::Dataset(){}


   Dataset::Dataset( char* filename, int inputs, int outputs, int tot, int type){

       numinputs = inputs;
       numoutputs = outputs;
       datatype = type;
       numpatterns = tot;

       data = new double [numpatterns * (numinputs + numoutputs)];

       ifstream datafile;

       datafile.open(filename);
       if( ! datafile.is_open() )
       {cout << "file not opened" << endl ; return;}

       for( int r = 0; r < numpatterns; r++ ){
           for(int c = 0; c < numinputs+numoutputs; c++)
               datafile >> data[r*(numinputs+numoutputs)+c];
       }

   }

   void Dataset::printdata(){

       for( int r = 0; r < numpatterns; r++ ){
           for(int c = 0; c < numinputs+numoutputs; c++){
               cout << data[r*(numinputs+numoutputs)+c];
               cout << " " ;
           }
           cout << endl;

       }

   }



*/

