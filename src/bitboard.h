#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include "types.h"

#define BOARD_SETUP_EMPTY 0
#define BOARD_SETUP_CLASSIC 1

typedef struct
{
    uint64_t bitboards[12];
    uint64_t enPessant;
    uint8_t flags;
} Bitboard;

void InitBitboard(Bitboard *bitboard, uint8_t boardType);
uint64_t GetCombinedBitboard(Bitboard *bitboard);
uint8_t GetPieceType(Bitboard *bitboard, uint8_t bit);

#endif