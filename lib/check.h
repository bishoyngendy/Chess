#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED



#endif // CHECK_H_INCLUDED

// get a piece (x & Y location) and the king location
// return true (1) if the king is check by that piece
int isChecked(char board[BOARD_LENGTH][BOARD_LENGTH], char currentPlayer, int currentMove[]);

int getCheckingPieceLoc(char board[BOARD_LENGTH][BOARD_LENGTH], char player, int kingLocation[], int pieceLocation[]);
// To handle Checkmate
// returns 1 for true (0 for false)
int kingCannotMove(char board[BOARD_LENGTH][BOARD_LENGTH], char player, int kingLocation[], char tempBoard[BOARD_LENGTH][BOARD_LENGTH]);

// returns 1 for true (0 for false)
int pieceCannotBeCaptured(char board[BOARD_LENGTH][BOARD_LENGTH], char player,
                          int pieceLocation[], char tempBoard[BOARD_LENGTH][BOARD_LENGTH]);

// returns 1 for true (0 for false)
int wayCannotBeBlocked (char board[BOARD_LENGTH][BOARD_LENGTH],
                        char player, int pieceLocation[], int kingLocation[],
                        char tempBoard[BOARD_LENGTH][BOARD_LENGTH]);

// to get king Location
void getKingLocation(char board[BOARD_LENGTH][BOARD_LENGTH], char player, int coord[]);
