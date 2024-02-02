#include "eval.h"

int Eval::PieceSquareTablesEval(const Bitboard *bitboard)
{
    int eval = 0;
    for(uint8_t i = 0; i < 6; ++i)
    {
        for(uint8_t j = 0; j < 64; ++j)
        {
            if(bitboard->bitboards[i] & (1ULL << j))
            {
                eval -= Eval::pieceSquareTables[i][j];
            }
        }
    }
    for(uint8_t i = 6; i < 12; ++i)
    {
        for(uint8_t j = 0; j < 64; ++j)
        {
            if(bitboard->bitboards[i] & (1ULL << j))
            {
                eval += Eval::pieceSquareTables[i-6][63-j];
            }
        }
    }
    return eval;
}