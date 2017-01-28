#include "global.h"

void makeMove(char board[BOARD_LENGTH][BOARD_LENGTH], char move[])
{
    // moves the piece to the new square
    board[move[3]][move[2]] = board[move[1]][move[0]];

    // replace the initial square with its color
    if ((move[0] + move[1]) % 2 == 0)
    {
        board[move[1]][move[0]] = '.';
    }
    else
    {
        board[move[1]][move[0]] = '-';
    }
}

// add the piece to the captured array
void capture(char captureArr[], int* arrSize, char piece)
{
    captureArr[*arrSize] = piece;
    (*arrSize)++;
}


void promote(char board[BOARD_LENGTH][BOARD_LENGTH], char move[], char player)
{
    // promotes the pawn to the desired piece
    if (player == 'w')
    {
        board[move[3]][move[2]] = tolower(move[4]);
    }
    else
    {
        board[move[3]][move[2]] = toupper(move[4]);
    }

    // replace the initial square of the pawn with its color
    if ((move[0] + move[1]) % 2 == 0)
    {
        board[move[1]][move[0]] = '.';
    }
    else
    {
        board[move[1]][move[0]] = '-';
    }
}

