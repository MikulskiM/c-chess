#include <stdio.h>
#include "board.h"
#include "player.h"

int main(){
    ChessPiece  board[ROWS][COLUMNS];
    int         want_to_play    = TRUE;
    Player      player_w        = {WHITE};
    Player      player_b        = {BLACK};
    int         black_move      = FALSE;

    initialize_board(board);

    while(want_to_play) {

        print_board(board);

        if(black_move){
            ask_move(player_b, board, &want_to_play);
            black_move = FALSE;
        }
        else{
            ask_move(player_w, board, &want_to_play);
            black_move = TRUE;
        }
    }

    print_board(board);

    return 0;
}