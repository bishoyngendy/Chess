#include <stdio.h>
#include "global.h"

//prototype
int convertRow(char c);
int convertColumn(char c);

// return the piece inside a square
char getPieceInside(char board[BOARD_LENGTH][BOARD_LENGTH], int x, int y)
{
    return board[x][y];
}

// convert previous and next input text to indexes in board
void convertInput(char inpArr[])
{
    inpArr[0] = convertRow(inpArr[0]);
    inpArr[1] = convertColumn(inpArr[1]);
    inpArr[2] = convertRow(inpArr[2]);
    inpArr[3] = convertColumn(inpArr[3]);
}

// convert row character names to indexes in board
int convertRow(char c)
{
    int i = (c - 'A' + 1);
    return i;
}

// convert column character names to indexes in board
int convertColumn(char c)
{
    int i = (int)(c - '1' + 1);
    return i;
}
