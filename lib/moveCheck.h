#ifndef MOVECHECK_H_INCLUDED
#define MOVECHECK_H_INCLUDED

#endif // MOVECHECK_H_INCLUDED

// return (0 for wrong) (1 for true)
int checkRockMove(char coord[]);

// check if there are any pieces in the way of the rock
// return zero if there is a piece in the way of the rock
// return one in case there is no pieces in the way
int checkRockWay(char board[BOARD_LENGTH][BOARD_LENGTH], char coord[]);

// check if there are any pieces in the way of the bishop
// return zero if there is a piece in the way of the bishop
// return one in case there is no pieces in the way
int checkBishopWay(char board[BOARD_LENGTH][BOARD_LENGTH], char coord[]);

// check if there are any pieces in the way of the queen
// return zero if there is a piece in the way of the queen
// return one in case there is no pieces in the way
int checkQueenWay(char board[BOARD_LENGTH][BOARD_LENGTH], char coord[]);

// return (0 for wrong) (1 for true)
int checkBishopMove(char coord[]);

// return (0 for wrong) (1 for true)
int checkKnightMove(char coord[]);

// return (0 for wrong) (1 for true)
int checkKingMove(char coord[]);

// return (0 for wrong) (1 for true) get the player as a char 'w' or 'b'
int checkPawnMove(char board[BOARD_LENGTH][BOARD_LENGTH], char coord[], char player);

// return (0 for wrong) (1 for true) get the player as a char 'w' or 'b'
int checkPawnCapture(char board[BOARD_LENGTH][BOARD_LENGTH], char coord[], char player);

// return (0 when trying to promote) (1 for false) get the player as a char 'w' or 'b'
int checkPawnPromotion (char coord[], char player);

// return (0 for wrong) (1 for true)
int checkQueenMove(char coord[]);

// check if the from & to coordinates are the same (0 for wrong) (1 for true)
int checkSameMove(char coord[]);

// check if the piece can move to a new position
// return 1 for true - 0 for invalid move - -1 for empty square
int isMovable(char board[BOARD_LENGTH][BOARD_LENGTH], char currentPlayer, char currentMove[], char piece);

// returns 1 for true && (0 for false)
int isPinned(char board[BOARD_LENGTH][BOARD_LENGTH], char tempboard[BOARD_LENGTH][BOARD_LENGTH],
             char pieceLocation[], char desireLocation[]);
