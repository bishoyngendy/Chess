#include <stdio.h>
#include <stdlib.h>
#include "lib/validation.h"
#include "lib/global.h"
#include "lib/intialization.h"
#include "lib/check.h"
#include "lib/undo.h"
#include "lib/stalemate.h"
#include "windows.h"

// global variables
char currentMove[7];

// for storing the game
char gameMoves[GAME_MOVES][7];
int currentMoveIndex = 0;
int redoSize = 0;

// 0 for game continuation - 1 for draw 2 for white win - 3 for black win
int gameEnded;
char currentPlayer;
char capturedWhite[PIECES_NUMBER];
char capturedBlack[PIECES_NUMBER];
char moveOne[7];
char moveTwo[7];
int capturedWhiteSize = 0; int capturedBlackSize = 0;

// prototypes
int getMove();
char startGame();

char board [BOARD_LENGTH][BOARD_LENGTH] = {
                    {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', ' '},
                    {'1', 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', '1'},
                    {'2', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', '2'},
                    {'3', '.', '-', '.', '-', '.', '-', '.', '-', '3'},
                    {'4', '-', '.', '-', '.', '-', '.', '-', '.', '4'},
                    {'5', '.', '-', '.', '-', '.', '-', '.', '-', '5'},
                    {'6', '-', '.', '-', '.', '-', '.', '-', '.', '6'},
                    {'7', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', '7'},
                    {'8', 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', '8'},
                    {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', ' '}
                    };

char tempBoard[BOARD_LENGTH][BOARD_LENGTH]= {
                    {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', ' '},
                    {'1', 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', '1'},
                    {'2', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', '2'},
                    {'3', '.', '-', '.', '-', '.', '-', '.', '-', '3'},
                    {'4', '-', '.', '-', '.', '-', '.', '-', '.', '4'},
                    {'5', '.', '-', '.', '-', '.', '-', '.', '-', '5'},
                    {'6', '-', '.', '-', '.', '-', '.', '-', '.', '6'},
                    {'7', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', '7'},
                    {'8', 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', '8'},
                    {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', ' '}
                    };

int main()
{
    gameEnded = 0;
    currentPlayer = 'w';

    int logicValidMove = 0, promValidMove = 0;
    int checkCurrentKing = 0; int checkOppenentKing = 0;
    int currentKingLocation[2]; int opponentKingLocation[2];

    char newGame = startGame();

    if (newGame == 'L')
        loadGame(gameMoves, board, &currentMoveIndex, capturedWhite, capturedBlack, &capturedWhiteSize, &capturedBlackSize);
    else if (newGame != 'N')
        printf("There isn't any saved game.... Staring a new one\n");
    else
        printf("Starting a new game\n\n\n");

    fflush(stdin); // free the buffer before start getting games

    while(gameEnded == 0)
    {
        // get the current player and the opponent one
        char* player = currentPlayer == 'w' ? "white" : "black";
        char opponentPlayer = currentPlayer == 'w' ? 'b' : 'w';

        // print the board
        PrintBoard(board, currentPlayer,
                   capturedWhite, &capturedWhiteSize,
                   capturedBlack, &capturedBlackSize);
        printf("\n");

        // warning if the king is checked
        if (checkOppenentKing == 1)
            printf("Be careful! Your king is checked\n");

        printf("Press U for Undo, R for Redo, S for Save \nIt's %s's turn: ", player);

        // getting the new move
        int size = getMove(); // get the size of the entered move

        // check for entry syntax
        //(0 not valid) (1 valid move) (2 valid move in promotion)
        //(3 for undo) (4 for redo) (-1 for save)
        int valid = checkValidMove(currentMove, size);

        convertInput(currentMove); // convert the alphabet entry to int

        //checkSameMove returns 0 if it is the same move and 1 if not
        if (valid && !(checkSameMove(currentMove)))
            valid = 0;

        char piece;
        switch(valid){
        case -1:
            saveGame(gameMoves,currentMoveIndex, board);
            printf("Game Saved\n");
            continue;
        break;
        case 0:
            printf("\nEnter a valid move for %s: \n", player);
            continue;
            break;
        case 1: // 4 digits as input
            piece = getPieceInside(board, currentMove[1], currentMove[0]);
            if (!playMyPiece(piece, currentPlayer))
            {
                printf("\nYou can't move the other player's piece !!\n\n");
                continue;
            }

            char square = getPieceInside(board, currentMove[3], currentMove[2]);
            if (!(square == '.' || square == '-')) // check capture own pieces
            {
                // check that no one can capture his pieces
                if (playMyPiece(square, currentPlayer))
                {
                    printf("\nYou can't capture your pieces !!\n\n");
                    continue;
                }
            }

            // return 1 for true, 0 for invalid, -1 for empty square (check move for each piece)
            logicValidMove = isMovable(board, currentPlayer, currentMove, piece);
            if (logicValidMove == -1)
            {
                printf("\nPlease enter a non empty square !!\n");
                continue;
            }
            else if(logicValidMove == 0)
            {
                printf("\nPlease enter a valid move. \n");
                continue;
            }
            break;
        case 2: // 5 digits as input
            logicValidMove = 0;
            piece = getPieceInside(board, currentMove[1], currentMove[0]);
            if (tolower(piece) == 'p')
            {
                promValidMove = checkPawnMove(board, currentMove, currentPlayer)
                                || checkPawnCapture(board, currentMove, currentPlayer)
                                && !checkPawnPromotion(currentMove, currentPlayer);
            }
            else
            {
                printf("5 chars is only available when promoting a pawn\n");
                continue;
            }
            break;
        case 3: // Undo
            // make sure he can't undo the first move
            if (undo(board, gameMoves, &currentMoveIndex, &capturedWhiteSize, &capturedBlackSize, &redoSize))
            {
                currentPlayer = (currentPlayer == 'w') ? 'b' : 'w';
                getKingLocation(board, currentPlayer, opponentKingLocation); // save king location to opponentKingLocation
                checkOppenentKing = isChecked(board,opponentPlayer,opponentKingLocation);
            }
            continue;
            break;
        case 4: // Redo
            if(redo(board, gameMoves, &currentMoveIndex, &capturedWhiteSize, &capturedBlackSize, &redoSize))
            {
                currentPlayer = (currentPlayer == 'w') ? 'b' : 'w';
                getKingLocation(board, currentPlayer, opponentKingLocation); // save king location to opponentKingLocation
                checkOppenentKing = isChecked(board,opponentPlayer,opponentKingLocation);
            }
            continue;
            break;
        case 5: // short castle
            logicValidMove = 0;
            getKingLocation(board, currentPlayer, currentKingLocation); // save king location to currentKingLocation
            if((squaresNotAllowed(board, currentPlayer, 's', tempBoard, currentKingLocation))&&
                (prevMotion(gameMoves, &currentMoveIndex, currentPlayer, 's')) &&
                (checkCastleWay(board, currentPlayer, 's')))
            {
                castle(board, currentPlayer, 's', tempBoard, gameMoves,
                        &currentMoveIndex, moveOne, moveTwo);
                currentPlayer = (currentPlayer == 'w') ? 'b' : 'w';
            }
            else
            {
                printf("Castling not allowed\n");
            }
            continue;
            break;
        case 6: // long castle
            logicValidMove = 0;
            getKingLocation(board, currentPlayer, currentKingLocation); // save king location to currentKingLocation
            if((!squaresNotAllowed(board, currentPlayer, 'l', tempBoard, currentKingLocation))&&
                (prevMotion(gameMoves, &currentMoveIndex, currentPlayer, 'l')) &&
                (checkCastleWay(board, currentPlayer, 'l')))
            {
                castle(board, currentPlayer, 'l', tempBoard, gameMoves,
                        &currentMoveIndex, moveOne, moveTwo);
                currentPlayer = (currentPlayer == 'w') ? 'b' : 'w';
            }
            else
            {
                printf("Castling not allowed\n");
            }
            continue;
            break;
        }

        // valid move but not a promotion
        if (logicValidMove)
        {
            char square = getPieceInside(board, currentMove[3], currentMove[2]);
            currentMove[5] = square;
            currentMove[4] = piece;
            currentMove[6] = ' '; // This means that it is not a promotion move

            if (!(square == '.' || square == '-')) // capture
            {
                char* captArr = (currentPlayer == 'w') ? capturedBlack : capturedWhite;
                int* size = currentPlayer == 'w' ? &capturedBlackSize : &capturedWhiteSize;
                capture(captArr, size, square);
            }
            makeMove(board, currentMove);
            makeMove(tempBoard, currentMove);

            saveMove(gameMoves, &currentMoveIndex, currentMove); // save in history
            redoSize = 0;
        }
        else if (promValidMove)
        {
            char square = getPieceInside(board, currentMove[3], currentMove[2]);

            if (!(square == '.' || square == '-')) // capture
            {
                char* captArr = (currentPlayer == 'w') ? capturedBlack : capturedWhite;
                int* size = currentPlayer == 'w' ? &capturedBlackSize : &capturedWhiteSize;
                capture(captArr, size, square);
            }
            promote(board, currentMove, currentPlayer);
            promote(tempBoard, currentMove, currentPlayer);

            currentMove[5] = square;
            currentMove[4] = piece;
            currentMove[6] = currentPlayer == 'w' ? 'p' : 'P'; // This means that it is a promotion move

            saveMove(gameMoves, &currentMoveIndex, currentMove);
            redoSize = 0;
        }
        // swap players
        currentPlayer = (currentPlayer == 'w') ? 'b' : 'w';
        opponentPlayer = currentPlayer == 'w' ? 'b' : 'w';

        // check for any checks
        checkCurrentKing = 0; checkOppenentKing = 0;
        // get the current king's location
        getKingLocation(board,opponentPlayer,currentKingLocation); // save king location to currentKingLocation
        // check if it's king will be checked
        checkCurrentKing = isChecked(board,opponentPlayer,currentKingLocation);

        if (checkCurrentKing == 1)
        {
            printf("\nYou can't play this!\nCheck\n");
            if (undo(board, gameMoves, &currentMoveIndex, &capturedWhiteSize, &capturedBlackSize, &redoSize))
            {
                currentPlayer = (currentPlayer == 'w') ? 'b' : 'w';
            }
            continue;
        }

        // get the opponent king's location
        getKingLocation(board, currentPlayer, opponentKingLocation); // save king location to opponentKingLocation
        // check if the other's king will be checked
        checkOppenentKing = isChecked(board,currentPlayer,opponentKingLocation);

        if(checkOppenentKing)
        {
            int pieceLocation[2] = {0,0};

            getCheckingPieceLoc(board,currentPlayer,opponentKingLocation, pieceLocation);

            if(kingCannotMove(board, currentPlayer, opponentKingLocation, tempBoard)
               && pieceCannotBeCaptured(board, currentPlayer, pieceLocation, tempBoard)
               && wayCannotBeBlocked(board, currentPlayer, pieceLocation, opponentKingLocation, tempBoard))
            {
                PrintBoard(board, currentPlayer,
                   capturedWhite, &capturedWhiteSize,
                   capturedBlack, &capturedBlackSize);
                printf("Checkmate: %s Wins :)\n\n", player);
                gameEnded = 3;
            }
        }
        else if (!availbleMove(board, currentPlayer))
        {
            printf("Stalmate :)\n\n");
            gameEnded = 2;
        }
        else if (capturedWhiteSize == 15 && capturedBlackSize == 15) // there is only the kings
        {
            printf("Draw :)\n\n");
            gameEnded = 2;
        }
    }

    return 0;
}

// return the inputted character
char startGame()
{
    //  validation on starting a new game or to load an old one
    char newGame;    char tmpGame;
    printf("To start a new game enter N. \nPress L to load the saved game\n");
    int validEntry = scanf(" %c%c", &newGame, &tmpGame);
    fflush(stdin);
    while(validEntry != 2 || (tmpGame != '\n') || (newGame != 'N' && newGame != 'L'))
    {
        printf("Please enter a valid entry!\n");
        printf("To start a new game enter N. \nPress L to load the saved game\n");
        validEntry = scanf(" %c%c", &newGame, &tmpGame);
        fflush(stdin);
    }

    return newGame;
}

// return the size of the array
int getMove()
{
    int i = 0;
    int status = 1;
    while(status)
    {
        currentMove[i++] = getchar();
        if ((i > 6)) status = 0; // to read a maximum of 6 digits
        else if ((currentMove[i - 1] == '\0') || (currentMove[i - 1] == '\n')) status = 0;
    }
    fflush(stdin);

    return i; // i is the array size
}
