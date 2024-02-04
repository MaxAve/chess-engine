#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>
#include "types.h"

/* Flag bits */
#define CURRENT_TURN          1 << 0
#define WHITE_QEENSIDE_CASTLE 1 << 1
#define WHITE_KINGSIDE_CASTLE 1 << 2
#define BLACK_QEENSIDE_CASTLE 1 << 3
#define BLACK_KINGSIDE_CASTLE 1 << 4

/* Bitboard directions */
#define UP          8
#define DOWN       -8
#define LEFT        1
#define RIGHT      -1
#define UP_LEFT     9
#define UP_RIGHT    7
#define DOWN_LEFT  -7
#define DOWN_RIGHT -9

/* Bitboards for certain operations */
#define LEFT_EXCLUDE  0x7f7f7f7f7f7f7f7fULL
#define RIGHT_EXCLUDE 0xfefefefefefefefeULL

#define _FILE  0x0101010101010101ULL
#define A_FILE (_FILE<<7)
#define B_FILE (_FILE<<6)
#define C_FILE (_FILE<<5)
#define D_FILE (_FILE<<4)
#define E_FILE (_FILE<<3)
#define F_FILE (_FILE<<2)
#define G_FILE (_FILE<<1)
#define H_FILE FILE_

#define RANK   0x00000000000000ffULL
#define RANK_1 RANK
#define RANK_2 (RANK<<8)
#define RANK_3 (RANK<<16)
#define RANK_4 (RANK<<24)
#define RANK_5 (RANK<<32)
#define RANK_6 (RANK<<40)
#define RANK_7 (RANK<<48)
#define RANK_8 (RANK<<56)

/* Board setups */
#define BOARD_SETUP_EMPTY   0
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
void PutPiece(Bitboard *bitboard, uint8_t piece, uint8_t x, uint8_t y);

#endif