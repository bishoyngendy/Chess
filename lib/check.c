#include "global.h"
#include "moveCheck.h"
#include <ctype.h>

int checkWayTiles(char board[BOARD_LENGTH][BOARD_LENGTH],
                    char player, int pieceLocation[], int diff,
                    char tempBoard[BOARD_LENGTH][BOARD_LENGTH], int betweenSquares[10][2]);

int checkWayDiagonals(char board[BOARD_LENGTH][BOARD_LENGTH],
                    char player, int pieceLocation[], int diffX,
                    char tempBoard[BOARD_LENGTH][BOARD_LENGTH], int betweenSquares[10][2]);

int isChecked(char board[BOARD_LENGTH][BOARD_LENGTH], char player, int kingLocation[])
{
    int yKing = kingLocation[0]; int xKing = kingLocation[1];
    int validMove = 0;
 //   int breakCounter = 0;
    for (int i = 1, counter = BOARD_LENGTH - 1; i < counter; i++)
    {
        for (int k = 1; k < counter; k++)
        {
            if (!(board[i][k] == '-' || board[i][k] == '.')) // check that square isn't empty
            {
                if (!(playMyPiece(board[i][k], player)) && tolower(board[i][k]) != 'k') // check for which player is the piece
                {
                    char tmpPlayer = player == 'w' ? 'b' : 'w';
                    char currentMove[] = {(char)k, (char)i, (char)xKing, (char)yKing};

                    if (player == 'b' && currentMove[1] == 7  && board[i][k] == 'p'||
                            player == 'w' && currentMove[1] == 2 && board[i][k] == 'P')
                    {
                        (currentMove[1])--; (currentMove[3])--;
                    }
                    validMove = isMovable(board, tmpPlayer, currentMove, board[i][k]);
                }
            }
            if (validMove == 1) break;
        }
        if (validMove == 1) break;
    }

    return validMove;
}

int getCheckingPieceLoc(char board[BOARD_LENGTH][BOARD_LENGTH], char player, int kingLocation[], int pieceLocation[])
{
    int yKing = kingLocation[0]; int xKing = kingLocation[1];
    int validMove = 0;
    // int breakCounter = 0;
    for (int i = 1, counter = BOARD_LENGTH - 1; i < counter; i++)
    {
        for (int k = 1; k < counter; k++)
        {
            if (!(board[i][k] == '-' || board[i][k] == '.')) // check that square isn't empty
            {
                if (!(playMyPiece(board[i][k], player)) && tolower(board[i][k]) != 'k') // check for which player is the piece
                {
                    char tmpPlayer = player == 'w' ? 'b' : 'w';
                    char currentMove[] = {(char)k, (char)i, (char)xKing, (char)yKing};
                    validMove = isMovable(board, tmpPlayer, currentMove, board[i][k]);
                    pieceLocation[0] = k;
                    pieceLocation[1] = i;
                    //char currentMove[] = {
                    //validMove = isMovable(board, 'w', currentMove, 'r');
                }
            }
            if (validMove == 1) break;
        }
        if (validMove == 1) break;
    }
    return validMove;
}
int kingCannotMove(char board[BOARD_LENGTH][BOARD_LENGTH], char player, int kingLocation[], char tempBoard[BOARD_LENGTH][BOARD_LENGTH])
{
    // make tempBoard similar to the original board
    for (int i = 0, counter = (BOARD_LENGTH - 1); i < counter; i++)
    {
        for(int j = 0; j < counter; j++)
        {
            tempBoard[i][j] = board[i][j];
        }
    }

    int yKing = kingLocation[0]; int xKing = kingLocation[1];

    int kingCannotMv = 1;
    int possiblePlaces[8][2];


    // fill the array with the 8 squares around the king
    for(int i = 0; i < 3; i++)
    {
        possiblePlaces[i][0] = yKing - 1;
    }
    for(int i = 3; i < 5; i++)
    {
        possiblePlaces[i][0] = yKing;
    }
    for(int i = 5; i < 8; i++)
    {
        possiblePlaces[i][0] = yKing + 1;
    }

    possiblePlaces[0][1] = possiblePlaces[3][1] = possiblePlaces[5][1] = xKing - 1;
    possiblePlaces[1][1] = possiblePlaces[6][1] = xKing;
    possiblePlaces[2][1] = possiblePlaces[4][1] = possiblePlaces[7][1] = xKing + 1;

    // loop over the array of possible places of king
    for (int i = 0; (i < 9) && (kingCannotMv == 1); i++)
    {
        int xPlace = possiblePlaces[i][1];
        int yPlace = possiblePlaces[i][0];
        if(xPlace < 9 && xPlace > 0 && yPlace < 9 && yPlace > 0)
        {
            if((board[yPlace][xPlace] == '-' || board[yPlace][xPlace] == '.')
                ||(player == 'w' && board[yPlace][xPlace] != tolower(board[yPlace][xPlace])
                || player == 'b' && board[yPlace][xPlace] != toupper(board[yPlace][xPlace])))
            {
                // check if the king can move to this square without being checked
                char finalC = board[yPlace][xPlace]; char initialC = board[yKing][xKing];

                tempBoard[yPlace][xPlace] = initialC;
                tempBoard[yKing][xKing] = ((yKing + xKing) % 2 == 0) ? '.' : '-';

                int kingLoc[2];
                kingLoc[0] = yPlace;
                kingLoc[1] = xPlace;
                if (isChecked(tempBoard, player, kingLoc))
                {
                    tempBoard[yPlace][xPlace] = finalC;
                    tempBoard[yKing][xKing] = initialC;
                }
                else
                {
                    kingCannotMv = 0;
                }
            }
        }
    }
    return kingCannotMv;
}

int pieceCannotBeCaptured(char board[BOARD_LENGTH][BOARD_LENGTH], char player,
                          int pieceLocation[], char tempBoard[BOARD_LENGTH][BOARD_LENGTH])
{
    // make tempBoard similar to the original board
    for (int i = 0, counter = (BOARD_LENGTH - 1); i < BOARD_LENGTH; i++)
    {
        for(int j = 0; j < BOARD_LENGTH; j++)
        {
            tempBoard[i][j] = board[i][j];
        }
    }

    int pieceCannotBeCap = 1;
    int yPiece = pieceLocation[1], xPiece = pieceLocation[0];
    char piece = getPieceInside(board, yPiece, xPiece);

    // loop over the board to get my pieces
    for (int i = 1, counter = (BOARD_LENGTH - 1); (i < counter) && (pieceCannotBeCap); i++)
    {
        for(int j = 1; (j < counter) && (pieceCannotBeCap); j++)
        {
            if ((!(board[i][j] == '-' || board[i][j] == '.'))
                && ((player == 'w' && board[i][j] == tolower(board[i][j]))
                || (player == 'b' && board[i][j] == toupper(board[i][j]))))
            {
                char pieceToCapture = getPieceInside(board, i, j);

                char pieceToCaptureLocation[2];
                pieceToCaptureLocation[0] = (char)j;
                pieceToCaptureLocation[1] = (char)i;

                // if any of my pieces is not pinned check if it can
                // capture the piece checking the king
                if(!(isPinned(board, tempBoard, pieceToCaptureLocation, pieceLocation)))
                {
                    char currentMove[] = {(char)j, (char)i, (char)xPiece, (char)yPiece};
                    if (isMovable(board, player, currentMove, pieceToCapture))
                    {
                        pieceCannotBeCap = 0;
                    }
                }
            }
        }
    }
    return pieceCannotBeCap;
}

int wayCannotBeBlocked (char board[BOARD_LENGTH][BOARD_LENGTH],
                        char player, int pieceLocation[], int kingLocation[],
                        char tempBoard[BOARD_LENGTH][BOARD_LENGTH])
{
    // make tempBoard similar to the original board
    for (int i = 0, counter = (BOARD_LENGTH - 1); i < counter; i++)
    {
        for(int j = 0; j < counter; j++)
        {
            tempBoard[i][j] = board[i][j];
        }
    }

    int wayCannotBeBlock = 1;

    int yPiece = pieceLocation[0], xPiece = pieceLocation[1];
    int yKing = kingLocation[1], xKing = kingLocation[0];

    char piece = getPieceInside(board, xPiece, yPiece);

    int diffX, diffY;
    switch(tolower(piece)) // switch over the piece checking the king
    {
        case 'r':
        if ((yPiece == yKing) && (abs(xPiece - xKing) > 1))
        {
            int diff = abs(xPiece - xKing);
            int betweenSquares [10][2]; // array containing the squares between the king and the piece
            // fill the array according to the piece type and position relative to the king
            if (xPiece > xKing)
            {
                for (int i = 0; i < (diff - 1); i++)
                {
                    betweenSquares[i][0] = yKing;
                    betweenSquares[i][1] = xKing + 1 + i;
                }
            }
            else
            {
                for (int i = 0; i < (diff - 1); i++)
                {
                    betweenSquares[i][0] = yPiece;
                    betweenSquares[i][1] = xPiece + 1 + i;
                }
            }
            // loop over the array of betweenSquares
            // loop over the board to get my pieces
            // check if any of the pieces is not pinned and can move to that between Square
            wayCannotBeBlock = checkWayTiles(board, player, pieceLocation, diff, tempBoard, betweenSquares);
//            for(int k = 0; k < (diff - 1); k++)
//            {
//                for (int i = 1, counter = (BOARD_LENGTH - 1); (i < counter) && (wayCannotBeBlock); i++)
//                {
//                    for(int j = 1; (j < counter) && (wayCannotBeBlock); j++)
//                    {
//                        if ((!(board[i][j] == '-' || board[i][j] == '.'))
//                            && ((player == 'w' && board[i][j] == tolower(board[i][j]))
//                            || (player == 'b' && board[i][j] == toupper(board[i][j]))))
//                        {
//                            char pieceToMove = getPieceInside(board, i, j);
//                            char pieceToMoveLocation[2];
//                            pieceToMoveLocation[0] = (char)j;
//                            pieceToMoveLocation[1] = (char)i;
//
//                            int ySquare = betweenSquares[k][0];
//                            int xSquare = betweenSquares[k][1];
//
//                            char square[2];
//                            square[0] = ySquare;
//                            square[1] = xSquare;
//
//                            if(!(isPinned(board, tempBoard, pieceToMoveLocation, square)))
//                            {
//                                char currentMove[] = {(char)j, (char)i, (char)ySquare, (char)xSquare};
//                                if (isMovable(board, player, currentMove, pieceToMove) && tolower(pieceToMove) != 'k')
//                                {
//                                    wayCannotBeBlock = 0;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
        }
        else if ((xKing == xPiece) && (abs(yPiece - yKing) > 1))
        {
            int diff = abs(yPiece - yKing);
            int betweenSquares [10][2];
            if (yPiece > yKing)
            {
                for (int i = 0; i < (diff - 1); i++)
                {
                    betweenSquares[i][0] = yKing + 1 + i;
                    betweenSquares[i][1] = xKing;
                }
            }
            else
            {
                for (int i = 0; i < (diff - 1); i++)
                {
                    betweenSquares[i][0] = yPiece + 1 + i;
                    betweenSquares[i][1] = xPiece;
                }
            }
            wayCannotBeBlock = checkWayTiles(board, player, pieceLocation, diff, tempBoard, betweenSquares);
        }
            break;
        case 'b':
            diffX = xKing - xPiece;
            diffY = yKing - yPiece;

            int betweenSquares [10][2];
            if (diffX > 1 && diffY > 1)
            {
                for (int i = 0; i < (abs(diffX) - 1); i++)
                {
                    betweenSquares[i][0] = yPiece + 1 + i;
                    betweenSquares[i][1] = xPiece + 1 + i;
                }
                wayCannotBeBlock = checkWayDiagonals(board, player, pieceLocation, diffX, tempBoard, betweenSquares);
            }
            else if (diffX > 1 && diffY < -1)
            {
                for (int i = 0; i < (abs(diffX) - 1); i++)
                {
                    betweenSquares[i][0] = yPiece - 1 - i;
                    betweenSquares[i][1] = xPiece + 1 + i;
                }
                wayCannotBeBlock = checkWayDiagonals(board, player, pieceLocation, diffX, tempBoard, betweenSquares);
            }
            else if (diffX < -1 && diffY > -1)
            {
                for (int i = 0; i < (abs(diffX) - 1); i++)
                {
                    betweenSquares[i][0] = yPiece + 1 + i;
                    betweenSquares[i][1] = xPiece - 1 - i;
                }
                wayCannotBeBlock = checkWayDiagonals(board, player, pieceLocation, diffX, tempBoard, betweenSquares);
            }
            else if (diffX < -1 && diffY < -1)
            {
                for (int i = 0; i < (abs(diffX) - 1); i++)
                {
                    betweenSquares[i][0] = yKing - 1 - i;
                    betweenSquares[i][1] = xKing - 1 - i;
                }
                wayCannotBeBlock = checkWayDiagonals(board, player, pieceLocation, diffX, tempBoard, betweenSquares);
            }
            break;
        case 'q':
            if ((yPiece == yKing) && (abs(xPiece - xKing) > 1))
            {
                int diff = abs(xPiece - xKing);
                int betweenSquares [10][2];
                if (xPiece > xKing)
                {
                    for (int i = 0; i < (diff - 1); i++)
                    {
                        betweenSquares[i][0] = yKing;
                        betweenSquares[i][1] = xKing + 1 + i;
                    }
                }
                else
                {
                    for (int i = 0; i < (diff - 1); i++)
                    {
                        betweenSquares[i][0] = yPiece;
                        betweenSquares[i][1] = xPiece + 1 + i;
                    }
                }
                wayCannotBeBlock = checkWayTiles(board, player, pieceLocation, diff, tempBoard, betweenSquares);
            }
            else if ((xKing == xPiece) && (abs(yPiece - yKing) > 1))
            {
                int diff = abs(yPiece - yKing);
                int betweenSquares [10][2];
                if (yPiece > yKing)
                {
                    for (int i = 0; i < (diff - 1); i++)
                    {
                        betweenSquares[i][0] = yKing + 1 + i;
                        betweenSquares[i][1] = xKing;
                    }
                }
                else
                {
                    for (int i = 0; i < (diff - 1); i++)
                    {
                        betweenSquares[i][0] = yPiece + 1 + i;
                        betweenSquares[i][1] = xPiece;
                    }
                }
                wayCannotBeBlock = checkWayTiles(board, player, pieceLocation, diff, tempBoard, betweenSquares);
            }

            diffX = xKing - xPiece;
            diffY = yKing - yPiece;

            if (diffX > 1 && diffY > 1)
            {
                for (int i = 0; i < (abs(diffX) - 1); i++)
                {
                    betweenSquares[i][0] = yPiece + 1 + i;
                    betweenSquares[i][1] = xPiece + 1 + i;
                }
                wayCannotBeBlock = checkWayDiagonals(board, player, pieceLocation, diffX, tempBoard, betweenSquares);
            }
            else if (diffX > 1 && diffY < -1)
            {
                for (int i = 0; i < (abs(diffX) - 1); i++)
                {
                    betweenSquares[i][0] = yPiece - 1 - i;
                    betweenSquares[i][1] = xPiece + 1 + i;
                }
                wayCannotBeBlock = checkWayDiagonals(board, player, pieceLocation, diffX, tempBoard, betweenSquares);
            }
            else if (diffX < -1 && diffY > -1)
            {
                for (int i = 0; i < (abs(diffX) - 1); i++)
                {
                    betweenSquares[i][0] = yPiece + 1 + i;
                    betweenSquares[i][1] = xPiece - 1 - i;
                }
                wayCannotBeBlock = checkWayDiagonals(board, player, pieceLocation, diffX, tempBoard, betweenSquares);
            }
            else if (diffX < -1 && diffY < -1)
            {
                for (int i = 0; i < (abs(diffX) - 1); i++)
                {
                    betweenSquares[i][0] = yPiece - 1 - i;
                    betweenSquares[i][1] = xPiece - 1 - i;
                }
                wayCannotBeBlock = checkWayDiagonals(board, player, pieceLocation, diffX, tempBoard, betweenSquares);
            }
            break;
        default:
            break;
    }
    return wayCannotBeBlock;
}

int checkWayTiles(char board[BOARD_LENGTH][BOARD_LENGTH],
                    char player, int pieceLocation[], int diff,
                    char tempBoard[BOARD_LENGTH][BOARD_LENGTH], int betweenSquares[10][2])
{
    int wayCannotBeBlock = 1;
    for(int k = 0; (k < (diff - 1)) && (wayCannotBeBlock); k++)
    {
        for (int i = 1, counter = (BOARD_LENGTH - 1); (i < counter) && (wayCannotBeBlock); i++)
        {
            for(int j = 1; (j < counter) && (wayCannotBeBlock); j++)
            {
                if ((!(board[i][j] == '-' || board[i][j] == '.'))
                    && ((player == 'w' && board[i][j] == tolower(board[i][j]))
                    || (player == 'b' && board[i][j] == toupper(board[i][j]))))
                {
                    char pieceToMove = getPieceInside(board, i, j);
                    char pieceToMoveLocation[2];
                    pieceToMoveLocation[0] = (char)j;
                    pieceToMoveLocation[1] = (char)i;

                    int ySquare = betweenSquares[k][0];
                    int xSquare = betweenSquares[k][1];

                    char square[2];
                    square[0] = ySquare;
                    square[1] = xSquare;

                    if(!(isPinned(board, tempBoard, pieceToMoveLocation, square)))
                    {
                        char currentMove[] = {(char)j, (char)i, (char)ySquare, (char)xSquare};
                        if (isMovable(board, player, currentMove, pieceToMove) && tolower(pieceToMove) != 'k')
                        {
                            wayCannotBeBlock = 0;
                            return wayCannotBeBlock;
                        }
                    }
                }
            }
        }
    }
    return wayCannotBeBlock;
}

int checkWayDiagonals(char board[BOARD_LENGTH][BOARD_LENGTH],
                    char player, int pieceLocation[], int diffX,
                    char tempBoard[BOARD_LENGTH][BOARD_LENGTH], int betweenSquares[10][2])
{
    int wayCannotBeBlock = 1;
    for(int k = 0; (k < (abs(diffX) - 1)) && (wayCannotBeBlock); k++)
    {
        for (int i = 1, counter = (BOARD_LENGTH - 1); (i < counter) && (wayCannotBeBlock); i++)
        {
            for(int j = 1; (j < counter) && (wayCannotBeBlock); j++)
            {
                if ((!(board[i][j] == '-' || board[i][j] == '.'))
                    && ((player == 'w' && board[i][j] == tolower(board[i][j]))
                    || (player == 'b' && board[i][j] == toupper(board[i][j]))))
                {
                    char pieceToMove = getPieceInside(board, i, j);
                    char pieceToMoveLocation[2];
                    pieceToMoveLocation[0] = (char)j;
                    pieceToMoveLocation[1] = (char)i;

                    int ySquare = betweenSquares[k][0];
                    int xSquare = betweenSquares[k][1];

                    char square[2];
                    square[0] = ySquare;
                    square[1] = xSquare;

                    if(!(isPinned(board, tempBoard, pieceToMoveLocation, square)))
                    {
                        char currentMove[] = {(char)j, (char)i, (char)ySquare, (char)xSquare};
                        if (isMovable(board, player, currentMove, pieceToMove) && tolower(pieceToMove) != 'k')
                        {
                            wayCannotBeBlock = 0;
                            return wayCannotBeBlock;
                        }
                    }
                }
            }
        }
    }
    return wayCannotBeBlock;
}

void getKingLocation(char board[BOARD_LENGTH][BOARD_LENGTH], char player, int coord[])
{
    int found = 0;
    char kingChar = (player == 'w') ? 'k' : 'K';
    for (int i = 1, counter = BOARD_LENGTH - 1; i < counter && !found; i++)
    {
        for (int k = 1; k < counter && !found; k++)
        {
            if(board[i][k] == kingChar)
            {
                found = 1;
                coord[0] = i; coord[1] = k;
            }
        }
    }
}
