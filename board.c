#include <stdio.h>
#include "board.h"

ChessPiece w_king    = {KING,    WHITE, 'e', 8};
ChessPiece w_queen   = {QUEEN,   WHITE, 'd', 8};
ChessPiece w_rook1   = {ROOK,    WHITE, 'a', 8};
ChessPiece w_rook2   = {ROOK,    WHITE, 'h', 8};
ChessPiece w_knight1 = {KNIGHT,  WHITE, 'b', 8};
ChessPiece w_knight2 = {KNIGHT,  WHITE, 'g', 8};
ChessPiece w_bishop1 = {ROOK,    WHITE, 'c', 8};
ChessPiece w_bishop2 = {ROOK,    WHITE, 'f', 8};

ChessPiece w_pawn1 = {PAWN, WHITE, 'a', 7};
ChessPiece w_pawn2 = {PAWN, WHITE, 'b', 7};
ChessPiece w_pawn3 = {PAWN, WHITE, 'c', 7};
ChessPiece w_pawn4 = {PAWN, WHITE, 'd', 7};
ChessPiece w_pawn5 = {PAWN, WHITE, 'e', 7};
ChessPiece w_pawn6 = {PAWN, WHITE, 'f', 7};
ChessPiece w_pawn7 = {PAWN, WHITE, 'g', 7};
ChessPiece w_pawn8 = {PAWN, WHITE, 'h', 7};

ChessPiece b_king    = {KING,    BLACK, 'e', 1};
ChessPiece b_queen   = {QUEEN,   BLACK, 'd', 1};
ChessPiece b_rook1   = {ROOK,    BLACK, 'a', 1};
ChessPiece b_rook2   = {ROOK,    BLACK, 'h', 1};
ChessPiece b_knight1 = {KNIGHT,  BLACK, 'b', 1};
ChessPiece b_knight2 = {KNIGHT,  BLACK, 'g', 1};
ChessPiece b_bishop1 = {ROOK,    BLACK, 'c', 1};
ChessPiece b_bishop2 = {ROOK,    BLACK, 'f', 1};

ChessPiece b_pawn1 = {PAWN, BLACK, 'a', 2};
ChessPiece b_pawn2 = {PAWN, BLACK, 'b', 2};
ChessPiece b_pawn3 = {PAWN, BLACK, 'c', 2};
ChessPiece b_pawn4 = {PAWN, BLACK, 'd', 2};
ChessPiece b_pawn5 = {PAWN, BLACK, 'e', 2};
ChessPiece b_pawn6 = {PAWN, BLACK, 'f', 2};
ChessPiece b_pawn7 = {PAWN, BLACK, 'g', 2};
ChessPiece b_pawn8 = {PAWN, BLACK, 'h', 2};

void initialize_board(char board[ROW_LENGTH][ROW_LENGTH]) {
    ChessPiece pieces[] = {
        w_rook1, w_knight1, w_bishop1, w_queen, w_king, w_bishop2, w_knight2, w_rook2,
        w_pawn1, w_pawn2, w_pawn3, w_pawn4, w_pawn5, w_pawn6, w_pawn7, w_pawn8,
        b_pawn1, b_pawn2, b_pawn3, b_pawn4, b_pawn5, b_pawn6, b_pawn7, b_pawn8,
        b_rook1, b_knight1, b_bishop1, b_queen, b_king, b_bishop2, b_knight2, b_rook2
    };

    for (int i = 0; i < ROW_LENGTH; i++) {
        board[0][i] = pieces[i].piece;
        board[1][i] = pieces[i + ROW_LENGTH].piece;
        board[6][i] = pieces[i + 2 * ROW_LENGTH].piece;
        board[7][i] = pieces[i + 3 * ROW_LENGTH].piece;
    }
}

void print_board(char board[ROW_LENGTH][ROW_LENGTH]) {
    printf("   a b c d e f g h\n");  // Print column letters

    for (int i = 0; i < ROW_LENGTH; i++) {
        printf(" %d|", i + 1);  // Print row number
        for (int j = 0; j < ROW_LENGTH; j++) {
            printf("%c|", board[i][j]);  // Print the board with vertical separators
        }
        printf("%d\n", i + 1);  // Print row number again on the right
    }

    printf("   a b c d e f g h\n");  // Print column letters again
}