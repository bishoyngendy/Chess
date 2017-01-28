#include <stdio.h>
#include "global.h"

void printCapPieces (char captureArr[], int* arrSize);

void PrintBoard(char board[BOARD_LENGTH][BOARD_LENGTH] , char player,
                char whilteCaptureArr[], int* whiteArrSize,
                char blackCaptureArr[], int* blackArrSize)
{
    if (player == 'w')
    {
        printf("Captured Pieces From Black :\n");
        printCapPieces(blackCaptureArr, *blackArrSize);

        // Board
        for(int i = 9; i >= 0; i--)
        {
            for(int j = 0; j < 10; j++)
            {
                printf("%c   " , board[i][j]);
            }
            printf("\n\n");
        }

        printf("Captured Pieces From White :\n");
        printCapPieces(whilteCaptureArr, *whiteArrSize);
    }
    else
    {
        printf("Captured Pieces From White :\n");
        printCapPieces(whilteCaptureArr, *whiteArrSize);

        for(int i = 0; i < 10; i++)
        {
            for(int j = 9; j >= 0; j--)
            {
                printf("%c   " , board[i][j]);
            }
            printf("\n\n");
        }

        printf("Captured Pieces From Black :\n");
        printCapPieces(blackCaptureArr, *blackArrSize);
    }
}

void printCapPieces (char captureArr[], int* arrSize)
{
    for(int i = 0; i < arrSize; i++)
    {
        printf("%c " , captureArr[i]);
    }
    printf("\n");
}

