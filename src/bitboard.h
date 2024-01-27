#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include "types.h"

#define UP 8
#define DOWN -8
#define LEFT 1
#define RIGHT -1
#define UP_LEFT 9
#define UP_RIGHT 7
#define DOWN_LEFT -7
#define DOWN_RIGHT -9

#define LEFT_EXCLUDE 0x7f7f7f7f7f7f7f7fULL
#define RIGHT_EXCLUDE 0xfefefefefefefefeULL

#define BOARD_SETUP_EMPTY 0
#define BOARD_SETUP_CLASSIC 1

typedef struct
{
    uint64_t bitboards[12];
    uint64_t enPessant;
    uint8_t flags;
} Bitboard;

void InitBitboard(Bitboard *bitboard, uint8_t boardType);
uint64_t GetCombinedBitboard(const Bitboard *bitboard);
uint64_t GetCombinedBitboardWhite(const Bitboard *bitboard);
uint64_t GetCombinedBitboardBlack(const Bitboard *bitboard);
uint8_t GetPieceType(Bitboard *bitboard, uint8_t bit);

#endif