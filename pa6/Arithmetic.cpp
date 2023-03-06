/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#6
* Arithmetic.cpp 
* Doing arithmetic operations on big integers
*********************************************************************************/ 

// import sys

// # check number of command line arguments
// if len(sys.argv)!=3:
//    print("Usage: "+sys.argv[0]+" <input file> <output file>")
//    quit()
// # end if

// # open files
// f1 = open(sys.argv[1], 'r')
// f2 = open(sys.argv[2], 'w')

// # read from f1
// A = int( f1.readline() ) # line 1
// f1.readline()            # line 2
// B = int( f1.readline() ) # line 3

// # write lines to f2
// f2.write(str(A)+'\n\n')
// f2.write(str(B)+'\n\n')
// f2.write(str(A+B)+'\n\n')
// f2.write(str(A-B)+'\n\n')
// f2.write(str(A-A)+'\n\n')
// f2.write(str(3*A-2*B)+'\n\n')
// f2.write(str(A*B)+'\n\n')
// f2.write(str(A**2)+'\n\n')
// f2.write(str(B**2)+'\n\n')
// f2.write(str(9*A**4+16*B**5)+'\n\n')

// # close files
// f1.close()
// f2.close()

#include<iostream>
#include<string>
#include<stdexcept>
#include<iostream>
#include<fstream>
#include"BigInteger.h"

using namespace std;

int main(int argc, char** argv){
    ifstream in;
	ofstream out;
    string number;
    if (argc != 3){
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}
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

    getline(in, number);
	BigInteger A = number;
	getline(in, number);
	getline(in, number);
	BigInteger B = number;

	out << A << endl << endl;
	out << B << endl << endl;
    out << A+B << endl << endl;
	out << A-B << endl << endl;
	out << A-A << endl << endl;


    // BigInteger C1 = A + A + A;
    BigInteger C = BigInteger("3");
    C *= A;
    BigInteger D = B + B;

	// out << C << endl << endl;
	// out << D << endl << endl;

	out << C-D << endl << endl;

	out << A*B << endl << endl;
    out << A*A << endl << endl;
    out << B*B << endl << endl;

    BigInteger E = A * A * A * A;
    BigInteger F = B * B * B * B * B;
    
    BigInteger E2 = E + E + E + E + E + E + E + E + E;
    BigInteger F2 = F + F + F + F + F + F + F + F + F + F + F + F + F + F + F + F;

	out << E2+F2 << endl << endl;
    
    in.close();
	out.close();

	return(EXIT_SUCCESS);


}