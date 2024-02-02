#ifndef TRANSPOSITION_H
#define TRANSPOSITION_H

#include <iostream>
#include <unordered_map>
#include "bitboard.h"
#include "types.h"

namespace TranspositionTable
{
//extern std::unordered_map<uint64_t, ...> table;

extern uint64_t zobristKeys[BOARD_SIZE][NUM_PIECES + 1]; // NUM_PIECES + 1 because we also need to hash the en pessant bitboard
extern uint64_t zobristPositionFlagsKeys[8]; // 8 zobrist keys for every bit in Bitboard::flags

void InitZobristKeys();
uint64_t ZobristHash(const Bitboard &board);
}

#endif