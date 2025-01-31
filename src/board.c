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

void place_piece(ChessPiece board[ROWS][COLUMNS], char piece, char color, int row, int col, void *can_move_function, void *move_function) {
    board[row][col].piece = piece;
    board[row][col].color = color;
    board[row][col].can_make_this_move = can_move_function;
    board[row][col].make_this_move = move_function;
}

int is_empty(ChessPiece *piece) {
    if(piece->piece == EMPTY){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int is_opponent_piece(ChessPiece *self, ChessPiece *target) {
    if(is_empty == FALSE && self->color != target->color){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

void initialize_bishops(ChessPiece board[ROWS][COLUMNS]) {
    place_piece(board, BISHOP, BLACK, 0, 2, bishop_can_make_this_move, piece_move);
    place_piece(board, BISHOP, BLACK, 0, 5, bishop_can_make_this_move, piece_move);
    place_piece(board, BISHOP, WHITE, 7, 2, bishop_can_make_this_move, piece_move);
    place_piece(board, BISHOP, WHITE, 7, 5, bishop_can_make_this_move, piece_move);
}

void initialize_knights(ChessPiece board[ROWS][COLUMNS]) {
    place_piece(board, KNIGHT, BLACK, 0, 1, knight_can_make_this_move, piece_move);
    place_piece(board, KNIGHT, BLACK, 0, 6, knight_can_make_this_move, piece_move);
    place_piece(board, KNIGHT, WHITE, 7, 1, knight_can_make_this_move, piece_move);
    place_piece(board, KNIGHT, WHITE, 7, 6, knight_can_make_this_move, piece_move);
}

void initialize_rooks(ChessPiece board[ROWS][COLUMNS]) {
    place_piece(board, ROOK, BLACK, 0, 0, rook_can_make_this_move, piece_move);
    place_piece(board, ROOK, BLACK, 0, 7, rook_can_make_this_move, piece_move);
    place_piece(board, ROOK, WHITE, 7, 0, rook_can_make_this_move, piece_move);
    place_piece(board, ROOK, WHITE, 7, 7, rook_can_make_this_move, piece_move);
}

void initialize_queens(ChessPiece board[ROWS][COLUMNS]) {
    place_piece(board, QUEEN, BLACK, 0, 3, queen_can_make_this_move, piece_move);
    place_piece(board, QUEEN, WHITE, 7, 3, queen_can_make_this_move, piece_move);
}

void initialize_kings(ChessPiece board[ROWS][COLUMNS]) {
    place_piece(board, KING, BLACK, 0, 4, king_can_make_this_move, piece_move);
    place_piece(board, KING, WHITE, 7, 4, king_can_make_this_move, piece_move);
}

void initialize_pawns(ChessPiece board[ROWS][COLUMNS]) {
    for (int j = 0; j < COLUMNS; j++) {
        place_piece(board, PAWN, WHITE, 6, j, pawn_can_make_this_move, piece_move);
        place_piece(board, PAWN, BLACK, 1, j, pawn_can_make_this_move, piece_move);
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

    if (king_counter == BOTH_KINGS) {
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
