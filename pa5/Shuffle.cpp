/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#5
* Shuffle.cpp 
* Shuffling cards
*********************************************************************************/ 
#include "List.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void shuffle(List&D){
    List one;
    List two;
    int first_half = D.length()/2;
    int second_half = D.length()-first_half;
    //splitting first half
    D.moveFront();
    for(int i = 0;i<first_half;i++){
        one.insertBefore(D.peekNext());
        D.moveNext();
    }
    //second half
    for(int i = 0;i<second_half;i++){
        two.insertBefore(D.peekNext());
        D.moveNext();
    }
    one.moveFront();
    two.moveFront();
    D.moveFront();
    D.clear();
    //merging
    for(int i =0; i<first_half;i++){
        D.insertBefore(two.peekNext());
        two.moveNext();
        D.insertBefore(one.peekNext());
        one.moveNext();
    }
    if((first_half+second_half)% 2 != 0){
        D.insertBefore(two.peekNext());
    }
}

int main(int argc, char* argv[]) {
    int size_d = atoi(argv[1]);
    if (argc != 2) {
        cerr << "ERROR: incorrect number of arguments\n" << endl;
        exit(EXIT_FAILURE);
    }
    if (size_d < 1) {
        cerr << "ERROR: deck size is too small\n" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "deck size	 shuffle count" << endl;
	cout << "------------------------------" << endl;
    List Deck;
    List Deck_copy;
    int counter = 1;
    for(int i =1; i<= size_d;i++){
        for (int j = 0; j < i; j++) {
            Deck.insertBefore(j);
        }
        Deck_copy = Deck;
        shuffle(Deck);
        while(!(Deck == Deck_copy)){
            shuffle(Deck);
            counter++;
        }
        cout << setw(2) << left << i << "              " << setw(2) << left << counter << endl;
        Deck.clear();
        Deck_copy.clear();
        counter = 1;
    }

}