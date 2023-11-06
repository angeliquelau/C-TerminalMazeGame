/*
* Name: Angelique Emily Lau En Xian
* File name: printAndMove.c
* Design date: 22 August 2021
* Last MOD: 3 October 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include "printAndMove.h"
#include "LinkedList.h"

void printMap(int **mapData, char **map, char action, int numObj, int row, int col, int updatedX, int updatedY, char face, int goalX, int goalY, int snakeX, int snakeY)
{
    int i, j, m;
    
    system("clear");
    /*printf("row col: %d %d\n", newEntry->row, newEntry->col);*/

    /*printf("[before] x, y: %d, %d\n", updatedX, updatedY);*/ /*for testing*/

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            /*borders*/
            if(i == 0 || i == row - 1)
            {
                map[i][j] = '-';
            }
            else if(j == 0 || j == col - 1)
            {
                map[i][j] = '|';
            }
            /*assuming the first two lines of the 2D array are user's character and goal's
            coordinates*/
            /*setting the position of the user's character into the 2D array*/
            else if((i == updatedX && j == updatedY) || (i == snakeX && j == snakeY))
            {
                printMove(action, updatedX, updatedY, snakeX, snakeY, map, face);
                map[snakeX][snakeY] = '~';
            }
            /*setting the goal into the 2D array*/
            else if(i == goalX && j == goalY) 
            {
                map[i][j] = 'x';
            }
            else 
            {
                /*for all the other coordinates that are not assigned to a character,
                set them to white space*/
                map[i][j] = ' ';

                /*printing the rest of the coordinates assigned as the walls*/
                for(m = 0; m < numObj; m++)
                {
                    if((i == mapData[m][0] && j == mapData[m][1]) && mapData[m][2] == 3)
                    {
                        map[i][j] = 'o';             
                    }
                }
            }
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int updateUserY(char action, char **map, int userX, int userY)
{
    switch(action)
    {
        /*if the coordinates the user wants to move to is a space, then update user 
        character position depending on user input*/
        case 'a':
            if(map[userX][userY--] == ' ')
            {
                map[userX][userY] = '<';
            }
            break;

        case 'd':
            if(map[userX][userY++] == ' ')
            {
                map[userX][userY] = '>';
            }
            break;
    }
    return userY;
}

int updateUserX(char action, char **map, int userX, int userY)
{
    switch(action)
    {
        /*if the coordinates the user wants to move to is a space, then update user 
        character position depending on user input*/
        case 'w':
            if(map[userX--][userY] == ' ') 
            {
                map[userX][userY] = '^';
            }
            break;

        case 's':
            if(map[userX++][userY] == ' ')
            {
                map[userX][userY] = 'v';
            }
            break;
    }
    return userX;
}

/*part of the code guided by Dr. Ling*/
int updateSnakeY(char action, char **map, int snakeX, int snakeY, int userX, int userY, int col)
{
    /*if i dont do this, the snake will move diagonally.
    this is to check which move to make next to let the snake get closer to the user*/
    if(abs(snakeY - userY) > abs(snakeX - userX))
    {
        /*if snake is to the left of player, it will go left*/
        if(snakeY > userY)
        {
            snakeY--;
            /*if the updated cooridnate is a space and is not a wall then print 
            at that coordinate, otherwise, change it back to previous coordinate*/
            if(map[snakeX][snakeY] == ' ' && map[snakeX][snakeY] != 'o')
            {
                map[snakeX][snakeY] = '~';
            }
            else
            {
                snakeY++;
            }
        }  
        /*if snake is to the right of player, it will go right*/
        if(snakeY < userY)
        {
            snakeY++;
            /*if the updated cooridnate is a space and is not a wall then print 
            at that coordinate, otherwise, change it back to previous coordinate*/
            if(map[snakeX][snakeY] == ' ' && map[snakeX][snakeY] != 'o')
            {
                map[snakeX][snakeY] = '~';
            }
            else
            {
                snakeY--;
            }
        }
    }
    return snakeY;
}

/*part of the code guided by Dr. Ling*/
int updateSnakeX(char action, char **map, int snakeX, int snakeY, int userX, int userY, int row)
{   
    /*if i dont do this, the snake will move diagonally.
    this is to check which move to make next to let the snake get closer to the user*/
    if(abs(snakeY - userY) < abs(snakeX - userX))
    {
        /*if snake is under player, it will go up*/
        if(snakeX > userX)
        {
            snakeX--;
            /*if the updated cooridnate is a space and is not a wall then print 
            at that coordinate, otherwise, change it back to previous coordinate*/
            if(map[snakeX][snakeY] == ' ' && map[snakeX][snakeY] != 'o')
            {
                map[snakeX][snakeY] = '~';
            }
            else
            {
                snakeX++; 
            }
        }
        /*if snake is above player, it will go down*/
        if(snakeX < userX)
        {
            snakeX++;
            /*if the updated cooridnate is a space and is not a wall then print 
            at that coordinate, otherwise, change it back to previous coordinate*/
            if(map[snakeX][snakeY] == ' ' && map[snakeX][snakeY] != 'o')
            {
                map[snakeX][snakeY] = '~';
            }
            else
            {
                snakeX--;
            }
        }
    }
    return snakeX;
}

void printMove(char action, int userX, int userY, int snakeX, int snakeY, char **map, char face)
{
    /*original position*/
    map[userX][userY] = '^';

    if(action == 'u')
    {
        map[userX][userY] = face;
    }
    else
    {
        /*if the character is not facing in this direction, then change to make it face 
        in the correct direction*/
        switch(action)
        {
            case 'w':
                if(map[userX][userY] != '^')
                {
                    map[userX][userY] = '^';
                }
                break;

            case 's':
                if(map[userX][userY] != 'v')
                {
                    map[userX][userY] = 'v';
                }
                break;

            case 'a':
                if(map[userX][userY] != '<')
                {
                    map[userX][userY] = '<';
                }
                break;

            case 'd':
                if(map[userX][userY] != '>')
                {
                    map[userX][userY] = '>';
                }
                break;
        }
    }
}

