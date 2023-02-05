/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#3
* FindCompenent.c 
* Finds SCC from a Graph
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <ctype.h>
#include "Graph.h"

int main(int argc, char * argv[]){

    // needed variables
    int n, u, v, comp; // n = #vertices; u, v = vertex of two edges
    comp = 0;
    FILE *in, *out;  // input output files

    // check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    if (in==NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out==NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // scan the first line or first digit to get # vertex
    fscanf(in, " %d", &n);

    Graph G = newGraph(n);
    u = 1;
    v = 1;

    while(u != 0 || v != 0){
        fscanf(in, " %d%d", &u, &v);
        if((v == 0) || (u == 0)){
            break;
        }
        addArc(G,u,v);
    }
    //printing graphs adj list
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out,G);
    Graph T = transpose(G);
    List S = newList();
    for(int i =1; i <= getOrder(G);i++){
        append(S,i);
    }
    //calling DFS on the copied and transposed Graph
    DFS(G,S);
    DFS(T,S);
    //puesdocode from Mikes oh
    for(moveFront(S); index(S) >= 0; moveNext(S)){
        if(getParent(T,get(S)) == NIL){
            comp += 1;
        }
    }    

    fprintf(out, "G contains %d strongly connected components:\n", comp);

    int x = 0;
    //allocating mem for the SCC List 
    List* C = calloc(comp,sizeof(List));
    for (int i = 0; i < comp; i++){
        C[i] = newList();
    }
    //counting the # of SCC by checking if the parent of graphs node is nil
    for(moveBack(S); index(S) >= 0; movePrev(S)){
        int y = get(S);
        prepend(C[x],y);
        if(getParent(T,get(S)) == NIL){
            x++;
        }
    }  
    //printing the SCC
    for(int i =0;i < comp; i++){
        fprintf(out, "Component %d: ", i+1);
        printList(out, C[i]);
        fprintf(out, "\n");
    }
    // create and allocate an array of Lists (*List C)to store the strong components

    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    for (int i = 0; i < comp; i++){
        freeList(&(C[i]));
    }
    free(C);
    fclose(in);
    fclose(out);
    return 0;
}