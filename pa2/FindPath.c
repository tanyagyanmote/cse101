/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#2 
* FindPath.c 
* Uses the Graph ADT to find shortest paths between pairs of vertices
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[]){
    int n,u,v; 
    FILE *in, *out;
    //check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    //open files for reading and writing 
    in = fopen(argv[1], "r");
        if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    //puesdo give in oh: Mahyar
    fscanf(in, " %d", &n);
    Graph G = newGraph(n);
    u = 1;
    v = 1;
    //making sure vertex is valid
    while(u != 0 || v != 0){
        fscanf(in, " %d%d", &u, &v);
        if((v == 0) || (u == 0)){
            break;
        }
        addEdge(G,u,v);
    }
    //printing the graph
    printGraph(out,G);
    List L = newList();
    int u1,v1;
    while(u1 != 0 || v1 != 0){
        fscanf(in, " %d%d", &u1, &v1);
        if((v1 == 0) || (u1 == 0)){
            break;
        }
        BFS(G,u1);
        if(getDist(G,v1) == INF){
            fprintf(out, "\nThe distance from %d to %d is infinity\n", u1, v1);
            fprintf(out, "No %d-%d path exists\n", u1, v1);
        }
        else{
            fprintf(out, "\nThe distance from %d to %d is %d\n", u1, v1, getDist(G, v1));
            fprintf(out, "A shortest %d-%d path is: ", u1, v1);
            getPath(L,G,v1);
            printList(out,L);
        }
        clear(L);
    }
    //free everything
    freeGraph(&G);
    freeList(&L);
    fclose(in);
    fclose(out);
    return 0;
}

