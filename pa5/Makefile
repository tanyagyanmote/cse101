#********************************************************************************* 
# Tanya Gyanmote, tgyanmot 
# 2023 Winter CSE101 PA#5
# MakeFile 
# Complies and executes the program
# ********************************************************************************* 
#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListClient     make ListClient
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

Shuffle : Shuffle.o List.o
	g++ -std=c++17 -Wall -g -o Shuffle Shuffle.o List.o 

Shuffle.o : List.h Shuffle.cpp
	g++ -std=c++17 -Wall -g -c Shuffle.cpp

ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -g -o ListTest ListTest.o List.o 

ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -g -c ListTest.cpp

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -g -c List.cpp

clean :
	rm -f Shuffle Shuffle.o ListTest ListTest.o List.o

check1 : ListTest
	valgrind --leak-check=full ListTest

check2 : Shuffle
	valgrind --leak-check=full Shuffle 35

