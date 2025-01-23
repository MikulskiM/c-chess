#include <stdio.h>
#include <ctype.h>
#include "player.h"

int row_to_index(char row) {
    return ROWS - (row - '0');
}

int column_to_index(char column) {
    return column - 'a';
}

int wrong_index(int row_index, int column_index, ChessPiece board[ROWS][COLUMNS]) {
    return row_index < 0 || row_index >= ROWS || column_index < 0 || column_index >= COLUMNS;
}

void ask_move(Player player, ChessPiece board[ROWS][COLUMNS]) {
    int row_index = 0;
    int column_index = 0;
    int move_row_index = 0;
    int move_column_index = 0;
    char figure_coords[2] = {'0', '0'};
    char move_coords[2] = {'0', '0'};

    printf("\t[ %c ]\tMake a move - select figure: ", player.color);
    scanf("%2s", figure_coords);

    // convert piece coordinates to the array indexes
    if (isdigit(figure_coords[0])) {
        row_index = row_to_index(figure_coords[0]);
        column_index = column_to_index(figure_coords[1]);
    } else if (isdigit(figure_coords[1])) {
        row_index = row_to_index(figure_coords[1]);
        column_index = column_to_index(figure_coords[0]);
    } else {
        printf("NO DIGITS DETECTED\n");
        printf("WRONG FORMAT!\n");
        return;
    }

    if (wrong_index(row_index, column_index, board)) {
        printf("\n\tERROR WRONG INDEX DETECTED!\n");
        return;
    }

    printf("Selected piece: %c [ %c ]\n", board[row_index][column_index].piece, board[row_index][column_index].color);

    // Check if this is the corect color
    if (player.color == board[row_index][column_index].color) {
        printf("THAT'S YOUR PIECE - CORRECT\n");
    } else {
        printf("THAT'S NOT YOUR PIECE - YOU CAN'T MOVE IT\n");
        return;
    }

    printf("where to move: ");
    scanf("%2s", move_coords);

    // convert piece coordinates to the array indexes
    if (isdigit(move_coords[0])) {
        move_row_index = row_to_index(move_coords[0]);
        move_column_index = column_to_index(move_coords[1]);
    } else if (isdigit(move_coords[1])) {
        move_row_index = row_to_index(move_coords[1]);
        move_column_index = column_to_index(move_coords[0]);
    } else {
        printf("NO DIGITS DETECTED\n");
        printf("WRONG FORMAT!\n");
        return;
    }

    // check if that move is legal
    if (wrong_index(move_row_index, move_column_index, board)) {
        printf("\n\tERROR WRONG INDEX DETECTED!\n");
        return;
    }

    // Get the pointer to the function checking if this piece can do this move
    int (*can_make_this_move)(ChessPiece *, ChessPiece[ROWS][COLUMNS], char, int) = board[row_index][column_index].can_make_this_move;

    // Get the pointer to the function making move
    void (*make_this_move)(ChessPiece *, ChessPiece[ROWS][COLUMNS], char, int) = board[row_index][column_index].make_this_move;

    // Check function pointers
    if (can_make_this_move != NULL) {
        // use can_make_this_move()
        if (can_make_this_move(&board[row_index][column_index], board, move_column_index + 'a', ROWS- move_row_index)) {
            printf("Move is legal. Moving piece.\n");
            
            // use make_this_move()
            if (make_this_move != NULL) {
                make_this_move(&board[row_index][column_index], board, move_column_index + 'a', ROWS - move_row_index);
                printf("Piece moved successfully.\n");
            } else {
                printf("Error: No valid move function assigned.\n");
            }
        } else {
            printf("Invalid move.\n");
        }
    } else {
        printf("Error: No valid move check function assigned.\n");
    }
}
