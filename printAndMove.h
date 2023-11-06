#ifndef PRINTANDMOVE_H
#define PRINTANDMOVE_H

void printMap(int **mapData, char **map, char action, int numObj, int row, int col, int updatedX, int updatedY, char face, int goalX, int goalY, int snakeX, int snakeY);
void printMove(char action, int userX, int userY, int snakeX, int snakeY, char **map, char face);
int updateUserY(char action, char **map, int userX, int userY);
int updateUserX(char action, char **map, int userX, int userY);
int updateSnakeY(char action, char **map, int snakeX, int snakeY, int userX, int userY, int col);
int updateSnakeX(char action, char **map, int snakeX, int snakeY, int userX, int userY, int row);

#endif