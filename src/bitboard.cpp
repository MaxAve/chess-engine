#include "bitboard.h"

void InitBitboard(Bitboard &bitboard, uint8_t boardType)
{
    switch (boardType)
    {
        case BOARD_SETUP_EMPTY:
            for (int i = 0; i < NUM_PIECES; i++)
                bitboard.bitboards[i] = 0x0;
            break;
            
        case BOARD_SETUP_CLASSIC:
            bitboard.bitboards[PB] = 0xff000000000000;
            bitboard.bitboards[NB] = 0x4200000000000000;
            bitboard.bitboards[BB] = 0x2400000000000000;
            bitboard.bitboards[RB] = 0x8100000000000000;
            bitboard.bitboards[QB] = 0x1000000000000000;
            bitboard.bitboards[KB] = 0x800000000000000;
            bitboard.bitboards[PW] = 0xff00ULL;
            bitboard.bitboards[NW] = 0x42ULL;
            bitboard.bitboards[BW] = 0x24ULL;
            bitboard.bitboards[RW] = 0x81ULL;
            bitboard.bitboards[QW] = 0x10ULL;
            bitboard.bitboards[KW] = 0x8ULL;
            break;
    }
    bitboard.enPessant = 0x0ULL;
    bitboard.flags = 0x1f;
}

uint64_t GetCombinedBitboard(const Bitboard &bitboard)
{
    return bitboard.bitboards[0] | bitboard.bitboards[1] | bitboard.bitboards[2] | bitboard.bitboards[3] | bitboard.bitboards[4] | bitboard.bitboards[5] | bitboard.bitboards[6] | bitboard.bitboards[7] | bitboard.bitboards[8] | bitboard.bitboards[9] | bitboard.bitboards[10] | bitboard.bitboards[11];
}

uint64_t GetCombinedBitboardWhite(const Bitboard &bitboard)
{
    return bitboard.bitboards[6] | bitboard.bitboards[7] | bitboard.bitboards[8] | bitboard.bitboards[9] | bitboard.bitboards[10] | bitboard.bitboards[11];
}

uint64_t GetCombinedBitboardBlack(const Bitboard &bitboard)
{
    return bitboard.bitboards[0] | bitboard.bitboards[1] | bitboard.bitboards[2] | bitboard.bitboards[3] | bitboard.bitboards[4] | bitboard.bitboards[5];
}

uint8_t GetPieceType(Bitboard &bitboard, uint8_t bit)
{
    for(uint8_t i = 0; i < 12; ++i)
        if(bitboard.bitboards[i] & (1ULL << bit))
            return i;
    return NO_PIECE;
}

void PutPiece(Bitboard &bitboard, uint8_t piece, uint8_t x, uint8_t y)
{
    bitboard.bitboards[piece] |= (1ULL << (63 - (x + y * BOARD_WIDTH)));
}