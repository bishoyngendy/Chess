#include <ctype.h>
#include "global.h"


// board[0][1] stores the initial coordinates in the board
// board[2][3] stores the final coordinates in the board
// board[4] stores the moved piece
// board[5] stores the captured piece if present or '.' or '-'
// board[6] stores the promoted piece

int undo(char board[BOARD_LENGTH][BOARD_LENGTH], char gameMoves[GAME_MOVES][7] , int *currentMoveIndex,
         int* capturedWhiteSize, int* capturedBlackSize, int* redoSize)
{
    int moveIndex = *currentMoveIndex - 1;
    (*redoSize)++;

    if((islower(gameMoves[moveIndex][4])) == (islower(gameMoves[moveIndex - 1][4]))) // castle
    {
        (*currentMoveIndex)--;
        int i = undo(board, gameMoves, currentMoveIndex, capturedWhiteSize, capturedBlackSize, redoSize);
        if (i == 0) return;
        (*currentMoveIndex)++;
    }
    if(((isupper(gameMoves[moveIndex][5])) && (islower(gameMoves[moveIndex][4])))) // white captures black
    {
       (*capturedBlackSize)--;
    }
    else if (((isupper(gameMoves[moveIndex][5])) && (islower(gameMoves[moveIndex][4])))) // black captures white
    {
       (*capturedWhiteSize)--;
    }

    char prevY = gameMoves[moveIndex][0], prevX = gameMoves[moveIndex][1];
    char nextY = gameMoves[moveIndex][2], nextX = gameMoves[moveIndex][3];

    if (*currentMoveIndex <= 0)
    {
        printf("Can't Undo, It's the first move !! \n");
        return 0;
    }
    else
    {
        (*currentMoveIndex)--;
        if(gameMoves[moveIndex][6] == 0 || gameMoves[moveIndex][6] == ' ') // not a promotion
        {
            board[gameMoves[moveIndex][1]][gameMoves[moveIndex][0]]
                    = gameMoves[moveIndex][4];
            board[gameMoves[moveIndex][3]][gameMoves[moveIndex][2]]
                    = gameMoves[moveIndex][5];
        }
        else // promotion
        {
            board[gameMoves[moveIndex][3]][gameMoves[moveIndex][2]]
                    = gameMoves[moveIndex][5];
            board[gameMoves[moveIndex][1]][gameMoves[moveIndex][0]]
                    = gameMoves[moveIndex][6];
        }
    }
    return 1;
}

int redo(char board[BOARD_LENGTH][BOARD_LENGTH], char gameMoves[GAME_MOVES][7] , int *currentMoveIndex,
         int* capturedWhiteSize, int* capturedBlackSize, int* redoSize)
{
    int moveIndex = *currentMoveIndex;

    if((islower(gameMoves[moveIndex][4])) == (islower(gameMoves[moveIndex + 1][4]))) // castle
    {
        (*currentMoveIndex)++;
        int i = redo(board, gameMoves, currentMoveIndex, capturedWhiteSize, capturedBlackSize, redoSize);
        if (i == 0) return;
        (*currentMoveIndex)--;
    }
    if(((isupper(gameMoves[moveIndex][5])) && (islower(gameMoves[moveIndex][4])))) // white captures black
    {
       (*capturedBlackSize)++;
    }
    else if (((isupper(gameMoves[moveIndex][5])) && (islower(gameMoves[moveIndex][4])))) // black captures white
    {
       (*capturedWhiteSize)++;
    }

    char prevY = gameMoves[moveIndex][0], prevX = gameMoves[moveIndex][1];
    char nextY = gameMoves[moveIndex][2], nextX = gameMoves[moveIndex][3];

//    if (*currentMoveIndex >= *gameSize)
    if (*redoSize == 0)
    {
        printf("Can't Redo.\n");
        return 0;
    }
    else
    {
        (*redoSize)--;
        (*currentMoveIndex)++;
        if(gameMoves[moveIndex][6] == 0 || gameMoves[moveIndex][6] == ' ') // not a promotion
        {
            board[gameMoves[moveIndex][3]][gameMoves[moveIndex][2]]
                    = gameMoves[moveIndex][4];
            board[gameMoves[moveIndex][1]][gameMoves[moveIndex][0]]
                    = gameMoves[moveIndex][5];
        }
        else // promotion
        {
            board[gameMoves[moveIndex][3]][gameMoves[moveIndex][2]]
                    = gameMoves[moveIndex][6];
            board[gameMoves[moveIndex][1]][gameMoves[moveIndex][0]]
                    = gameMoves[moveIndex][5];
        }
    }
    return 1;
}

void saveMove(char gameMoves[GAME_MOVES][7] , int *currentMoveIndex, char currentMove[])
{
    for (int i = 0; i < 7; i++)
    {
        gameMoves[*currentMoveIndex][i] = currentMove[i];
    }
    (*currentMoveIndex)++;
}

