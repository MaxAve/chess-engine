#include "bitboard.h"

void InitBitboard(Bitboard *bitboard, uint8_t boardType)
{
    switch (boardType)
    {
        case BOARD_SETUP_EMPTY:
            for (int i = 0; i < NUM_PIECES; i++)
                bitboard->bitboards[i] = 0x0;
            break;
            
        case BOARD_SETUP_CLASSIC:
            bitboard->bitboards[PW] = 0xff00ULL;
            bitboard->bitboards[NW] = 0x42ULL;
            bitboard->bitboards[BW] = 0x24ULL;
            bitboard->bitboards[RW] = 0x81ULL;
            bitboard->bitboards[QW] = 0x10ULL;
            bitboard->bitboards[KW] = 0x8ULL;
            bitboard->bitboards[PB] = 0x00ff000000000000;
            bitboard->bitboards[NB] = 0x4200000000000000;
            bitboard->bitboards[BB] = 0x2400000000000000;
            bitboard->bitboards[RB] = 0x8100000000000000;
            bitboard->bitboards[QB] = 0x1000000000000000;
            bitboard->bitboards[KB] = 0x0800000000000000;
            break;
    }
    bitboard->enPessant = 0x0ULL;
    bitboard->flags = 0x1;
}