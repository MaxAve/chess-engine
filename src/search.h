#ifndef SEARCH_H
#define SEARCH_H

#include <stdint.h>
#include <limits.h>
#include <algorithm>
#include "bitboard.h"
#include "eval.h"
#include "pieces.h"

namespace Search
{
typedef struct
{
    uint8_t pieceType;
    uint64_t modified;
} BitboardModification;

typedef struct
{
    int eval;
    BitboardModification bestMove;
    BitboardModification extra; // e.g. pawn promotions, castling
} DeepEval;

void UpdateBitboard(Bitboard &bitboard, const BitboardModification &modif);

void UpdateBitboard(Bitboard &bitboard, const DeepEval &modif);

BitboardModification PromotePieces(Bitboard &bitboard, uint64_t promotionRank, uint8_t pieceType, uint8_t pieceTypePromoted);

DeepEval minimax(const Bitboard &bitboard, uint8_t depth, bool maximizing, int alpha=INT32_MIN, int beta=INT32_MAX);
} // namespace Search

#endif