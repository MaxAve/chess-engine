#include "search.h"

void Search::UpdateBitboard(Bitboard *bitboard, const Search::BitboardModification *modif)
{
    bitboard->bitboards[modif->pieceType] = modif->modified;
}

void Search::UpdateBitboard(Bitboard *bitboard, const Search::DeepEval *modif)
{
    bitboard->bitboards[modif->bestMove.pieceType] = modif->bestMove.modified;
    bitboard->bitboards[modif->extra.pieceType] = modif->extra.modified;
}

Search::BitboardModification Search::PromotePieces(Bitboard *bitboard, uint64_t promotionRank, uint8_t pieceType, uint8_t pieceTypePromoted)
{
    const uint64_t promotion = bitboard->bitboards[pieceType] & promotionRank;
    bitboard->bitboards[pieceType] &= ~promotion;
    bitboard->bitboards[pieceTypePromoted] |= promotion;
    const Search::BitboardModification ret = {pieceTypePromoted, bitboard->bitboards[pieceTypePromoted]};
    return ret;
}

Search::DeepEval Search::minimax(const Bitboard *bitboard, uint8_t depth, bool maximizing, int alpha, int beta)
{
    Search::DeepEval eval;

    if(Eval::IsWhiteCheckmated(bitboard))
    {
        eval.eval = -1000000000 - depth;
        return eval;
    }
    if(Eval::IsBlackCheckmated(bitboard)) {
        eval.eval = 1000000000 + depth;
        return eval;
    }
    if(Eval::IsDraw(bitboard)) {
        eval.eval = 0;
        return eval;
    }
    if(depth == 0) {
        eval.eval = Eval::PieceSquareTablesEval(bitboard);
        eval.eval += (maximizing ? depth : -depth);
        return eval;
    }

    if(maximizing)
    {
        /* Maximizing (white) */

        eval.eval = INT32_MIN;

        // Iterate over every white piece bitboard
        for(uint8_t i = 6; i < 12; ++i)
        {
            // Iterate over every bit in the bitboard
            for(uint8_t j = 0; j < 64; ++j)
            {
                // Check if there is a piece on that square
                if(bitboard->bitboards[i] & (1ULL << j))
                {
                    const uint64_t legalMoves = GetLegalMoves(bitboard, i, j);
                    const uint64_t orderedMoves[] = {
                        legalMoves & GetCombinedBitboardBlack(bitboard),
                        legalMoves ^ orderedMoves[0]
                    };

                    // Iterate over every move, in order from most to least aggressive
                    for(uint8_t moveOrder = 0; moveOrder < 2; ++moveOrder)
                    {
                        for(uint8_t k = 0; k < 64; ++k)
                        {
                            if(orderedMoves[moveOrder] & (1ULL << k))
                            {
                                Bitboard hypotheticalBitboard = *bitboard;

                                // Capture pieces at target square
                                for(int l = 0; l < 12; ++l)
                                    hypotheticalBitboard.bitboards[l] &= ~(1ULL << k);
                                hypotheticalBitboard.bitboards[i] &= ~(1ULL << j); // Remove piece from old position
                                hypotheticalBitboard.bitboards[i] |= (1ULL << k); // Place piece at target position
                                // TODO only promotes to queens, add other pieces
                                const Search::BitboardModification promotion = Search::PromotePieces(&hypotheticalBitboard, RANK_8, PW, QW); // Handle promotions

                                Search::DeepEval hypotheticalEval = minimax(&hypotheticalBitboard, depth-1, false, alpha, beta);

                                if(hypotheticalEval.eval > eval.eval)
                                {
                                    eval.eval = hypotheticalEval.eval;
                                    //TODO Note: this code might be redundand outside the root nodes
                                    eval.bestMove.pieceType = i;
                                    eval.bestMove.modified = hypotheticalBitboard.bitboards[i];
                                    eval.extra = promotion;
                                }

                                alpha = std::max(alpha, eval.eval);
                                if(beta <= alpha)
                                    return eval; // Stop examining node
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        /* Minimizing (black) */

        eval.eval = INT32_MAX;

        // Iterate over every black piece bitboard
        for(uint8_t i = 0; i < 6; ++i)
        {
            // Iterate over every bit in the bitboard
            for(uint8_t j = 0; j < 64; ++j)
            {
                // Check if there is a piece on that square
                if(bitboard->bitboards[i] & (1ULL << j))
                {
                    const uint64_t legalMoves = GetLegalMoves(bitboard, i, j); // Get legal moves
                    const uint64_t orderedMoves[] = {
                        legalMoves & GetCombinedBitboardWhite(bitboard),
                        legalMoves ^ orderedMoves[0]
                    };

                    // Iterate over every move from most to least aggressive
                    for(uint8_t moveOrder = 0; moveOrder < 2; ++moveOrder)
                    {
                        for(uint8_t k = 0; k < 64; ++k)
                        {
                            if(orderedMoves[moveOrder] & (1ULL << k))
                            {
                                Bitboard hypotheticalBitboard = *bitboard;

                                // Capture pieces at target square
                                for(int l = 0; l < 12; ++l)
                                    hypotheticalBitboard.bitboards[l] &= ~(1ULL << k);
                                hypotheticalBitboard.bitboards[i] &= ~(1ULL << j); // Remove piece from old position
                                hypotheticalBitboard.bitboards[i] |= (1ULL << k); // Place piece at target position
                                // TODO only promotes to queens, add other pieces
                                const Search::BitboardModification promotion = Search::PromotePieces(&hypotheticalBitboard, RANK_1, PB, QB); // Handle promotions

                                Search::DeepEval hypotheticalEval = minimax(&hypotheticalBitboard, depth-1, true, alpha, beta);

                                if(hypotheticalEval.eval < eval.eval)
                                {
                                    eval.eval = hypotheticalEval.eval;
                                    //TODO Note: this code might be redundand outside the root nodes
                                    eval.bestMove.pieceType = i;
                                    eval.bestMove.modified = hypotheticalBitboard.bitboards[i];
                                    eval.extra = promotion;
                                }

                                beta = std::min(beta, eval.eval);
                                if(beta <= alpha)
                                    return eval; // Stop examining node
                            }
                        }
                    }
                }
            }
        }
    }

    return eval;
}