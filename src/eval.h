#ifndef EVAL_H
#define EVAL_H

#include <cmath>
#include "bitboard.h"
#include "utils.h"
#include "pieces.h"

namespace Eval
{
// TODO this is stupid. make better.
const int pieceSquareTables[6][64]
{
    {
    0,   0,   0,   0,   0,   0,   0,   0,
    250, 250, 250, 250, 250, 250, 250, 250,
    170, 150, 150, 160, 160, 150, 150, 170,
    125, 120, 100, 125, 125, 100, 120, 125,
    100, 110, 120, 150, 150, 120, 110, 100,
    100, 110, 70,  125, 125, 70,  110, 100,
    100, 100, 100, 100, 100, 100, 100, 100,
    0,   0,   0,   0,   0,   0,   0,   0
    },
    {
    200, 220, 250, 280, 280, 250, 220, 200,
    210, 220, 260, 265, 265, 260, 220, 210,
    250, 280, 320, 340, 340, 320, 280, 250,
    265, 290, 320, 335, 335, 320, 290, 265,
    265, 290, 315, 270, 270, 315, 290, 265,
    250, 270, 330, 315, 315, 330, 270, 250,
    210, 250, 280, 300, 300, 280, 250, 210,
    200, 230, 240, 250, 250, 240, 230, 200
    },
    {
    230, 260, 285, 300, 300, 285, 260, 230,
    250, 280, 290, 300, 300, 290, 280, 250,
    270, 300, 320, 310, 310, 320, 300, 270,
    290, 320, 350, 330, 330, 350, 320, 290,
    290, 300, 350, 330, 330, 350, 300, 290,
    270, 300, 320, 310, 310, 320, 300, 270,
    250, 310, 280, 310, 310, 280, 310, 250,
    230, 250, 270, 280, 280, 270, 250, 230
    },
    {
    600, 600, 600, 600, 600, 600, 600, 600,
    580, 580, 580, 580, 580, 580, 580, 580,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 490, 500, 510, 510, 500, 490, 500
    },
    {
    955, 960, 960, 950, 950, 960, 960, 955,
    940, 930, 925, 920, 920, 925, 930, 940,
    920, 900, 900, 900, 900, 900, 900, 920,
    900, 900, 900, 900, 900, 900, 900, 900,
    900, 900, 900, 900, 900, 900, 900, 900,
    880, 900, 870, 900, 900, 870, 900, 880,
    850, 900, 900, 900, 900, 900, 900, 850,
    800, 830, 860, 880, 880, 860, 830, 800
    },
    {
    9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999,
    9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000,
    9260, 9240, 9220, 9200, 9200, 9220, 9240, 9260,
    9460, 9440, 9420, 9400, 9400, 9420, 9440, 9460,
    9700, 9660, 9620, 9600, 9600, 9620, 9660, 9700,
    9790, 9760, 9690, 9700, 9700, 9690, 9760, 9790,
    9950, 9980, 9945, 9920, 9920, 9945, 9980, 9950,
    9999, 9999, 9850, 9935, 9935, 9850, 9999, 9999
    }
};

/**
 * Returns an evaluation by using piece square tables
*/
int PieceSquareTablesEval(const Bitboard &bitboard);

/**
 * Returns true if white is checkmated
*/
bool IsWhiteCheckmated(const Bitboard &bitboard);

/**
 * Returns true if black is checkmated
*/
bool IsBlackCheckmated(const Bitboard &bitboard);

/**
 * Returns true if the position is a guaranteed draw
 * @warning Stalemate is checked by seeing whether the king can move or not; THIS DOES NOT include checking if the king is in check
*/
bool IsDraw(const Bitboard &bitboard);
}

#endif