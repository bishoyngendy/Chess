#include "global.h"
#include "moveCheck.h"
#include "validation.h"
#include "check.h"

// check if there are any available move for any pieces
// return 1 for true
int availbleMove(char board[BOARD_LENGTH][BOARD_LENGTH], char player)
{
    char tempBoard[BOARD_LENGTH][BOARD_LENGTH];
    // make tempBoard similar to the original board
    for (int i = 0, counter = (BOARD_LENGTH - 1); i < counter; i++)
    {
        for(int j = 0; j < counter; j++)
        {
            tempBoard[i][j] = board[i][j];
        }
    }

    char currentMove[8][8];
    int counter = 0;
    int i; int k; int counterLoop;
    for (i = 1, counterLoop = BOARD_LENGTH - 1; i < counterLoop; i++)
    {
        for (k = 1; k < counterLoop; k++)
        {
            if (!(board[i][k] == '-' || board[i][k] == '.')) // check that square isn't empty
            {
                if (playMyPiece(board[i][k], player)) // check for which player is the piece
                {
                    counter++;
                    char piece = board[i][k];
                    if (tolower(piece) == 'n')
                    {
                        for (int s1 = 0; s1 < 8; s1++)
                        {
                            currentMove[s1][1] = i;
                            currentMove[s1][0] = k;
                        }
                        currentMove[0][2] = 1 + k;      currentMove[0][3] = 2 + i;
                        currentMove[1][2] = 2 + k;      currentMove[1][3] = 1 + i;
                        currentMove[2][2] = -1 + k;     currentMove[2][3] = 2 + i;
                        currentMove[3][2] = 2 + k;      currentMove[3][3] = -1 + i;
                        currentMove[4][2] = 1 + k;      currentMove[4][3] = -2 + i;
                        currentMove[5][2] = -2 + k;     currentMove[5][3] = 1 + i;
                        currentMove[6][2] = -1 + k;     currentMove[6][3] = -2 + i;
                        currentMove[7][2] = -2 + k;     currentMove[7][3] = -1 + i;

                        for (int s2 = 0; s2 < 8; s2++)
                        {
                            if (existInBoard(currentMove[s2]))
                            {
                                char desLoc[2];
                                desLoc[0] = currentMove[s2][2]; desLoc[1] = currentMove[s2][3];
                                char tmpPiece = board[desLoc[1]][desLoc[0]];
                                char checkTrue = 1;
                                if (tmpPiece != '.' && tmpPiece != '-')
                                    checkTrue = !playMyPiece(tmpPiece, player);
                                int rst = isMovable(board, player, currentMove[s2], piece)
                                        && !(isPinned(board, tempBoard, currentMove[s2], desLoc))
                                        && checkTrue;
                                if (rst) return 1;
                            }
                        }
                    }
                    else
                    {
                        //initializeMove(currentMove, i, k);

                        for (int s3 = 0; s3 < 8; s3++)
                        {
                            currentMove[s3][1] = i;
                            currentMove[s3][0] = k;
                        }
                        currentMove[0][3] = 0 + i;      currentMove[0][2] = 1 + k;
                        currentMove[1][3] = 1 + i;      currentMove[1][2] = 0 + k;
                        currentMove[2][3] = 1 + i;      currentMove[2][2] = 1 + k;
                        currentMove[3][3] = -1 + i;     currentMove[3][2] = -1 + k;
                        currentMove[4][3] = -1 + i;     currentMove[4][2] = 0 + k;
                        currentMove[5][3] = 0 + i;      currentMove[5][2] = -1 + k;
                        currentMove[6][3] = 1 + i;      currentMove[6][2] = -1 + k;
                        currentMove[7][3] = -1 + i;     currentMove[7][2] = 1 + k;

                        for (int s=0; s < 8; s++)
                        {
                            if (existInBoard(currentMove[s]))
                            {
                                int desLoc[2];
                                desLoc[0] = currentMove[s][2]; desLoc[1] = currentMove[s][3];
                                char tmpPiece = board[desLoc[1]][desLoc[0]];
                                char checkTrue = 1;
                                if (tmpPiece != '.' && tmpPiece != '-')
                                    checkTrue = !playMyPiece(tmpPiece, player);

                                int rst = isMovable(board, player, currentMove[s], piece)
                                            && !(isPinned(board, tempBoard, currentMove[s], desLoc))
                                            && checkTrue;
                                if (tolower(piece) == 'k')
                                {
                                    rst = rst && !isChecked(board,player,desLoc);
                                }
                                if (rst) return 1;
                            }
                        }
                    }
                }
            }
            if (counter == 16) break;
        }
        if (counter == 16) break;
    }
    return 0;
}

void initializeMove(char currentMove[8][4], int i, int k)
{
    for (int s = 0; s < 8; s++)
    {
        currentMove[s][0] = i;
        currentMove[s][1] = k;
    }
    currentMove[0][3] = 0 + k;      currentMove[0][2] = 1 + i;
    currentMove[1][3] = 1 + k;      currentMove[1][2] = 0 + i;
    currentMove[2][3] = 1 + k;      currentMove[2][2] = 1 + i;
    currentMove[3][3] = -1 + k;     currentMove[3][2] = -1 + i;
    currentMove[4][3] = -1 + k;     currentMove[4][2] = 0 + i;
    currentMove[5][3] = 0 + k;      currentMove[5][2] = -1 + i;
    currentMove[6][3] = 1 + k;      currentMove[6][2] = -1 + i;
    currentMove[7][3] = -1 + k;     currentMove[7][2] = 1 + i;
}

int existInBoard(char move[])
{
    if((move[3] >= 1 && move[3]<=8) && (move[2] >= 1 && move[2]<=8))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
