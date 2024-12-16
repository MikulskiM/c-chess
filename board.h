#ifndef BOARD_H
#define BOARD_H

#define ROW_LENGTH 8

#define KING    'K'
#define QUEEN   'Q'
#define ROOK    'R'
#define KNIGHT  'N'
#define PAWN    'P'

#define WHITE   'W'
#define BLACK   'B'

typedef struct ChessPiece {
    char piece;
    char color;
    char x;     // Column position (a-h)
    int  y;     // Row position (1-8)
} ChessPiece;

void initialize_board(char board[ROW_LENGTH][ROW_LENGTH]);
void print_board(char board[ROW_LENGTH][ROW_LENGTH]);

#endif // BOARD_H