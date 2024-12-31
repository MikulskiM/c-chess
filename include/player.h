#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

typedef struct Player{
    char color;
} Player;

void ask_move(Player player, ChessPiece board[ROW_LENGTH][ROW_LENGTH]);

#endif // PLAYER_H