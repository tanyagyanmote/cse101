#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UNDEF -2
#define NIL 0

typedef struct GraphObj{
    List *adjList;
    int order; // # of vertices
    int size; // # of edges
    int* color; //array of color of vertex "i"
    int* parent; //array of parent of vertex "i"
    int* discover; //array of discover times for each vertex
    int* finish; //array of finished color of vertex "i"
}GraphObj;

Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->size = 0;
    G->order = n;
    G->adjList = calloc(n+1,sizeof(List));
    G->parent = calloc(n+1,sizeof(List));
    G->finish = calloc(n+1,sizeof(List));
    G->color = calloc(n+1,sizeof(List));
    G->discover = calloc(n+1,sizeof(List));
    for (int i = 0; i < n+1; i++){
        G->adjList[i] = newList();
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->color[i] = 0;
        G->finish[i] = UNDEF;
    }
    return G;

}

void freeGraph(Graph* pG){
    for (int i = 0; i <= (*pG)->order; i++){
        freeList(&((*pG)->adjList[i]));
    }
    free((*pG)->adjList);
    free((*pG)->color);
    free((*pG)->discover);
    free((*pG)->parent);
    free((*pG)->finish);
    free(*pG);
    *pG = NULL;
}

int getOrder(Graph G){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getParent(Graph G, int u){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u > getOrder(G) || u < 1){
        fprintf(stderr, "Graph Error: calling getParent() with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}


int getDiscover(Graph G, int u){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u > getOrder(G) || u < 1){
        fprintf(stderr, "Graph Error: calling getDiscover() with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u > getOrder(G) || u < 1){
        fprintf(stderr, "Graph Error: calling getFinish() with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];

}

void addEdge(Graph G, int u, int v){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if((u<1) || (v<1) || u > getOrder(G) || v > getOrder(G)){
        fprintf(stderr, "Graph Error: calling addEdge() on invalid vertex reference\n");
        exit(EXIT_FAILURE);
    }
    addArc(G,u,v);
    addArc(G,v,u);
    G->size --;
}
//puesdo give in oh: Mahyar
void addArc(Graph G, int u, int v){
    //preconditions
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if((u<1) || (v<1) || u > getOrder(G) || v > getOrder(G)){
        fprintf(stderr, "Graph Error: calling addArc() on invalid vertex reference\n");
        exit(EXIT_FAILURE);
    }
    //if theres nothing in the list then append 
    if(length(G->adjList[u]) == 0){
        append(G->adjList[u],v);
    }
    //if theres smth in the list
    else{
        //adding the node
        moveBack(G->adjList[u]);
        while((get(G->adjList[u])) > v){
            movePrev(G->adjList[u]);
            if(index(G->adjList[u]) == -1){
                break;
            }
        }
        //if your cursors at -1 then append
        if(index(G->adjList[u]) == -1){
            prepend(G->adjList[u],v);
        }
        //otherwise you can insert before
        else{
            insertAfter(G->adjList[u],v);
        }
    }
    G->size ++;
}

void Visit(Graph G, List S, int x, int *time){
    // BASE CASE
    List A = G->adjList[x];
    G->discover[x] = ++ (*time);
    G->color[x] = 1;
    for(int i = 0; i < length(A); i++){
        i = get(A);
        if(G->color[i]==0){
            G->parent[i] = x;
            Visit(G,S,i,(*time));
        }
    }
    G->color[x] = 2;
    G->finish[x] = ++ (*time);
    prepend(S,x);
}

void DFS(Graph G, List S){
    if (!G) {
        fprintf(stderr, "Error in BFS(). empty graph.\n");
        exit(EXIT_FAILURE);
    }
    //basecase
    for(int i =0;i < G->order;i++){
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    int time = 0;
    for(int i = 0; i<length(S);i++){
        i = get(S);
        if (G->color[i] == 0){
            Visit(G,S,i,&time);
        }
    }
    for(int i = 1; i <= G->order;i++){
        deleteBack(S);
    }
}

Graph transpose(Graph G){
    // BASE CASE
    Graph transpose = newGraph();
    // make a new graph 
    // iterate through the graph G:
    //      move to the front of the adj[i]
    //      while the data isn't -1:
    //          assign the data to some integer variable "x"
    //          call addArc on the new graph, y, and i
    //          move to the next element of the adj list
    // 
    return transpose;
}

Graph copyGraph(Graph G){
    // BASE CASE
    // same as copy list
    // create a new graph
    // iterate through the graph G:
    //    move to the front of adj[i]
    //    while the data isn't -1:
    //        call addArc on the new graph, i, and the data
    // return the new graph
}



void printGraph(FILE* out, Graph G){
    if (!G) {
        fprintf(stderr, "Error in pringGraph(). empty graph.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i <= G->order; i++){
        moveFront(G->adjList[i]);
        fprintf(out, "%d: ",i );
        while(index(G->adjList[i]) >  -1){
            fprintf(out, "%d ", get(G->adjList[i]));
            moveNext(G->adjList[i]);
        }
        fprintf(out, "\n");
    }
}