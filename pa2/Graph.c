/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#2
* Graph.c 
* Graph ADT 
*********************************************************************************/ 
#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INF -1
#define NIL -2

typedef struct GraphObj{
    List *neighbor;
    int order; // # of vertices
    int size; // # of edges
    int source;
    int* parent; //array of parent of vertex "i"
    int* distance; //array of dist from most recent source to vertex i
    int* color; //array of color of vertex "i"
}GraphObj;

Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->size = 0;
    G->source = NIL;
    G->order = n;
    G->neighbor = calloc(n+1,sizeof(List));
    G->parent = calloc(n+1,sizeof(List));
    G->distance = calloc(n+1,sizeof(List));
    G->color = calloc(n+1,sizeof(List));
    for (int i = 0; i < n+1; i++){
        G->neighbor[i] = newList();
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->color[i] = 0;
    }
    return G;

}

void freeGraph(Graph* pG){
    for (int i = 0; i <= (*pG)->order; i++){
        freeList(&((*pG)->neighbor[i]));
    }
    free((*pG)->neighbor);
    free((*pG)->color);
    free((*pG)->distance);
    free((*pG)->parent);
    free(*pG);
    *pG = NULL;
}
/*** Access functions ***/

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

int getSource(Graph G){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
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

int getDist(Graph G, int u){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u > getOrder(G) || u < 1){
        fprintf(stderr, "Graph Error: calling getDist() with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    if(G->source != NIL){
        return G->distance[u];
    }
    return INF;
}

void getPath(List L, Graph G, int u){
    // BFS not called == source is not found
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u > getOrder(G) || u < 1){
        fprintf(stderr, "Graph Error: calling getParent() with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    if (u == getSource(G)){
        append(L,u);
    }
    else if (G->parent[u] == NIL){
        append(L,NIL);
    }
    else{
        getPath(L, G, G->parent[u]);
        append(L,u);
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    G->size = 0;
    G->source = NIL;
    G->order = 0;
    for (int i = 0; i < getSize(G); i++){
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->color[i] = 0;
        clear(G->neighbor[i]);
    }

}

void addEdge(Graph G, int u, int v){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if((u<1) || (v<1) || u > getOrder(G) || v > getOrder(G)){
        fprintf(stderr, "Graph Error: calling addEdge() on invalid egde reference\n");
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
        fprintf(stderr, "Graph Error: calling addArc() on invalid egde reference\n");
        exit(EXIT_FAILURE);
    }
    //if theres nothing in the list then append 
    if(length(G->neighbor[u]) == 0){
        append(G->neighbor[u],v);
    }
    //if theres smth in the list
    else{
        //adding the node
        moveBack(G->neighbor[u]);
        while((get(G->neighbor[u])) > v){
            movePrev(G->neighbor[u]);
            if(index(G->neighbor[u]) == -1){
                break;
            }
        }
        //if your cursors at -1 then append
        if(index(G->neighbor[u]) == -1){
            prepend(G->neighbor[u],v);
        }
        //otherwise you can insert before
        else{
            insertAfter(G->neighbor[u],v);
        }
    }
    G->size ++;
}

void BFS(Graph G, int s){
    // preconditions
    if (!G) {
        fprintf(stderr, "Error in BFS(). empty graph.\n");
        exit(EXIT_FAILURE);
    }
    if (s<0) {
        fprintf(stderr, "Error in BFS(). s is negative.\n");
        exit(EXIT_FAILURE);
    }
    //iterating through the array
    for(int i = 1; i <= G->order; i++){
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->color[i] = 0;
    }
    G->source = s;
    //discovering the source s
    G->color[s] = 1; 
    G->distance[s] = 0;
    G->parent[s] = NIL;
    //constructing new list
    List Q = newList();
    //enqueue
    append(Q,s);
    //while length is not equal to 0
    while(length(Q) != 0){
        //using the list get fcn move to front of the neighbor list
        moveFront(Q);
        int x = get(Q);
        moveFront(G->neighbor[x]);
        for(int iter = 1; iter <= length(G->neighbor[x]); iter++){
            int y = get(G->neighbor[x]);
            if(G->color[y] == 0){ //y is undiscovered
                G->color[y] = 1; //discover y
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Q,y);
            }
            moveNext(G->neighbor[x]);
        }
        G->color[x] = 2; //finished x
        deleteFront(Q);
    }
    freeList(&Q);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    if (!G) {
        fprintf(stderr, "Error in pringGraph(). empty graph.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i <= G->order; i++){
        moveFront(G->neighbor[i]);
        fprintf(out, "%d: ",i );
        while(index(G->neighbor[i]) >  -1){
            fprintf(out, "%d ", get(G->neighbor[i]));
            moveNext(G->neighbor[i]);
        }
        fprintf(out, "\n");
    }
}