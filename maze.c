/*
* Name: Angelique Emily Lau En Xian
* File name: maze.c
* Design date: 22 August 2021
* Last MOD: 3 October 2021
* Note: part of the especially those related to struct is guided by Dr. Ling
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"
#include "printAndMove.h"
#include "terminal.h"
#include "LinkedList.h"

int main(int argc, char *argv[])
{
    int i;

    if(argc <= 1)
    {
        printf("Too little parameters!\n");
    }
    else if(argc > 2)
    {
        printf("Too many parameters!\n");
    }
    else
    {
        int **mapData;
        char **map;
        int numObj, row, col, userPosX, userPosY, goalPosX, goalPosY, snakePosX, snakePosY;
        char *filename;
        char action = ' ';
        FILE *inPtr = NULL;
        LinkedList *mapLL = NULL;
        MapEntry *newEntry = NULL;
        MapEntry *prevEntry = NULL;
        mapLL = createLinkedList(); /*create linked list*/

        filename = argv[1]; /*getting the filename from command line arguments*/

        inPtr = fopen(filename, "r");
        if(inPtr == NULL)
        {
            perror("Could not open file.");
        }
        else
        {
            /*getting the number of objects, row and column*/
            fscanf(inPtr, "%d %d %d", &numObj, &row, &col);
            /*printf("hi\n");*/
            /*printf("%d %d %d\n", numObj, row, col);*/ /*testing*/

            /*printf("hi2\n");*/
            /*dynamically allocate memory for 2d array*/
            mapData = (int**)malloc(numObj * sizeof(int*));
            for(i = 0; i < numObj; i++)
            {
                mapData[i] = (int*)malloc(3 * sizeof(int));
            }

            i = 0;
            /*getting coordinates of the objects*/
            /*loop until it reaches EOF*/
            while(fscanf(inPtr, "%d %d %d", &mapData[i][0], &mapData[i][1], &mapData[i][2]) != EOF)
            {
                if(mapData[i][2] == 0)
                {
                    userPosX = mapData[i][0];
                    userPosY = mapData[i][1];
                }
                if(mapData[i][2] == 1)
                {
                    snakePosX = mapData[i][0];
                    snakePosY = mapData[i][1];
                }
                if(mapData[i][2] == 2)
                {
                    goalPosX = mapData[i][0];
                    goalPosY = mapData[i][1];
                }
                i++;
            } 
            /*testing*/
            /*for(i = 0; i < numObj; i++)
            {
                printf("hello: %d %d %d\n", mapData[i][0], mapData[i][1], mapData[i][2]);

                if(mapData[i][2] == 3)
                {
                    printf("\nwall: %d %d\n\n", mapData[i][0], mapData[i][1]);
                }
            }*/
            fclose(inPtr); 
        }

        /*printf("%d, %d, %d\n", numObj, row, col);*/ /*for testing*/

        /*creating 2D array for map*/
        map = (char**)malloc(row * sizeof(char*));
        for(i = 0; i < row; i++)
        {
            map[i] = (char*)malloc(col * sizeof(char));
        }
        /*testing*/
        /*printf("user and goal: %d %d %d %d %d %d\n", userPosX, userPosY, goalPosX, goalPosY, snakePosX, snakePosY);*/

        /*allocate memory for newEntry*/
        newEntry = (MapEntry *)malloc(sizeof(MapEntry));
        map[userPosX][userPosY] = '^';
        /*printing the map, with the original position of the user character facing upwards*/
        printMap(mapData, map, action, numObj, row, col, userPosX, userPosY, map[userPosX][userPosY], goalPosX, goalPosY, snakePosX, snakePosY);

        /*store the original position in linked list*/
        newEntry->userFace = map[userPosX][userPosY];
        newEntry->userX = userPosX;
        newEntry->userY = userPosY;
        newEntry->snakeX = snakePosX;
        newEntry->snakeY = snakePosY;
        insertStart(mapLL, newEntry);

        /*keep looping if user's x and y is not the same as snake or goal's x and y*/
        while((userPosX != goalPosX || userPosY != goalPosY) && (userPosX != snakePosX || userPosY != snakePosY))
        {
            /*create new entry each time it loops*/
            newEntry = (MapEntry *)malloc(sizeof(MapEntry));
            /*the part where user enters the movement of the character without having to 
            press enter each time*/
            disableBuffer();
            scanf(" %c", &action); /*only get one character input*/
            enableBuffer();

            /*getting the updated position of the player only if user enter w,a,s,d*/
            if(action == 'a' || action == 's' || action == 'w' || action == 'd')
            {
                userPosX = updateUserX(action, map, userPosX, userPosY);
                userPosY = updateUserY(action, map, userPosX, userPosY);
                snakePosX = updateSnakeX(action, map, snakePosX, snakePosY, userPosX, userPosY, row);
                snakePosY = updateSnakeY(action, map, snakePosX, snakePosY, userPosX, userPosY, col);
                
                if(((userPosX >= 1 && userPosX <= row - 2) && (userPosY >= 1 && userPosY <= col - 2)) && ((snakePosX >= 1 && snakePosX <= row - 2) && (snakePosY >= 1 && snakePosY <= col - 2)) && (map[userPosX][userPosY] != 'o'))
                {
                    /*printing the map with the latest position of the character*/
                    printMap(mapData, map, action, numObj, row, col, userPosX, userPosY, map[userPosX][userPosY], goalPosX, goalPosY, snakePosX, snakePosY);
                }
                else 
                {
                    /*if user enters a position which makes the userPosX or userPosY goes out of 
                    bound or into the wall, then it will change the num back to the previous ones
                    so that it stays in the playable area and not go into the wall.
                    also, if user is in a corner and still wants to move but cannot because facing
                    a wall or the boundary, then it will change the facing direction of the 
                    character to the action user entered*/
                    if(action == 'w')
                    {
                        userPosX++;
                        map[userPosX][userPosY] = '^';
                    }
                    else if(action == 's')
                    {
                        userPosX--;
                        map[userPosX][userPosY] = 'v';
                    }
                    else if(action == 'a')
                    {
                        userPosY++;
                        map[userPosX][userPosY] = '<';
                    }
                    else if(action == 'd')
                    {
                        userPosY--;
                        map[userPosX][userPosY] = '>';
                    }
                    /*snakePosX = updateSnakeX(action, map, snakePosX, snakePosY, userPosX, userPosY, row);
                    snakePosY = updateSnakeY(action, map, snakePosX, snakePosY, userPosX, userPosY, col);*/
                    printMap(mapData, map, action, numObj, row, col, userPosX, userPosY, map[userPosX][userPosY], goalPosX, goalPosY, snakePosX, snakePosY);       
                }

                /*store data into struct each time it loops*/
                newEntry->userFace = map[userPosX][userPosY];
                newEntry->userX = userPosX;
                newEntry->userY = userPosY;
                newEntry->snakeX = snakePosX;
                newEntry->snakeY = snakePosY;
                insertStart(mapLL, newEntry);
                /*printLinkedList(mapLL, &printMapLL);*/ /*testing to see if the data stored is correct*/
            }
            else if(action == 'u')
            {
                prevEntry = removeStart(mapLL); /*get the remove node*/
                
                /*if prevEntry is not null, then we get the data and store into the respective variables*/
                if(prevEntry != NULL)
                {
                    /*post assignment: why did i typecast? it seems like its not needed??? the heck?*/
                    userPosX = (/*(MapEntry *)*/prevEntry)->userX;
                    userPosY = (/*(MapEntry *)*/prevEntry)->userY;
                    snakePosX = (/*(MapEntry *)*/prevEntry)->snakeX;
                    snakePosY = (/*(MapEntry *)*/prevEntry)->snakeY;
                    map[userPosX][userPosY] = (/*(MapEntry *)*/prevEntry)->userFace;
                }
                /*and print it out*/
                printMap(mapData, map, action, numObj, row, col, userPosX, userPosY, map[userPosX][userPosY], goalPosX, goalPosY, snakePosX, snakePosY);
                /*testing to see if the data stored is correct*/        
                /*printLinkedList(mapLL, &printMapLL);*/ /*just to print out and see what is stored in the linked list*/
            }
            
            /*printf("[after]\nuser x, y: %d, %d\nsnake x, y: %d, %d\n", userPosX, userPosY, snakePosX, snakePosY);*/ /*just for debugging*/

            /*when it reaches the coordinates of the goal, it will enter this part*/
            if(userPosX == goalPosX && userPosY == goalPosY)
            {
                printf("YOU WIN!\n");
            }
            /*if player ends up in the same coordinates as snake, then it will enter this part*/
            if(snakePosX == userPosX && snakePosY == userPosY)
            {
                printf("YOU LOSE, TRY AGAIN.\n");
            }
        }

        /*free the dynamically allocated memory for linked list*/
        freeLinkedList(mapLL, &freeNode);
        
        /*free the entries*/
        free(prevEntry); 

        /*free the 2d arrays*/
        for(i = 0; i < numObj; i++) 
        {
            free(mapData[i]);
        }
        free(mapData);
        mapData = NULL;

        for(i = 0; i < row; i++)
        {
            free(map[i]);
        }
        free(map);
        map = NULL;
    }
    
    return 0;
}

/*used testing to see if the data stored is correct*/   
/*method to print everything in the struct stored in the linked list*/
/*void printMapLL(void *data) 
{   
    printf("user face: %c, user pos: %d %d, snake pos: %d %d\n", ((MapEntry *)data)->userFace, ((MapEntry *)data)->userX, ((MapEntry *)data)->userY, ((MapEntry *)data)->snakeX, ((MapEntry *)data)->snakeY);
}*/

void freeNode(void *data)
{
    free((MapEntry *)data);    
}