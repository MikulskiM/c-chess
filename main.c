#include <stdio.h>
#include "board.h"
#include "player.h"

int main(){
    ChessPiece board[ROW_LENGTH][ROW_LENGTH];

    initialize_board(board);

    print_board(board);

    Player player_w = {WHITE};
    ask_move(player_w, board);

    return 0;
}