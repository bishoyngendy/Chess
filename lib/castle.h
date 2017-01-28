#ifndef CASTLE_H_INCLUDED
#define CASTLE_H_INCLUDED



#endif // CASTLE_H_INCLUDED

int checkCastleWay(char board[BOARD_LENGTH][BOARD_LENGTH], char player, char type);

int prevMotion(char gameMoves[GAME_MOVES][7] , int *currentMoveIndex, char player, char type);

int squaresNotAllowed(char board[BOARD_LENGTH][BOARD_LENGTH], char player, char type,
                        char tempBoard[BOARD_LENGTH][BOARD_LENGTH], , int kingLocation[]);

void castle(char board[BOARD_LENGTH][BOARD_LENGTH], char player, int type,
            char tempBoard[BOARD_LENGTH][BOARD_LENGTH], char gameMoves[GAME_MOVES][7] , int *currentMoveIndex,
            char moveOne[], char moveTwo[]);
