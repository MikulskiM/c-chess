#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

typedef struct {
    char color; // WHITE or BLACK
} Player;

void ask_move(Player player, ChessPiece board[ROWS][COLUMNS], int* want_to_play);

int row_to_index(char row);
int column_to_index(char column);
int wrong_index(int row_index, int column_index, ChessPiece board[ROWS][COLUMNS]);

#endif // PLAYER_H