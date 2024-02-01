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

        /* White knight */
        case NW:
            legalMoves |= ((1ULL << (bit + LEFT*2  + UP    )) & ~(FILE | (FILE << 1) | RANK));
            legalMoves |= ((1ULL << (bit + LEFT*2  + DOWN  )) & ~(FILE | (FILE << 1) | (RANK << 56)));
            legalMoves |= ((1ULL << (bit + LEFT    + UP*2  )) & ~(FILE | RANK | (RANK << 8)));
            legalMoves |= ((1ULL << (bit + LEFT    + DOWN*2)) & ~(FILE | (RANK << 48) | (RANK << 56)));
            legalMoves |= ((1ULL << (bit + RIGHT   + DOWN*2)) & ~((FILE << 7) | (RANK << 48) | (RANK << 56)));
            legalMoves |= ((1ULL << (bit + RIGHT   + UP*2  )) & ~((FILE << 7) | RANK | (RANK << 8)));
            legalMoves |= ((1ULL << (bit + RIGHT*2 + UP    )) & ~((FILE << 6) | (FILE << 7) | RANK));
            legalMoves |= ((1ULL << (bit + RIGHT*2 + DOWN  )) & ~((FILE << 6) | (FILE << 7) | (RANK << 56)));
            legalMoves &= ~whitePieces;
            // have fun with that
            break;

        /* Black knight */
        case NB:
            legalMoves |= ((1ULL << (bit + LEFT*2  + UP    )) & ~(FILE | (FILE << 1) | RANK));
            legalMoves |= ((1ULL << (bit + LEFT*2  + DOWN  )) & ~(FILE | (FILE << 1) | (RANK << 56)));
            legalMoves |= ((1ULL << (bit + LEFT    + UP*2  )) & ~(FILE | RANK | (RANK << 8)));
            legalMoves |= ((1ULL << (bit + LEFT    + DOWN*2)) & ~(FILE | (RANK << 48) | (RANK << 56)));
            legalMoves |= ((1ULL << (bit + RIGHT   + DOWN*2)) & ~((FILE << 7) | (RANK << 48) | (RANK << 56)));
            legalMoves |= ((1ULL << (bit + RIGHT   + UP*2  )) & ~((FILE << 7) | RANK | (RANK << 8)));
            legalMoves |= ((1ULL << (bit + RIGHT*2 + UP    )) & ~((FILE << 6) | (FILE << 7) | RANK));
            legalMoves |= ((1ULL << (bit + RIGHT*2 + DOWN  )) & ~((FILE << 6) | (FILE << 7) | (RANK << 56)));
            legalMoves &= ~blackPieces;
            break;
        
        /* White bishop */
        case BW:
            if(bit % 8 != 0 && bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP_RIGHT*i));
                    if((1ULL << (bit + UP_RIGHT*i)) & allPieces || (bit + UP_RIGHT*i) % 8 == 0 || (bit + UP_RIGHT*i) / 8 > 6)
                        break;
                }
            }
            if(bit % 8 != 0 && bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN_RIGHT*i));
                    if((1ULL << (bit + DOWN_RIGHT*i)) & allPieces || (bit + DOWN_RIGHT*i) % 8 == 0 || (bit + DOWN_RIGHT*i) / 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0 && bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN_LEFT*i));
                    if((1ULL << (bit + DOWN_LEFT*i)) & allPieces || (bit + DOWN_LEFT*i + 1) % 8 == 0 || (bit + DOWN_LEFT*i) / 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0 && bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP_LEFT*i));
                    if((1ULL << (bit + UP_LEFT*i)) & allPieces || (bit + UP_LEFT*i + 1) % 8 == 0 || (bit + UP_RIGHT*i) / 8 > 6)
                        break;
                }
            }
            legalMoves &= ~whitePieces;
            break;

        /* Black bishop */
        case BB:
            if(bit % 8 != 0 && bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP_RIGHT*i));
                    if((1ULL << (bit + UP_RIGHT*i)) & allPieces || (bit + UP_RIGHT*i) % 8 == 0 || (bit + UP_RIGHT*i) / 8 > 6)
                        break;
                }
            }
            if(bit % 8 != 0 && bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN_RIGHT*i));
                    if((1ULL << (bit + DOWN_RIGHT*i)) & allPieces || (bit + DOWN_RIGHT*i) % 8 == 0 || (bit + DOWN_RIGHT*i) / 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0 && bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN_LEFT*i));
                    if((1ULL << (bit + DOWN_LEFT*i)) & allPieces || (bit + DOWN_LEFT*i + 1) % 8 == 0 || (bit + DOWN_LEFT*i) / 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0 && bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP_LEFT*i));
                    if((1ULL << (bit + UP_LEFT*i)) & allPieces || (bit + UP_LEFT*i + 1) % 8 == 0 || (bit + UP_RIGHT*i) / 8 > 6)
                        break;
                }
            }
            legalMoves &= ~blackPieces;
            break;

        /* White rook */
        case RW:
            if(bit % 8 != 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + RIGHT*i));
                    if((1ULL << (bit + RIGHT*i)) & allPieces || (bit + RIGHT*i) % 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + LEFT*i));
                    if((1ULL << (bit + LEFT*i)) & allPieces || (bit + LEFT*i + 1) % 8 == 0)
                        break;
                }
            }
            if(bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP*i));
                    if((1ULL << (bit + UP*i)) & allPieces || (bit + UP*i) / 8 >= 7)
                        break;
                }
            }
            if(bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN*i));
                    if((1ULL << (bit + DOWN*i)) & allPieces || (bit + DOWN*i) / 8 == 0)
                        break;
                }
            }
            legalMoves &= ~whitePieces;
            break;

        /* Black rook */
        case RB:
            if(bit % 8 != 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + RIGHT*i));
                    if((1ULL << (bit + RIGHT*i)) & allPieces || (bit + RIGHT*i) % 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + LEFT*i));
                    if((1ULL << (bit + LEFT*i)) & allPieces || (bit + LEFT*i + 1) % 8 == 0)
                        break;
                }
            }
            if(bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP*i));
                    if((1ULL << (bit + UP*i)) & allPieces || (bit + UP*i) / 8 >= 7)
                        break;
                }
            }
            if(bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN*i));
                    if((1ULL << (bit + DOWN*i)) & allPieces || (bit + DOWN*i) / 8 == 0)
                        break;
                }
            }
            legalMoves &= ~blackPieces;
            break;

        /* White queen */
        case QW:
            if(bit % 8 != 0 && bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP_RIGHT*i));
                    if((1ULL << (bit + UP_RIGHT*i)) & allPieces || (bit + UP_RIGHT*i) % 8 == 0 || (bit + UP_RIGHT*i) / 8 > 6)
                        break;
                }
            }
            if(bit % 8 != 0 && bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN_RIGHT*i));
                    if((1ULL << (bit + DOWN_RIGHT*i)) & allPieces || (bit + DOWN_RIGHT*i) % 8 == 0 || (bit + DOWN_RIGHT*i) / 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0 && bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN_LEFT*i));
                    if((1ULL << (bit + DOWN_LEFT*i)) & allPieces || (bit + DOWN_LEFT*i + 1) % 8 == 0 || (bit + DOWN_LEFT*i) / 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0 && bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP_LEFT*i));
                    if((1ULL << (bit + UP_LEFT*i)) & allPieces || (bit + UP_LEFT*i + 1) % 8 == 0 || (bit + UP_RIGHT*i) / 8 > 6)
                        break;
                }
            }
            if(bit % 8 != 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + RIGHT*i));
                    if((1ULL << (bit + RIGHT*i)) & allPieces || (bit + RIGHT*i) % 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + LEFT*i));
                    if((1ULL << (bit + LEFT*i)) & allPieces || (bit + LEFT*i + 1) % 8 == 0)
                        break;
                }
            }
            if(bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP*i));
                    if((1ULL << (bit + UP*i)) & allPieces || (bit + UP*i) / 8 >= 7)
                        break;
                }
            }
            if(bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN*i));
                    if((1ULL << (bit + DOWN*i)) & allPieces || (bit + DOWN*i) / 8 == 0)
                        break;
                }
            }
            legalMoves &= ~whitePieces;
            break;

        /* Black queen */
        case QB:
            if(bit % 8 != 0 && bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP_RIGHT*i));
                    if((1ULL << (bit + UP_RIGHT*i)) & allPieces || (bit + UP_RIGHT*i) % 8 == 0 || (bit + UP_RIGHT*i) / 8 > 6)
                        break;
                }
            }
            if(bit % 8 != 0 && bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN_RIGHT*i));
                    if((1ULL << (bit + DOWN_RIGHT*i)) & allPieces || (bit + DOWN_RIGHT*i) % 8 == 0 || (bit + DOWN_RIGHT*i) / 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0 && bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN_LEFT*i));
                    if((1ULL << (bit + DOWN_LEFT*i)) & allPieces || (bit + DOWN_LEFT*i + 1) % 8 == 0 || (bit + DOWN_LEFT*i) / 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0 && bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP_LEFT*i));
                    if((1ULL << (bit + UP_LEFT*i)) & allPieces || (bit + UP_LEFT*i + 1) % 8 == 0 || (bit + UP_RIGHT*i) / 8 > 6)
                        break;
                }
            }
            if(bit % 8 != 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + RIGHT*i));
                    if((1ULL << (bit + RIGHT*i)) & allPieces || (bit + RIGHT*i) % 8 == 0)
                        break;
                }
            }
            if((bit + 1) % 8 != 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + LEFT*i));
                    if((1ULL << (bit + LEFT*i)) & allPieces || (bit + LEFT*i + 1) % 8 == 0)
                        break;
                }
            }
            if(bit / 8 < 7)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + UP*i));
                    if((1ULL << (bit + UP*i)) & allPieces || (bit + UP*i) / 8 >= 7)
                        break;
                }
            }
            if(bit / 8 > 0)
            {
                for(uint8_t i = 1; i < 8; i++)
                {
                    legalMoves |= (1ULL << (bit + DOWN*i));
                    if((1ULL << (bit + DOWN*i)) & allPieces || (bit + DOWN*i) / 8 == 0)
                        break;
                }
            }
            legalMoves &= ~blackPieces;
            break;
    }

    return legalMoves;
}