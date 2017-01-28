#ifndef UNDO_H_INCLUDED
#define UNDO_H_INCLUDED



#endif // UNDO_H_INCLUDED

// return 0 for fail && 1 for success
int undo(char board[BOARD_LENGTH][BOARD_LENGTH], char gameMoves[GAME_MOVES][7] , int *currentMoveIndex,
         int* capturedWhiteSize, int* capturedBlackSize, int* redoSize);

 // return 0 for fail && 1 for success
int redo(char board[BOARD_LENGTH][BOARD_LENGTH], char gameMoves[GAME_MOVES][7] , int *currentMoveIndex,
         int* capturedWhiteSize, int* capturedBlackSize, int* redoSize);
//save the current move in the game history
void saveMove(char gameMoves[GAME_MOVES][7] , int *currentMoveIndex, char currentMove[]);

