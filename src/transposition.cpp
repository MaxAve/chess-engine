#include "transposition.h"

uint64_t TPosTable::zobristKeys[BOARD_SIZE][NUM_PIECES + 1]; // NUM_PIECES + 1 because we also need to hash the en pessant bitboard
uint64_t TPosTable::zobristPositionFlagsKeys[8]; // 8 zobrist keys for every bit in Bitboard::flags

void TPosTable::InitZobristKeys()
{
    srand(time(NULL));
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < (NUM_PIECES + 1); j++)
        {
            TPosTable::zobristKeys[i][j] = (uint64_t)rand() << 32 | rand(); // 64-bit random number
        }
    }
    for (int i = 0; i < 8; i++)
    {
        TPosTable::zobristPositionFlagsKeys[i] = (uint64_t)rand() << 32 | rand(); // 64-bit random number
    }
}

uint64_t TPosTable::ZobristHash(const Bitboard &board)
{
    uint64_t hash = 0ULL;
    for (int i = 0; i < NUM_PIECES; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board.bitboards[i] & (1ULL << j))
            {
                hash ^= TPosTable::zobristKeys[j][i];
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board.enPessant & (1ULL << i))
        {
            hash ^= TPosTable::zobristKeys[i][NUM_PIECES + 1];
        }
    }
    for (int i = 0; i < 8; i++)
    {
        if (board.flags & ((uint8_t)1 << i))
        {
            hash ^= TPosTable::zobristPositionFlagsKeys[i];
        }
    }
    return hash;
}