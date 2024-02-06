#include "eval.h"

int Eval::PieceSquareTablesEval(const Bitboard &bitboard)
{
    int eval = 0;
    for(uint8_t i = 0; i < 6; ++i)
        for(uint8_t j = 0; j < 64; ++j)
            if(bitboard.bitboards[i] & (1ULL << j))
                eval -= Eval::pieceSquareTables[i][j];
    for(uint8_t i = 6; i < 12; ++i)
        for(uint8_t j = 0; j < 64; ++j)
            if(bitboard.bitboards[i] & (1ULL << j))
                eval += Eval::pieceSquareTables[i-6][63-j];
    return eval;
}

bool Eval::IsWhiteCheckmated(const Bitboard &bitboard)
{
    if(bitboard.bitboards[KW] == 0ULL || (bitboard.bitboards[KW] & GetLegalMovesBlack(bitboard) && !GetLegalMoves(bitboard, KW, (uint8_t)std::log2(bitboard.bitboards[KW]))))
        return true;
    return false;
}

bool Eval::IsBlackCheckmated(const Bitboard &bitboard)
{
    if(bitboard.bitboards[KB] == 0ULL || (bitboard.bitboards[KB] & GetLegalMovesWhite(bitboard) && !GetLegalMoves(bitboard, KB, (uint8_t)std::log2(bitboard.bitboards[KB]))))
        return true;
    return false;
}

bool Eval::IsDraw(const Bitboard &bitboard)
{
    // Stalemate
    if(!GetLegalMovesWhite(bitboard) || !GetLegalMovesBlack(bitboard))
    {
        return true;
    }
    // King vs King
    const uint64_t whitePieces = GetCombinedBitboardWhite(bitboard);
    const uint64_t blackPieces = GetCombinedBitboardBlack(bitboard);
    if((whitePieces & (whitePieces - 1)) == 0 && (blackPieces & (blackPieces - 1)) == 0)
    {
        return true;
    }
    return false;
}