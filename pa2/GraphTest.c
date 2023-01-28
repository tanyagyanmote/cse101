/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#2
* GraphTest.c 
* Tests for Graph ADT 
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int n = 10;
   List V = newList();
   Graph G = newGraph(n);
   //testing constructor
   if (getOrder(G) != 10) {
      fprintf(stderr, "Graph G's vertices was not set to 10 -> getOrder fail");
      exit(EXIT_FAILURE);
   }
   if (getSize(G) != 0) {
      fprintf(stderr, "Graph G's edges was not set to 0 -> getSize fail");
      exit(EXIT_FAILURE);
   }
   if (getSource(G) != NIL) {
      fprintf(stderr, "Graph G's source not set to NIL -> getSource fail");
      exit(EXIT_FAILURE);
   }
   if (getParent(G,1) != NIL) {
      fprintf(stderr, "Graph G's parent not set to NIL -> getParent fail");
      exit(EXIT_FAILURE);
   }
   if (getDist(G,1) != INF) {
      fprintf(stderr, "Graph G's distance not found correctly -> getDist fail");
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

   printGraph(stdout, G);

   //testing accesss fcns
   BFS(G, 1);
   if (getParent(G,2) != 1) {
      fprintf(stderr, "Graph G's parent was not found correctly -> getParent fail");
      exit(EXIT_FAILURE);
   }
   if (getDist(G,2) != 1) {
      fprintf(stderr, "Graph G's distance was not found correctly -> getDist fail");
      exit(EXIT_FAILURE);
   }
   if (getSize(G) != 13) {
      fprintf(stderr, "Graph G's size was not found correctly -> getSize fail");
      exit(EXIT_FAILURE);
   }
   if (getSource(G) != 1) {
      fprintf(stderr, "Graph G's source was not found correctly -> getSource fail");
      exit(EXIT_FAILURE);
   }

   addEdge(G, 3, 4);
   BFS(G, 1);
   getPath(V, G, 2);
   printList(stdout, V);
   printf("\n");

   makeNull(G);
   //checking if makeNull worked
   if (getSize(G) != 0) {
      fprintf(stderr, "Graph G's size was not found correctly -> getSize fail");
      exit(EXIT_FAILURE);
   }
   if (getSource(G) != NIL) {
      fprintf(stderr, "Graph G's source was not found correctly -> getSource fail");
      exit(EXIT_FAILURE);
   }
   // Free objects 
   freeList(&V);
   freeGraph(&G);

   return(0);
}
/*
output:

1: 2 3 4 
2: 1 3 8 
3: 1 2 7 
4: 1 9 
5: 6 7 10 
6: 5 9 
7: 3 5 8 
8: 2 7 
9: 4 6 
10: 5 
1 2
*/