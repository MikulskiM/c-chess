#include <stdio.h>
#include <stdlib.h> // abs()
#include "board.h"

void print_chess_piece(ChessPiece chess_piece) {
    printf("--- chess piece ---\n");
    printf("\tpiece:\t%c\n", chess_piece.piece);
    printf("\tcolor:\t%c\n", chess_piece.color);
    printf("\tx:\t\t%c\n", chess_piece.x);
    printf("\ty:\t\t%d\n", chess_piece.y);
}

void initialize_bishops(ChessPiece board[ROWS][COLUMNS]) {
    board[0][2].piece = BISHOP;
    board[0][2].color = BLACK;
    board[0][2].can_make_this_move = bishop_can_make_this_move;
    board[0][2].make_this_move = piece_move;

    board[0][5].piece = BISHOP;
    board[0][5].color = BLACK;
    board[0][5].can_make_this_move = bishop_can_make_this_move;
    board[0][5].make_this_move = piece_move;

    board[7][2].piece = BISHOP;
    board[7][2].color = WHITE;
    board[7][2].can_make_this_move = bishop_can_make_this_move;
    board[7][2].make_this_move = piece_move;

    board[7][5].piece = BISHOP;
    board[7][5].color = WHITE;
    board[7][5].can_make_this_move = bishop_can_make_this_move;
    board[7][5].make_this_move = piece_move;
}

void initialize_knights(ChessPiece board[ROWS][COLUMNS]) {
    board[0][1].piece = KNIGHT;
    board[0][1].color = BLACK;
    board[0][1].can_make_this_move = knight_can_make_this_move;
    board[0][1].make_this_move = piece_move;

    board[0][6].piece = KNIGHT;
    board[0][6].color = BLACK;
    board[0][6].can_make_this_move = knight_can_make_this_move;
    board[0][6].make_this_move = piece_move;

    board[7][1].piece = KNIGHT;
    board[7][1].color = WHITE;
    board[7][1].can_make_this_move = knight_can_make_this_move;
    board[7][1].make_this_move = piece_move;

    board[7][6].piece = KNIGHT;
    board[7][6].color = WHITE;
    board[7][6].can_make_this_move = knight_can_make_this_move;
    board[7][6].make_this_move = piece_move;
}

void initialize_rooks(ChessPiece board[ROWS][COLUMNS]) {
    board[0][0].piece = ROOK;
    board[0][0].color = BLACK;
    board[0][0].can_make_this_move = rook_can_make_this_move;
    board[0][0].make_this_move = piece_move;

    board[0][7].piece = ROOK;
    board[0][7].color = BLACK;
    board[0][7].can_make_this_move = rook_can_make_this_move;
    board[0][7].make_this_move = piece_move;

    board[7][0].piece = ROOK;
    board[7][0].color = WHITE;
    board[7][0].can_make_this_move = rook_can_make_this_move;
    board[7][0].make_this_move = piece_move;

    board[7][7].piece = ROOK;
    board[7][7].color = WHITE;
    board[7][7].can_make_this_move = rook_can_make_this_move;
    board[7][7].make_this_move = piece_move;
}

void initialize_queens(ChessPiece board[ROWS][COLUMNS]) {
    board[0][3].piece = QUEEN;
    board[0][3].color = BLACK;
    board[0][3].can_make_this_move = queen_can_make_this_move;
    board[0][3].make_this_move = piece_move;

    board[7][3].piece = QUEEN;
    board[7][3].color = WHITE;
    board[7][3].can_make_this_move = queen_can_make_this_move;
    board[7][3].make_this_move = piece_move;
}

void initialize_kings(ChessPiece board[ROWS][COLUMNS]) {
    board[0][4].piece = KING;
    board[0][4].color = BLACK;
    board[0][4].can_make_this_move = king_can_make_this_move;
    board[0][4].make_this_move = piece_move;

    board[7][4].piece = KING;
    board[7][4].color = WHITE;
    board[7][4].can_make_this_move = king_can_make_this_move;
    board[7][4].make_this_move = piece_move;
}

void initialize_pawns(ChessPiece board[ROWS][COLUMNS]) {
    // white pawns
    for (int j = 0; j < COLUMNS; j++) {
        board[6][j].piece = PAWN;
        board[6][j].color = WHITE;
        board[6][j].can_make_this_move = pawn_can_make_this_move;
        board[6][j].make_this_move = piece_move;
    }

    // black pawns
    for (int j = 0; j < COLUMNS; j++) {
        board[1][j].piece = PAWN;
        board[1][j].color = BLACK;
        board[1][j].can_make_this_move = pawn_can_make_this_move;
        board[1][j].make_this_move = piece_move;
    }
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

    initialize_kings(board);
    initialize_queens(board);
    initialize_rooks(board);
    initialize_knights(board);
    initialize_bishops(board);
    initialize_pawns(board);
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

int king_is_alive(ChessPiece board[ROWS][COLUMNS]) {
    int king_counter = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j].piece == KING) {
                king_counter++;
            }
        }
    }

    if (king_counter == 2) {
        return TRUE;
    }
    else {
        return FALSE;
    }
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
        return TRUE;
    }

    // Move 2 steps forward if that's his first move
    if ((startY == 6 && self->color == WHITE) || (startY == 1 && self->color == BLACK)) {
        if (endX == startX && endY == startY + 2 * direction && 
            board[startY + direction][startX].piece == EMPTY && board[endY][endX].piece == EMPTY) {
            return TRUE;
        }
    }

    // Hit
    if ((endX == startX + 1 || endX == startX - 1) && endY == startY + direction && 
        board[endY][endX].piece != EMPTY && board[endY][endX].color != self->color) {
        return TRUE;
    }

    return FALSE; // Can't do that move
}

int king_can_make_this_move(ChessPiece *self, ChessPiece board[ROWS][COLUMNS], char toX, int toY) {
    int startY  = ROWS - self->y;
    int startX  = self->x - 'a';
    int endY    = ROWS - toY;
    int endX    = toX - 'a';

    // Move one step in whatever direction
    if (endX - startX >= -1 && endX - startX <= 1 &&
        endY - startY >= -1 && endY - startY <= 1 &&
        board[endY][endX].piece == EMPTY) {
        return TRUE;
    }

    // Hit
    if (endX - startX >= -1 && endX - startX <= 1 &&
        endY - startY >= -1 && endY - startY <= 1 && 
        board[endY][endX].piece != EMPTY && board[endY][endX].color != self->color) {
        return TRUE;
    }

    return FALSE; // Can't do that move
}

int rook_can_make_this_move(ChessPiece *self, ChessPiece board[ROWS][COLUMNS], char toX, int toY) {
    int startY = ROWS - self->y;
    int startX = self->x - 'a';
    int endY = ROWS - toY;
    int endX = toX - 'a';

    if (startX == endX || startY == endY) {
        // check if the path is empty
        if (startX == endX) { // vertical
            int step = (endY > startY) ? 1 : -1;
            for (int y = startY + step; y != endY; y += step) {
                if (board[y][startX].piece != EMPTY) return FALSE;
            }
        } else { // horizontal
            int step = (endX > startX) ? 1 : -1;
            for (int x = startX + step; x != endX; x += step) {
                if (board[startY][x].piece != EMPTY) return FALSE;
            }
        }
        // check if empty or an opponent
        if (board[endY][endX].piece == EMPTY || board[endY][endX].color != self->color) {
            return TRUE;
        }
    }

    return FALSE; // Can't do that move
}

int queen_can_make_this_move(ChessPiece *self, ChessPiece board[ROWS][COLUMNS], char toX, int toY) {
    // queen can move like bishop or a rook
    if (rook_can_make_this_move(self, board, toX, toY) || bishop_can_make_this_move(self, board, toX, toY)) {
        return TRUE;
    }
    return FALSE;
}

int bishop_can_make_this_move(ChessPiece *self, ChessPiece board[ROWS][COLUMNS], char toX, int toY) {
    int startY = ROWS - self->y;
    int startX = self->x - 'a';
    int endY = ROWS - toY;
    int endX = toX - 'a';

    // diagonal move
    if (abs(endX - startX) == abs(endY - startY)) {
        int stepX = (endX > startX) ? 1 : -1;
        int stepY = (endY > startY) ? 1 : -1;

        // check if the path is empty
        int x = startX + stepX;
        int y = startY + stepY;
        while (x != endX && y != endY) {
            if (board[y][x].piece != EMPTY) return FALSE;
            x += stepX;
            y += stepY;
        }

        // check if empty or an opponent
        if (board[endY][endX].piece == EMPTY || board[endY][endX].color != self->color) {
            return TRUE;
        }
    }

    return FALSE; // Can't do that move
}

int knight_can_make_this_move(ChessPiece *self, ChessPiece board[ROWS][COLUMNS], char toX, int toY) {
    int startY = ROWS - self->y;
    int startX = self->x - 'a';
    int endY = ROWS - toY;
    int endX = toX - 'a';

    // moves like letter "L", doesn't metter the direction
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        // check if empty or an opponent
        if (board[endY][endX].piece == EMPTY || board[endY][endX].color != self->color) {
            return TRUE;
        }
    }

    return FALSE; // Can't do that move
}

void piece_move(ChessPiece *self, ChessPiece board[ROWS][COLUMNS], char toX, int toY) {
    int startY  = ROWS - self->y;
    int startX  = self->x - 'a';
    int endY    = ROWS - toY;
    int endX    = toX - 'a';

    // Move piece
    board[endY][endX] = *self;
    board[startY][startX].piece = EMPTY;
    board[startY][startX].color = EMPTY;
    board[startY][startX].can_make_this_move = NULL;
    board[startY][startX].make_this_move = NULL;

    // update piece position
    board[endY][endX].x = toX;
    board[endY][endX].y = toY;
}
