/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#8
* Order.cpp 
* Doing operations on a dictionary
*********************************************************************************/ 

#include"Dictionary.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(int argc, char * argv[]) {
	ifstream in;
	ofstream out;
	if(argc != 3) {
		cerr << "Usage: <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}
	in.open(argv[1]);
	if(!in.is_open()) {
		cerr << "Unable to open file for reading" << endl;
		return(EXIT_FAILURE);
	}

	out.open(argv[2]);
	if(!out.is_open()) {
		cerr << "Unable to open file for writing" << endl;
		return(EXIT_FAILURE);
	}

	string key;
	Dictionary D;
	int num = 1;

	while(getline(in, key)) {
		D.setValue(key,num);
		num += 1;
	}

	out << D << endl << D.pre_string();
    
	in.close();
	out.close();

	return(EXIT_SUCCESS);
}