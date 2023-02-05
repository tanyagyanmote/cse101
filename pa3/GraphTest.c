/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#3
// GraphTest.c
// Test client for the Graph ADT
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
    int n = 10;
    Graph G = newGraph(n);
    List S = newList();
    for (int i = 1; i <= n; i++) {
        append(S, i);
    }
    //testing constructor
    if (getOrder(G) != 10) {
        fprintf(stderr, "Graph G's vertices was not set to 10 -> getOrder fail");
        exit(EXIT_FAILURE);
    }
    if (getSize(G) != 0) {
        fprintf(stderr, "Graph G's edges was not set to 0 -> getSize fail");
        exit(EXIT_FAILURE);
    }
    if (getParent(G,1) != NIL) {
        fprintf(stderr, "Graph G's parent not set to NIL -> getParent fail");
        exit(EXIT_FAILURE);
    }
    if (getDiscover(G,1) != UNDEF) {
        fprintf(stderr, "Graph G's discover time not found correctly -> getDiscover fail");
        exit(EXIT_FAILURE);
    }
    if (getFinish(G,1) != UNDEF) {
        fprintf(stderr, "Graph G's finish time not found correctly -> getFinish fail");
        exit(EXIT_FAILURE);
    }
    //adding vertices checking addEdge or addArc
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 1);
    addEdge(G, 4, 1);
    addEdge(G, 5, 6);
    addEdge(G, 7, 3);
    addEdge(G, 9, 4);
    addEdge(G, 10, 5);
    addEdge(G, 7, 5);
    addEdge(G, 8, 2);
    addEdge(G, 7, 8);
    addEdge(G, 9, 6);
    addArc(G, 3, 6);
    //making sure a duplicate doesn't get added
    addArc(G, 6, 3);

    fprintf(stdout,"The Original Graph: \n");
    printGraph(stdout, G);

    //testing accesss fcns
    DFS(G, S);
    if (getParent(G,2) != 1) {
        fprintf(stderr, "Graph G's parent was not found correctly -> getParent fail");
        exit(EXIT_FAILURE);
    }
    if (getOrder(G) != 10) {
        fprintf(stderr, "Graph G's vertices was not found correctly -> getOrder fail");
        exit(EXIT_FAILURE);
    }
    if (getSize(G) != 14) {
        fprintf(stderr, "Graph G's size was not found correctly -> getSize fail");
        exit(EXIT_FAILURE);
    }
    if (getDiscover(G,5) != 5) {
        fprintf(stderr, "Graph G's discover time was not found correctly -> getDiscover fail");
        exit(EXIT_FAILURE);
    }
    if (getFinish(G,4) != 15) {
        fprintf(stderr, "Graph G's finish time was not found correctly -> getFinish fail");
        exit(EXIT_FAILURE);
    }

    Graph T = transpose(G);
    Graph C = copyGraph(G);
    fprintf(stdout,"\nThe Transposed Graph: \n");
    printGraph(stdout, T);
    fprintf(stdout,"\nThe Copied Graph: \n" );
    printGraph(stdout, C);

    // Free objects 
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);


    return(0);
}
    /*
    output:
    The Original Graph: 
    1: 2 3 4 
    2: 1 3 8 
    3: 1 2 6 7 
    4: 1 9 
    5: 6 7 10 
    6: 3 5 9 
    7: 3 5 8 
    8: 2 7 
    9: 4 6 
    10: 5 

    The Transposed Graph: 
    1: 2 3 4 
    2: 1 3 8 
    3: 1 2 6 7 
    4: 1 9 
    5: 6 7 10 
    6: 3 5 9 
    7: 3 5 8 
    8: 2 7 
    9: 4 6 
    10: 5 

    The Copied Graph: 
    1: 2 3 4 
    2: 1 3 8 
    3: 1 2 6 7 
    4: 1 9 
    5: 6 7 10 
    6: 3 5 9 
    7: 3 5 8 
    8: 2 7 
    9: 4 6 
    10: 5 

    */


