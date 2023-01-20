/********************************************************************************* 
* Tanya Gyanmote, tgyanmot 
* 2023 Winter CSE101 PA#1 
* Lex.c 
* Fucntion to alphabetize lines in a file 
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
    FILE *in, *out;
    int line_count;
    char line[MAX_LEN];
    char** strings;
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
    //read each line of input file, and counts it
    line_count = 0;
    while( fgets(line, MAX_LEN, in) != NULL)  {
        line_count++;
    }
    //restarting at the beg. of file
    rewind(in);
    int counter = 0;
    //allocating string array
    strings = (char **) calloc(line_count, sizeof(char*));
    //while loop puesdocode given by Sheel in office hours
    while(fgets(line, MAX_LEN, in) != NULL){
        //allocating memory for each string
        strings[counter] = malloc(strlen(line) * sizeof(char));
        //copying string from file to string array
        strncpy(strings[counter],line,strlen(line));
        //last -> NULL
        strings[counter][strlen(line)-1] = '\0';
        counter += 1;
    }
    List L = newList();
    append(L,0);
    //puesdo given by Simon office hours
    //for loop cursor starting at front of the array
    for(int i = 1; i< line_count; i++){
        moveFront(L);
        int count = length(L) - 1;
        //while the length of the list is > 1
        //if its in order move cursor to the next
        while(count > 0 && strcmp(strings[i],strings[get(L)]) > 0) {
            moveNext(L);
            count -= 1;
        }
        //if 1 is > than 2 then insert 1 after
        if(strcmp(strings[i],strings[get(L)]) > 0){
            insertAfter(L,i);
        }
        //else insert 1 before
        else{
            insertBefore(L,i);
        }
    }
    //moving cursor to the front, to print out the array
    moveFront(L);
    for (int i = 0; i < line_count; i++) {
        fprintf(out, "%s\n", strings[get(L)]);
        moveNext(L);
    }
    //freeing everything at the end 
    for (int i = 0; i < line_count; i++) {
        free(strings[i]);
    }
    free(strings);
    freeList(&L);
    fclose(in);
    fclose(out);
    return(0);
}
