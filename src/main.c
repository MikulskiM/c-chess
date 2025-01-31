#include <stdio.h>
#include "board.h"
#include "player.h"

int main(){
    ChessPiece  board[ROWS][COLUMNS];
    int         game_is_active  = TRUE;
    Player      player_w        = {WHITE};
    Player      player_b        = {BLACK};
    int         is_black_turn   = FALSE;

    initialize_board(board);

    while(game_is_active) {

        print_board(board);

        if(is_black_turn){
            ask_move(player_b, board, &game_is_active);
            is_black_turn = FALSE;
        }
        else{
            ask_move(player_w, board, &game_is_active);
            is_black_turn = TRUE;
        }
    }

    print_board(board);

    return 0;
}