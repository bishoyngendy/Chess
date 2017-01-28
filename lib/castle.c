#include "global.h"


// return 1 if castling is OK && 0 if not
int checkCastleWay(char board[BOARD_LENGTH][BOARD_LENGTH], char player, char type)
{
    int status = 0;
    if (player == 'w' && type == 's')
    {
        if ((board[1][6] == '.' || board[1][6] == '-') &&
            (board[1][7] == '.' || board[1][7] == '-') )
        {
            status = 1;
        }
    }
    else if ((player == 'w' && type == 'l'))
    {
        if ((board[1][4] == '.' || board[1][4] == '-') &&
            (board[1][3] == '.' || board[1][3] == '-') &&
            (board[1][2] == '.' || board[1][2] == '-') )
        {
            status = 1;
        }
    }
    else if ((player == 'b' && type == 's'))
    {
        if ((board[8][6] == '.' || board[8][6] == '-') &&
            (board[8][7] == '.' || board[8][7] == '-') )
        {
            status = 1;
        }
    }
    else if ((player == 'b' && type == 'l'))
    {
        if ((board[8][4] == '.' || board[8][4] == '-') &&
            (board[8][3] == '.' || board[8][3] == '-') &&
            (board[8][2] == '.' || board[8][2] == '-') )
        {
            status = 1;
        }
    }
    return status;
}

// return 1 if castling is OK && 0 if not
int prevMotion(char gameMoves[GAME_MOVES][7] , int *currentMoveIndex, char player, char type)
{
    int status = 1;
    int moveIndex = *currentMoveIndex;

    if (player == 'w' && type == 's')
    {
        for(int i = 0; (i < moveIndex) && (status); i++)
        {
            if ((gameMoves[i][0] == (char)5 && gameMoves[i][1] == (char)1) ||
                (gameMoves[i][0] == (char)8 && gameMoves[i][1] == (char)1))
            {
                status = 0;
            }
        }
    }
    else if ((player == 'w' && type == 'l'))
    {
        for(int i = 0; (i < moveIndex) && (status); i++)
        {
            if ((gameMoves[i][0] == (char)5 && gameMoves[i][1] == (char)1) ||
                (gameMoves[i][0] == (char)1 && gameMoves[i][1] == (char)1))
            {
                status = 0;
            }
        }
    }
    else if ((player == 'b' && type == 's'))
    {
        for(int i = 0; (i < moveIndex) && (status); i++)
        {
            if ((gameMoves[i][0] == (char)5 && gameMoves[i][1] == (char)8) ||
                (gameMoves[i][0] == (char)8 && gameMoves[i][1] == (char)8))
            {
                status = 0;
            }
        }
    }
    else if ((player == 'b' && type == 'l'))
    {
        for(int i = 0; (i < moveIndex) && (status); i++)
        {
            if ((gameMoves[i][0] == (char)5 && gameMoves[i][1] == (char)8) ||
                (gameMoves[i][0] == (char)1 && gameMoves[i][1] == (char)8))
            {
                status = 0;
            }
        }
    }
    return status;
}

// return 1 if castling is  not OK && 0 if OK
int squaresNotAllowed(char board[BOARD_LENGTH][BOARD_LENGTH], char player, char type,
                        char tempBoard[BOARD_LENGTH][BOARD_LENGTH], int kingLocation[])
{
    int yKing = kingLocation[0]; int xKing = kingLocation[1];
    // make tempBoard similar to the original board
    for (int i = 0, counter = (BOARD_LENGTH - 1); i < counter; i++)
    {
        for(int j = 0; j < counter; j++)
        {
            tempBoard[i][j] = board[i][j];
        }
    }

    int kingCannotMv = 1;
    int possiblePlaces[5][2];
    int possiblePlacesSize;

    if (player == 'w' && type == 's')
    {
        possiblePlaces[0][0] = 1; possiblePlaces[0][1] = 5;
        possiblePlaces[1][0] = 1; possiblePlaces[1][1] = 6;
        possiblePlaces[2][0] = 1; possiblePlaces[2][1] = 7;
        possiblePlaces[3][0] = 1; possiblePlaces[3][1] = 8;

        possiblePlacesSize = 4;
    }
    else if ((player == 'w' && type == 'l'))
    {
        possiblePlaces[0][0] = 1; possiblePlaces[0][1] = 5;
        possiblePlaces[1][0] = 1; possiblePlaces[1][1] = 4;
        possiblePlaces[2][0] = 1; possiblePlaces[2][1] = 3;
        possiblePlaces[3][0] = 1; possiblePlaces[3][1] = 2;
        possiblePlaces[4][0] = 1; possiblePlaces[4][1] = 1;

        possiblePlacesSize = 5;
    }
    else if ((player == 'b' && type == 's'))
    {
        possiblePlaces[0][0] = 8; possiblePlaces[0][1] = 5;
        possiblePlaces[1][0] = 8; possiblePlaces[1][1] = 6;
        possiblePlaces[2][0] = 8; possiblePlaces[2][1] = 7;
        possiblePlaces[3][0] = 8; possiblePlaces[3][1] = 8;

        possiblePlacesSize = 4;
    }
    else if ((player == 'b' && type == 'l'))
    {
        possiblePlaces[0][0] = 8; possiblePlaces[0][1] = 5;
        possiblePlaces[1][0] = 8; possiblePlaces[1][1] = 4;
        possiblePlaces[2][0] = 8; possiblePlaces[2][1] = 3;
        possiblePlaces[3][0] = 8; possiblePlaces[3][1] = 2;
        possiblePlaces[4][0] = 8; possiblePlaces[4][1] = 1;

        possiblePlacesSize = 5;
    }

    // loop over the array of possible places of king
    for (int i = 0; (i < possiblePlacesSize) && (kingCannotMv == 1); i++)
    {
        int xPlace = possiblePlaces[i][1];
        int yPlace = possiblePlaces[i][0];
        int kingLoc[2] = {yPlace, xPlace};
        if(xPlace < 9 && xPlace > 0 && yPlace < 9 && yPlace > 0)
        {
            if((board[yPlace][xPlace] == '-' || board[yPlace][xPlace] == '.'))
            {
                // check if the king can move to this square without being checked
                char finalC = board[yPlace][xPlace]; char initialC = board[yKing][xKing];

                tempBoard[yPlace][xPlace] = initialC;
                tempBoard[yKing][xKing] = ((yKing + xKing) % 2 == 0) ? '.' : '-';

                if (isChecked(tempBoard, player, kingLoc))
                {
                    tempBoard[yPlace][xPlace] = finalC;
                    tempBoard[yKing][xKing] = initialC;
                    kingCannotMv = 0;
                    return kingCannotMv;
                }
            }
        }
    }
    return kingCannotMv;
}

void castle(char board[BOARD_LENGTH][BOARD_LENGTH], char player, int type,
            char tempBoard[BOARD_LENGTH][BOARD_LENGTH], char gameMoves[GAME_MOVES][7] , int *currentMoveIndex,
            char moveOne[], char moveTwo[])
{
    if (player == 'w' && type == 's')
    {
        board[1][7] = 'k';        board[1][6] = 'r';
        board[1][5] = '.';        board[1][8] = '-';

        tempBoard[1][7] = 'k';        tempBoard[1][6] = 'r';
        tempBoard[1][5] = '.';        tempBoard[1][8] = '-';

        moveOne[0] = (char)5;        moveOne[1] = (char)1;
        moveOne[2] = (char)7;        moveOne[3] = (char)1;
        moveOne[4] = 'k';        moveOne[5] = '.';
        moveOne[6] = ' ';
        saveMove(gameMoves, currentMoveIndex, moveOne); // save in history

        moveTwo[0] = (char)8;
        moveTwo[1] = (char)1;
        moveTwo[2] = (char)6;
        moveTwo[3] = (char)1;
        moveTwo[4] = 'r';
        moveTwo[5] = '-';
        moveTwo[6] = ' ';
        saveMove(gameMoves, currentMoveIndex, moveTwo); // save in history
    }
    else if ((player == 'w' && type == 'l'))
    {
        board[1][3] = 'k';        board[1][4] = 'r';
        board[1][5] = '.';        board[1][1] = '.';

        tempBoard[1][3] = 'k';        tempBoard[1][4] = 'r';
        tempBoard[1][5] = '.';        tempBoard[1][1] = '.';

        moveOne[0] = (char)5;        moveOne[1] = (char)1;
        moveOne[2] = (char)3;        moveOne[3] = (char)1;
        moveOne[4] = 'k';        moveOne[5] = '.';
        moveOne[6] = ' ';
        saveMove(gameMoves, currentMoveIndex, moveOne); // save in history

        moveTwo[0] = (char)1;
        moveTwo[1] = (char)1;
        moveTwo[2] = (char)4;
        moveTwo[3] = (char)1;
        moveTwo[4] = 'r';
        moveTwo[5] = '.';
        moveTwo[6] = ' ';
        saveMove(gameMoves, currentMoveIndex, moveTwo); // save in history
    }
    else if ((player == 'b' && type == 's'))
    {
        board[8][7] = 'K';        board[8][6] = 'R';
        board[8][5] = '-';        board[8][8] = '.';

        tempBoard[8][7] = 'K';        tempBoard[8][6] = 'R';
        tempBoard[8][5] = '-';        tempBoard[8][8] = '.';

        moveOne[0] = (char)5;        moveOne[1] = (char)8;
        moveOne[2] = (char)7;        moveOne[3] = (char)8;
        moveOne[4] = 'K';        moveOne[5] = '-';
        moveOne[6] = ' ';
        saveMove(gameMoves, currentMoveIndex, moveOne); // save in history

        moveTwo[0] = (char)8;
        moveTwo[1] = (char)8;
        moveTwo[2] = (char)6;
        moveTwo[3] = (char)8;
        moveTwo[4] = 'R';
        moveTwo[5] = '.';
        moveTwo[6] = ' ';
        saveMove(gameMoves, currentMoveIndex, moveTwo); // save in history
    }
    else if ((player == 'b' && type == 'l'))
    {
        board[8][3] = 'K';        board[8][4] = 'R';
        board[8][5] = '-';        board[8][1] = '-';

        tempBoard[8][3] = 'K';        tempBoard[8][4] = 'R';
        tempBoard[8][5] = '-';        tempBoard[8][1] = '-';

        moveOne[0] = (char)5;        moveOne[1] = (char)8;
        moveOne[2] = (char)3;        moveOne[3] = (char)8;
        moveOne[4] = 'K';        moveOne[5] = '-';
        moveOne[6] = ' ';
        saveMove(gameMoves, currentMoveIndex, moveOne); // save in history

        moveTwo[0] = (char)1;
        moveTwo[1] = (char)8;
        moveTwo[2] = (char)4;
        moveTwo[3] = (char)8;
        moveTwo[4] = 'R';
        moveTwo[5] = '-';
        moveTwo[6] = ' ';
        saveMove(gameMoves, currentMoveIndex, moveTwo); // save in history
    }
}
