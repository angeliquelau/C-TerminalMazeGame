#ifndef MAZE_H
#define MAZE_H

#include "LinkedList.h"

void printMapLL(void *data);
void printLastMap(LinkedList *mapLL, listFunc funcPtr);
void freeNode(void *data);

typedef struct 
{
    char userFace;
    int userX;
    int userY;
    int snakeX;
    int snakeY;
}MapEntry;

#endif