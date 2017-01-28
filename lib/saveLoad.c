#include "global.h"
#include <stdio.h>
#include <string.h>

void saveGame(char gameMoves[GAME_MOVES][7], int currentMoveIndex, char board[BOARD_LENGTH][BOARD_LENGTH])
{
    FILE *fp;
    fp = fopen("savedGame.txt", "w");

    if (fp == NULL) {
      printf("Can't open input file!\n");
      return;
    }

   fprintf(fp, "%d\n", currentMoveIndex);

    for (int i = 0; i < currentMoveIndex; i++)
    {
       fprintf(fp,"%d,%d,%d,%d,%c,%c,%c", gameMoves[i][0],gameMoves[i][1],gameMoves[i][2],
                   gameMoves[i][3],gameMoves[i][4],gameMoves[i][5],gameMoves[i][6]);
       fputc('\n',fp);
    }
    fclose(fp);

    fp = fopen("savedGameBoard.txt", "w");
    if (fp == NULL) {
      printf("Can't open file!\n");
      return;
    }
    for (int i = 0; i < BOARD_LENGTH; i++)
    {
       for (int k = 0; k < BOARD_LENGTH; k++)
       {
           fputc(board[i][k], fp);
       }
    }

    fclose(fp);
}

void loadGame(char gameMoves[GAME_MOVES][7], char board[BOARD_LENGTH][BOARD_LENGTH],
              int *currentMoveIndex, char capturedWhite[PIECES_NUMBER], char capturedBlack[PIECES_NUMBER],
              int *capturedWhiteSize, int *capturedBlackSize)
{
    FILE *fp;
    fp = fopen("savedGame.txt", "r");

    if (fp == NULL) {
      printf("Can't open file!\n");
      return;
    }
   fscanf(fp, "%d", currentMoveIndex);

   for (int i = 0; i < *currentMoveIndex; i++)
    {
        fscanf(fp,"%d,%d,%d,%d,%c,%c,%c", &gameMoves[i][0], &gameMoves[i][1], &gameMoves[i][2],
                    &gameMoves[i][3], &gameMoves[i][4], &gameMoves[i][5], &gameMoves[i][6]);

        if (gameMoves[i][5] != '-' && gameMoves[i][5] != '.')
        {
            char player = isupper(gameMoves[i][5]) ? 'b' : 'w';
            if (player == 'w')
                capture(capturedWhite, capturedWhiteSize, gameMoves[i][5]);
            else
                capture(capturedBlack, capturedBlackSize, gameMoves[i][5]);
        }
    }
    fclose(fp);

    fp = fopen("savedGameBoard.txt", "r");
    if (fp == NULL) {
      printf("Can't open file!\n");
      return;
    }

    for (int i = 0; i < BOARD_LENGTH; i++)
    {
       for (int k = 0; k < BOARD_LENGTH; k++)
       {
           //board[i][k] = fscanf(fp,"%c");
           board[i][k] = fgetc(fp);
       }
    }
}
