#include "pieces.h"

uint64_t GetLegalMoves(const Bitboard *bitboard, uint8_t pieceType, uint8_t bit)
{
    const uint64_t whitePieces = GetCombinedBitboardWhite(bitboard);
    const uint64_t blackPieces = GetCombinedBitboardBlack(bitboard);
    const uint64_t allPieces = whitePieces | blackPieces;
    uint64_t legalMoves = 0ULL;

    switch(pieceType)
    {
        /* White pawn */
        case PW:
            /* Capture */
            legalMoves |= ((1ULL << (bit + UP_LEFT)) & RIGHT_EXCLUDE);
            legalMoves |= ((1ULL << (bit + UP_RIGHT)) & LEFT_EXCLUDE);
            legalMoves &= blackPieces;

            /* Advance */
            legalMoves |= ((1ULL << (bit + UP)) & ~allPieces);
            if(((1ULL << bit) & 0xff00ULL) && !(allPieces & (1ULL << (bit + UP))))
                legalMoves |= ((1ULL << (bit + UP * 2)) & ~allPieces); 
            break;

        /* Black pawn */
        case PB:
            /* Capture */
            legalMoves |= ((1ULL << (bit + DOWN_LEFT)) & RIGHT_EXCLUDE);
            legalMoves |= ((1ULL << (bit + DOWN_RIGHT)) & LEFT_EXCLUDE);
            legalMoves &= whitePieces;

            /* Advance */
            legalMoves |= ((1ULL << (bit + DOWN)) & ~allPieces);
            if(((1ULL << bit) & 0xff000000000000ULL) && !(allPieces & (1ULL << (bit + DOWN))))
                legalMoves |= ((1ULL << (bit + DOWN * 2)) & ~allPieces); 
            break;
    }

    return legalMoves;
}