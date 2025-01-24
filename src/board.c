#include <stdio.h>
#include <stdlib.h> // abs()
#include "board.h"

/* TODO: DEINE THOSE FIGURES
ChessPiece w_king    = {KING,    WHITE, 'e', 8};
ChessPiece w_queen   = {QUEEN,   WHITE, 'd', 8};
ChessPiece w_rook1   = {ROOK,    WHITE, 'a', 8};
ChessPiece w_rook2   = {ROOK,    WHITE, 'h', 8};
ChessPiece w_knight1 = {KNIGHT,  WHITE, 'b', 8};
ChessPiece w_knight2 = {KNIGHT,  WHITE, 'g', 8};
ChessPiece w_bishop1 = {ROOK,    WHITE, 'c', 8};
ChessPiece w_bishop2 = {ROOK,    WHITE, 'f', 8};

ChessPiece b_king    = {KING,    BLACK, 'e', 1};
ChessPiece b_queen   = {QUEEN,   BLACK, 'd', 1};
ChessPiece b_rook1   = {ROOK,    BLACK, 'a', 1};
ChessPiece b_rook2   = {ROOK,    BLACK, 'h', 1};
ChessPiece b_knight1 = {KNIGHT,  BLACK, 'b', 1};
ChessPiece b_knight2 = {KNIGHT,  BLACK, 'g', 1};
ChessPiece b_bishop1 = {ROOK,    BLACK, 'c', 1};
ChessPiece b_bishop2 = {ROOK,    BLACK, 'f', 1};
*/

void print_chess_piece(ChessPiece chess_piece) {
    printf("--- chess piece ---\n");
    printf("\tpiece:\t%c\n", chess_piece.piece);
    printf("\tcolor:\t%c\n", chess_piece.color);
    printf("\tx:\t\t%c\n", chess_piece.x);
    printf("\ty:\t\t%d\n", chess_piece.y);
}

void initialize_board(ChessPiece board[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            board[i][j].piece = EMPTY;
            board[i][j].color = EMPTY;
            board[i][j].x = 'a' + j;
            board[i][j].y = ROWS - i;
            board[i][j].can_make_this_move = NULL;
            board[i][j].make_this_move = NULL;
        }
    }

    // white pawns
    for (int j = 0; j < COLUMNS; j++) {
        board[6][j].piece = PAWN;
        board[6][j].color = WHITE;
        board[6][j].can_make_this_move = (void *)pawn_can_make_this_move;
        board[6][j].make_this_move = (void *)pawn_move;
    }

    // black pawns
    for (int j = 0; j < COLUMNS; j++) {
        board[1][j].piece = PAWN;
        board[1][j].color = BLACK;
        board[1][j].can_make_this_move = (void *)pawn_can_make_this_move;
        board[1][j].make_this_move = (void *)pawn_move;
    }
}

void print_board(ChessPiece board[ROWS][COLUMNS]) {
    printf("\tBLACK\n");
    printf("   a b c d e f g h\n");  // Print column letters

    for (int i = 0; i < ROWS; i++) {
        printf(" %d|", ROWS - i);  // Print row number
        for (int j = 0; j < COLUMNS; j++) {
            printf("%c|", board[i][j].piece);  // Print the board with vertical separators
        }
        printf("%d\n", ROWS - i);  // Print row number again on the right
    }

    printf("   a b c d e f g h\n");  // Print column letters again
    printf("\tWHITE\n");
}

int pawn_can_make_this_move(ChessPiece *self, ChessPiece board[ROWS][COLUMNS], char toX, int toY) {
    int startY  = ROWS - self->y;
    int startX  = self->x - 'a';
    int endY    = ROWS - toY;
    int endX    = toX - 'a';
    int direction; // Moving direction: white goes up (-1), black goes down (+1)
    
    if(self->color == WHITE){
        direction = -1;
    }
    else{
        direction = 1;
    }

    // Move one step forward
    if (endX == startX && endY == startY + direction && board[endY][endX].piece == EMPTY) {
        return 1;
    }

    // Move 2 steps forward if that's his first move
    if ((startY == 6 && self->color == WHITE) || (startY == 1 && self->color == BLACK)) {
        if (endX == startX && endY == startY + 2 * direction && 
            board[startY + direction][startX].piece == EMPTY && board[endY][endX].piece == EMPTY) {
            return 1;
        }
    }

    // Hit
    if ((endX == startX + 1 || endX == startX - 1) && endY == startY + direction && 
        board[endY][endX].piece != EMPTY && board[endY][endX].color != self->color) {
        return 1;
    }

    return 0; // Can't do that move
}

void pawn_move(ChessPiece *self, ChessPiece board[ROWS][COLUMNS], char toX, int toY) {
    int startY  = ROWS - self->y;
    int startX  = self->x - 'a';
    int endY    = ROWS - toY;
    int endX    = toX - 'a';

    // Move pawn
    board[endY][endX] = *self;
    board[startY][startX].piece = EMPTY;
    board[startY][startX].color = EMPTY;
    board[startY][startX].can_make_this_move = NULL;
    board[startY][startX].make_this_move = NULL;

    // update pawn position
    board[endY][endX].x = toX;
    board[endY][endX].y = toY;
}
