#ifndef PIECES_H
#define PIECES_H

#include <stdint.h>
#include "bitboard.h"

/**
 * Returns a bitboard (64-bit) where positive bits repsent squares the piece can move to
 * @param bitboard pointer to board representation
 * @param pieceType piece type (e.g. PW, PB, QW, KB)
 * @param bit bit where the piece is located (0 = right-most bit = lower-right corner, 63 = left-most bit = upper-left corner)
 * @returns 64-bit bitboard (uint64_t)
 * @warning Generates all legal moves from scratch; slow!
*/
uint64_t GetLegalMoves(const Bitboard *bitboard, uint8_t pieceType, uint8_t bit);

#endif