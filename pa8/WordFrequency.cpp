#include<iostream>
#include<string>
#include<stdexcept>
#include<iostream>
#include<fstream>
#include "Dictionary.h"
#include <algorithm> 

using namespace std;

int main(int argc, char * argv[]){

    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line;
    string token;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789%";

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // read each line of input file, then count and print tokens 
    Dictionary D;
    while( getline(in, line) )  {
        len = line.length();
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
        while( token!="" ){  // we have a token
            //puesdo idea to use transform given by arka
            transform(token.begin(), token.end(), token.begin(), ::tolower);
            if((D.contains(token))){
                D.getValue(token) += 1;
			}
			else{
                D.setValue(token, 1);

			}
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }
        // print tokens in this line
    }

    out << D << endl;

    // close files 
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
