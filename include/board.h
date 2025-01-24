#ifndef BOARD_H
#define BOARD_H

#define ROWS    8
#define COLUMNS 8

#define TRUE    1
#define FALSE   0

#define KING    'K'
#define QUEEN   'Q'
#define ROOK    'R'
#define KNIGHT  'N'
#define PAWN    'P'
#define EMPTY   '_'

#define WHITE   'W'
#define BLACK   'B'

typedef struct ChessPiece ChessPiece;

struct ChessPiece {
    char piece;
    char color;
    char x;     // Column position (a-h)
    int  y;     // Row position (1-8)
    void *can_make_this_move;
    void *make_this_move;
};

void initialize_board(ChessPiece board[ROWS][COLUMNS]);
void print_board(ChessPiece board[ROWS][COLUMNS]);
void print_chess_piece(ChessPiece chess_piece);

int pawn_can_make_this_move(ChessPiece *self, ChessPiece board[ROWS][COLUMNS], char toX, int toY);
void pawn_move(ChessPiece *self, ChessPiece board[ROWS][COLUMNS], char toX, int toY);

#endif // BOARD_H