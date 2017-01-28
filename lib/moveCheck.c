#include "global.h"

// prototypes
int convertRow(char c);
int convertColumn(char c);

int checkRockMove(char coord[])
{
    int status = 0;

    // rock can only move to squares having same row or same column
    if (coord[0] == coord[2]) status = 1;
    else if (coord[1] == coord[3]) status = 1;

    return status;
}

int checkRockWay(char board[BOARD_LENGTH][BOARD_LENGTH], char coord[])
{
    // coord hold the old and the new coordinates in y & x old | y & x new

    int moveOnColumn = (coord[0] == coord[2]); // hold the axis of movement (1 for y-axis& 0 for x-axis)
    int diff; // the number of steps
    if(coord[0] == coord[2]) diff = abs(coord[1] - coord[3]);
    else diff = abs(coord[0] - coord[2]);

    if(moveOnColumn)
    {
        // to simulate the move from the smaller y to bigger y
        int smallerXcoord = coord[1] > coord[3] ? coord[3] : coord[1];

        // check every square in its way by . & -
        for (int i = 1; i < diff; i++)
        {
            int x = i + smallerXcoord, y = coord[0];
            if (board[x][y] != '.')
                if (board[x][y] != '-')
                {
                    //printf("Invalid move your piece can't jump over other pieces !!\n");
                    return 0; // return 0 if find any pieces in the way
                }
        }
    }
    else
    {
        // to simulate the move from the smaller x to bigger x
        int smallerYcoord = coord[0] > coord[2] ? coord[2] : coord[0];

        for (int i = 1; i < diff; i++)
        {
            int y = i + smallerYcoord, x = coord[1];
            if (board[x][y] != '.')
                if (board[x][y] != '-')
                {
                    //printf("Invalid move your piece can't jump over other pieces !!\n");
                    return 0; // return 0 if find any pieces in the way
                }
        }
    }
    return 1;
}

int checkBishopMove(char coord[])
{
    int status = 0;

    // the difference between new x and old x = the absolute value of the difference in y
    // this way the motion is diagonally in the board
    if ((coord[0] - coord[2]) == (coord[1] - coord[3]) ||
        (coord[0] - coord[2]) == (-1 * (coord[1] - coord[3])))
    {
        status = 1;
    }
    return status;
}

int checkBishopWay(char board[BOARD_LENGTH][BOARD_LENGTH], char coord[])
{
    // suppose x and y are increasing
    int diffY = coord[3] - coord[1];
    int diffX = coord[2] - coord[0];

    int lowerX, lowerY, higherX, higherY;
    if (diffX > 0 && diffY > 0)
    {
        int xCounter = coord[0] + 1;
        int yCounter = coord[1] + 1;

        while(xCounter < coord[2])
        {
            if (board[yCounter][xCounter] != '.')
            {
                if (board[yCounter][xCounter] != '-')
                {
                    // printf("Invalid move your piece can't jump over other pieces !!\n");
                    return 0;
                }
            }
            xCounter++;
            yCounter++;
        }
    }
    else if (diffX < 0 && diffY > 0)
    {
        int xCounter = coord[0] - 1;
        int yCounter = coord[1] + 1;

        while(xCounter > coord[2])
        {
            if (board[yCounter][xCounter] != '.')
            {
                if (board[yCounter][xCounter] != '-')
                {
                    // printf("Invalid move your piece can't jump over other pieces !!\n");
                    return 0;
                }
            }
            xCounter--;
            yCounter++;
        }
    }
    else if (diffX > 0 && diffY < 0)
    {
        int xCounter = coord[0] + 1;
        int yCounter = coord[1] - 1;

        while(xCounter < coord[2])
        {
            if (board[yCounter][xCounter] != '.')
            {
                if (board[yCounter][xCounter] != '-')
                {
                    // printf("Invalid move your piece can't jump over other pieces !!\n");
                    return 0;
                }
            }
            xCounter++;
            yCounter--;
        }
    }
    else
    {
        int xCounter = coord[0] - 1;
        int yCounter = coord[1] - 1;

        while(xCounter > coord[2])
        {
            if (board[yCounter][xCounter] != '.')
            {
                if (board[yCounter][xCounter] != '-')
                {
                    // printf("Invalid move your piece can't jump over other pieces !!\n");
                    return 0;
                }
            }
            xCounter--;
            yCounter--;
        }
    }
    return 1;
}

int checkQueenWay(char board[BOARD_LENGTH][BOARD_LENGTH], char coord[])
{
    // checks the queen's way as rock
    if ((coord[0] == coord[2]) || (coord[1] == coord[3]))
        return checkRockWay (board, coord);
    // checks the queen's way as bishop
    else
        return checkBishopWay (board, coord);
}

int checkKnightMove(char coord[])
{
    int status = 0;

    // absolute value of difference in x
    int x = abs((coord[2]) - (coord[0]));

    // absolute value of difference in x
    int y = abs((coord[3]) - (coord[1]));

    // To make the L motion x = 1 && y = 2 or y = 2 && x = 1
    if (((x == 1) && (y == 2)) || ((x == 2) && (y == 1)))
    {
        status = 1;
    }
    return status;
}

int checkKingMove(char coord[])
{
    int status = 0;
    // absolute value of difference in x
    int x = abs((coord[2]) - (coord[0]));

    // absolute value of difference in x
    int y = abs((coord[3]) - (coord[1]));

    // king moves one step only in any direction
    // so xCoordinate only changes by 1 while y is constant
    // or yCoordinate only changes by 1 while x is constant
    // or both of them changes by 1
    if (((x == 1) && (y == 0))
      ||((x == 0) && (y == 1))
      ||((x == 1) && (y == 1))
        )
    {
        status = 1;
    }
        return status;
}

int checkPawnMove(char board[BOARD_LENGTH][BOARD_LENGTH], char coord[], char player)
{
    int sign = player == 'w' ? 1 : -1; // hold 1 for white , -1 for black

    // check if it is not the same column
    if (coord[0] != coord[2]) return 0;

    int diff = (coord[3] - coord[1]) * sign; // hold the diff between the two locations in y-axis

    int x = coord[3]; int y = coord[2]; // get the x & y of the new location

    switch(diff){
    case 1:
        if(board[x][y] == '.' || board[x][y] == '-') // if the new location is empty so the pawn can go there
            return 1;
        break;

    case 2:
        // if the pawn is in the row 2 (for white) or row 7 (for black) can make two moves
        if (coord[1] == 2 || coord[1] == 7) {
            if((board[x][y] == '.' || board[x][y] == '-')
                && (board[x - 1*sign][y] == '.' || board[x - 1*sign][y] == '-')) // check for a piece on it's way
                return 1;
        }
        break;
    }

    return 0;
}

int checkPawnCapture(char board[BOARD_LENGTH][BOARD_LENGTH], char coord[], char player)
{
    int sign = player == 'w' ? 1 : -1; // hold 1 for white , -1 for black

    // check the difference between the y-axis
    if (abs(coord[2] - coord[0]) != 1) return 0;
    // check the difference  between the x-axis
    if ((coord[3] - coord[1]) * sign != 1) return 0;

    int x = coord[3]; int y = coord[2]; // get the x & y of the new location

    if(board[x][y] == '.' || board[x][y] == '-') return 0; // if the new location is empty so the pawn can go there
    else if(coord[0] == coord[2]) return 0;
    else return 1;
}

int checkQueenMove(char coord[])
{
    int status = 0;

    // the queen moves as a rock or as a bishop every single move
    if((checkBishopMove(coord)) || (checkRockMove(coord)))
    {
        status = 1;
    }
    return status;
}

int checkSameMove(char coord[])
{
    int status = !((coord[0] == coord[2]) && (coord[1] == coord[3]));
    if ((coord[0]) == '\017') status = 1;
    return status;
}

int checkPawnPromotion(char coord[], char player)
{
    if (player == 'w' && coord[1] == 7)
    {
        return 0;
    }
    else if (player = 'b' && coord[1] == 2)
    {
        return 0;
    }
    return 1;
}

int isMovable(char board[BOARD_LENGTH][BOARD_LENGTH], char currentPlayer, char currentMove[], char piece)
{
    int logicValidMove = -1;
    switch (tolower(piece)){
            case 'p':
                logicValidMove = checkPawnMove(board, currentMove, currentPlayer)
                            || checkPawnCapture(board, currentMove, currentPlayer)
                            && checkPawnPromotion(currentMove, currentPlayer);
                break;
            case 'r':
                logicValidMove = checkRockMove(currentMove) && checkRockWay(board, currentMove);
                break;
            case 'b':
                logicValidMove = checkBishopMove(currentMove) && checkBishopWay(board, currentMove);
                break;
            case 'n':
                logicValidMove = checkKnightMove(currentMove);
                break;
            case 'q':
                logicValidMove = checkQueenMove(currentMove) && checkQueenWay(board, currentMove);
                break;
            case 'k':
                // check law hayeb2a makshosh
                logicValidMove = checkKingMove(currentMove);
                break;
        }

    return logicValidMove;
}

int isPinned(char board[BOARD_LENGTH][BOARD_LENGTH], char tempboard[BOARD_LENGTH][BOARD_LENGTH],
             char pieceLocation[], char desireLocation[])
{
    int yPiece = pieceLocation[0];
    int xPiece = pieceLocation[1];

    int yDesire = desireLocation[0];
    int xDesire = desireLocation[1];

    char piece = getPieceInside(board, xPiece, yPiece);
    char desireSquare = getPieceInside(board, xDesire, yDesire);

    int kingLocation[2];
    if(piece == tolower(piece)) // white piece
    {
        getKingLocation(tempboard, 'w', kingLocation);
        if ((xPiece + yPiece) % 2 == 0)
        {
            tempboard[xPiece][yPiece] = '.';
        }
        else
        {
            tempboard[xPiece][yPiece] = '-';
        }

        tempboard[xDesire][yDesire] = piece;

        if(isChecked(tempboard, 'w', kingLocation))
        {
            tempboard[xPiece][yPiece] = piece;
            return 1;
        }
        tempboard[xPiece][yPiece] = piece;
        tempboard[xDesire][yDesire] = desireSquare;
    }
    else // black piece
    {
        getKingLocation(tempboard, 'b', kingLocation);
        if ((xPiece + yPiece) % 2 == 0)
        {
            tempboard[xPiece][yPiece] = '.';
        }
        else
        {
            tempboard[xPiece][yPiece] = '-';
        }

        tempboard[xDesire][yDesire] = piece;

        if(isChecked(tempboard, 'b', kingLocation))
        {
            tempboard[xPiece][yPiece] = piece;
            return 1;
        }
        tempboard[xPiece][yPiece] = piece;
        tempboard[xDesire][yDesire] = desireSquare;
    }
    return 0;
}
