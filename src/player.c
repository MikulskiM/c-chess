#include <stdio.h>
#include <ctype.h>
#include "player.h"

int row_to_index(char row){
    // input row -> array index
    return '8' - row;
}

int column_to_index(char column){
    // input column -> array index
    column = toupper(column);
    return column - 'A';
}

int wrong_index(int row_index, int column_index, ChessPiece board[ROW_LENGTH][ROW_LENGTH]){
    if (row_index >= 0 && row_index < ROW_LENGTH && column_index >= 0 && column_index < ROW_LENGTH) {
        return 0;
    } else {
        printf("WRONG INDEX\n");
        return 1;
    }
}

void ask_move(Player player, ChessPiece board[ROW_LENGTH][ROW_LENGTH]){
    int row_index = 0;
    int column_index = 0;
    char figure_coords[2] = {'0', '0'};
    char move_coords[2] = {'0', '0'};

    printf("\t[ %c ]\tMake a move - select figure: ", player.color);
    scanf("%2s", figure_coords);

    // b8 or B8 or 8B or 8b
    if (isdigit(figure_coords[0])){
        row_index = row_to_index(figure_coords[0]);
        column_index = column_to_index(figure_coords[1]);
    } else if (isdigit(figure_coords[1])){
        row_index = row_to_index(figure_coords[1]);
        column_index = column_to_index(figure_coords[0]);
    } else{
        printf("NO DIGITS DETECTED\n");
        printf("WRONG FORMAT!\n");
    }

    if (wrong_index(row_index, column_index, board)){
        printf("\n\tERROR WRONG INDEX DETECTED!\n");
    }

    printf("Selected piece: %c [ %c ]\n", board[row_index][column_index].piece, board[row_index][column_index].color);
    if (player.color == board[row_index][column_index].color){
        printf("THAT'S YOUR PIECE - CORRECT\n");
    } else{
        printf("THAT'S NOT YOUR PIECE - YOU CAN'T MOVE IT\n");
    }

    printf("where to move: ");
    scanf("%2s", move_coords);
}
