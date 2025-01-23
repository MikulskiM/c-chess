#include <stdio.h>
#include "board.h"
#include "player.h"

int main(){
    ChessPiece board[ROWS][COLUMNS];

    initialize_board(board);

    print_board(board);

    Player player_w = {WHITE};
    ask_move(player_w, board);

    print_board(board);

    return 0;
}