#ifndef MAKEMOVE_H_INCLUDED
#define MAKEMOVE_H_INCLUDED



#endif // MAKEMOVE_H_INCLUDED

// moves a piece to another square and replaces its previous square with its color
void makeMove(char board[BOARD_LENGTH][BOARD_LENGTH], char move[])
void promote (char board[BOARD_LENGTH][BOARD_LENGTH], char move[], char player);
void capture(char captureArr[], int* arrSize, char piece);
