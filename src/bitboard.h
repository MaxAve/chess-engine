#ifndef BITBOARD_H
#define BITBOARD_H

#include <iostream>
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

#endif