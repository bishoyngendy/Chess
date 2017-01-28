#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#endif // GLOBAL_H_INCLUDED

#define TYPES_NUMBER 6
#define PROMOTIONS_NUMBER 4
#define BOARD_LENGTH 10
#define PIECES_NUMBER 16
#define ASCII_DIFF 32
#define GAME_MOVES 300

//char types[TYPES_NUMBER] = {'p', 'r', 'n', 'b', 'q', 'k'};
char getPieceInside(char board[BOARD_LENGTH][BOARD_LENGTH], int x, int y);

// covert the char array values to int
void convertInput(char inpArr[]);
