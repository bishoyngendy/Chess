#include <stdlib.h>
#include "global.h"
#include <ctype.h>

// prototypes
int checkMoveFour(char str[]);
int checkMoveFive(char str[]);
int checkMoveOne(char str[]);
int checkMoveThree(char str[]);

char promotions[PROMOTIONS_NUMBER] = {'R', 'N', 'B', 'Q'};

// check for valid move for each game
int checkValidMove(char str[], int arrSize)
{
    int status;
    switch(arrSize) { // go to the case of its size
        case 2: status = checkMoveOne(str);
        break;
        case 4: status = checkMoveThree(str);
        break;
        case 5: status = checkMoveFour(str);
        break;
        case 6: status = checkMoveFive(str);
        break;
        default: status = 0;
        break;
    }
    return status;
}

// return (0 for false) (1 for true)
int checkMoveFour(char str[])
{
    int status = 0;

    if( str[0] >= 'A' && str[0] <= ('A'+7) && // check for the range of each char for index 0 & 2 in range of A and A+8
        str[2] >= 'A' && str[0] <= ('A'+7) && // for index 1 and 3 in range of 1 and 8
        str[1] >= '1' && str[1] <= '8' &&
        str[3] >= '1' && str[3] <= '8' ) {status = 1;}

    return status;
}

// return (0 for false) (2 for true)
int checkMoveFive(char str[])
{
    int status = checkMoveFour(str);
    char found = 0; // hold the current status (1 => false)

    if (status == 1)
    {
        for (int i = 0; i <PROMOTIONS_NUMBER && !found; i++)
        {
            found = (str[4] == promotions[i]) ? 1 : 0; // check for the fifth char if it exist in the promotions
        }
    }
    if (str[0] == 'O' && str[1] == '-' && str[2] == 'O' && str[3] == '-' && str[4] == 'O') status = 6;

    if(found == 1 && status == 1) status = 2;
    return status;
}

// return (3 for undo) (4 for redo)
int checkMoveOne(char str[])
{
    int status = 0;
    if (str[0] == 'U') status = 3;
    else if (str[0] == 'R') status = 4;
    else if(str[0] == 'S') status = -1;
    return status;
}

int checkMoveThree(char str[])
{
    int status = 0;
    if (str[0] == 'O' && str[1] == '-' && str[2] == 'O') status = 5;
    return status;
}

int playMyPiece (char piece, char player)
{
    if (player == 'w' && piece == tolower(piece))
    {
        return 1;
    }
    else if (player == 'b' && piece == toupper(piece))
    {
        return 1;
    }
    return 0;
}


