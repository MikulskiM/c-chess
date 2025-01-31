#include <stdio.h>
#include <ctype.h>
#include "player.h"

int row_to_index(char row) {
    return ROWS - (row - '0');
}

int column_to_index(char column) {
    return column - 'a';
}

int invalid_index(int row_index, int column_index) {
    return row_index < 0 || row_index >= ROWS || column_index < 0 || column_index >= COLUMNS;
}

void display_winner(char color) {
    if (color == BLACK) {
        printf(" ___   _        _    __   __  ___   ___     ___   _        _      ___   _  __   __      __  ___   _  _   ___   _ \n");
        printf("| _ \\ | |      /_\\   \\ \\ / / | __| | _ \\   | _ ) | |      /_\\    / __| | |/ /   \\ \\    / / |_ _| | \\| | / __| | |\n");
        printf("|  _/ | |__   / _ \\   \\ V /  | _|  |   /   | _ \\ | |__   / _ \\  | (__  | ' <     \\ \\/\\/ /   | |  | .` | \\__ \\ |_|\n");
        printf("|_|   |____| /_/ \\_\\   |_|   |___| |_|_\\   |___/ |____| /_/ \\_\\  \\___| |_|\\_\\     \\_/\\_/   |___| |_|\\_| |___/ (_)\n");                                                                                              
    } else {
        printf(" ___   _        _    __   __  ___   ___    __      __  _  _   ___   _____   ___    __      __  ___   _  _   ___   _ \n");
        printf("| _ \\ | |      /_\\   \\ \\ / / | __| | _ \\   \\ \\    / / | || | |_ _| |_   _| | __|   \\ \\    / / |_ _| | \\| | / __| | |\n");
        printf("|  _/ | |__   / _ \\   \\ V /  | _|  |   /    \\ \\/\\/ /  | __ |  | |    | |   | _|     \\ \\/\\/ /   | |  | .` | \\__ \\ |_|\n");
        printf("|_|   |____| /_/ \\_\\   |_|   |___| |_|_\\     \\_/\\_/   |_||_| |___|   |_|   |___|     \\_/\\_/   |___| |_|\\_| |___/ (_)\n");
    }
}

void get_piece_coordinates(char coords[2], int *row_index, int *column_index) {
    if (isdigit(coords[0])) {
        *row_index = row_to_index(coords[0]);
        *column_index = column_to_index(coords[1]);
    } else if (isdigit(coords[1])) {
        *row_index = row_to_index(coords[1]);
        *column_index = column_to_index(coords[0]);
    } else {
        printf("\tNO DIGITS DETECTED\n");
        printf("\tWRONG FORMAT! To quit type \"00\"\n");
        *row_index = -1;
        *column_index = -1;
    }
}

void validate_piece(Player player, ChessPiece board[ROWS][COLUMNS], int row_index, int column_index, int *piece_is_correct) {
    if (invalid_index(row_index, column_index)) {
        printf("\n\tERROR WRONG INDEX DETECTED!\n");
        printf("\tTo quit type \"00\"\n");
        *piece_is_correct = FALSE;
    }

    printf("Selected piece: %c [ %c ]\n", board[row_index][column_index].piece, board[row_index][column_index].color);

    if (player.color == board[row_index][column_index].color) {
        printf("THAT'S YOUR PIECE - CORRECT\n");
        *piece_is_correct = TRUE;
    } else {
        printf("THAT'S NOT YOUR PIECE - YOU CAN'T MOVE IT\n");
        printf("\tTo quit type \"00\"\n");
        *piece_is_correct = FALSE;
    }
}

void validate_and_execute_move(ChessPiece *selected_piece, ChessPiece board[ROWS][COLUMNS], 
                               int move_column_index, int move_row_index, int *move_is_correct) {
    if (invalid_index(move_row_index, move_column_index)) {
        printf("\n\tERROR WRONG INDEX DETECTED!\n");
        *move_is_correct = FALSE;
    }
    
    // get the pointer to the function checking if that move is valid
    int (*can_make_this_move)(ChessPiece *, ChessPiece[ROWS][COLUMNS], char, int) = selected_piece->can_make_this_move;
    
    // get the pointer to the function making move
    void (*make_this_move)(ChessPiece *, ChessPiece[ROWS][COLUMNS], char, int) = selected_piece->make_this_move;

    if (!can_make_this_move) {
        printf("Error: No valid move check function assigned.\n");
        *move_is_correct = FALSE;
    }

    if (can_make_this_move(selected_piece, board, move_column_index + 'a', ROWS - move_row_index)) {
        printf("Move is legal. Moving piece.\n");
        if (make_this_move) {
            make_this_move(selected_piece, board, move_column_index + 'a', ROWS - move_row_index);
            printf("Piece moved successfully.\n");
            *move_is_correct = TRUE;
            return;
        } else {
            printf("Error: No valid move function assigned.\n");
        }
    } else {
        printf("Invalid move.\n");
    }
    *move_is_correct = FALSE;
}

void ask_move(Player player, ChessPiece board[ROWS][COLUMNS], int *game_is_active) {
    int     row_index           = 0;
    int     column_index        = 0;
    int     move_row_index      = 0;
    int     move_column_index   = 0;
    char    figure_coords[2]    = {'0', '0'};
    char    move_coords[2]      = {'0', '0'};
    int     piece_is_correct    = FALSE;
    int     move_is_correct     = FALSE;

    do {
        printf("\t[ %c ]\tMake a move - select figure: ", player.color);
        scanf("%2s", figure_coords);

        if ((figure_coords[0] == '0' && figure_coords[1] == '0') || 
            (figure_coords[0] == 'e' && figure_coords[1] == 'x')) {
            *game_is_active = FALSE;
            printf("\t[ %c ]:\tI quit! You won...\n", player.color);
            if (player.color == WHITE) {
                display_winner(BLACK);
            }
            else {
                display_winner(WHITE);
            }
            return;
        }

        get_piece_coordinates(figure_coords, &row_index, &column_index);
        validate_piece(player, board, row_index, column_index, &piece_is_correct);

    } while (piece_is_correct == FALSE);

    do {
        printf("Where to move: ");
        scanf("%2s", move_coords);

        get_piece_coordinates(move_coords, &move_row_index, &move_column_index);

        validate_and_execute_move(&board[row_index][column_index], board, move_column_index, move_row_index, &move_is_correct);

        if (player.color == WHITE && !king_is_alive(board)) {
            printf("\t[ %c ]\tKilled opponent's king\n", player.color);
            display_winner(WHITE);
            *game_is_active = FALSE;
        } else if (player.color == BLACK && !king_is_alive(board)) {
            printf("\t[ %c ]\tKilled opponent's king\n", player.color);
            display_winner(BLACK);
            *game_is_active = FALSE;
        }
    } while (move_is_correct == FALSE);
}
