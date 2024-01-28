#ifndef UTILS_H
#define UTILS_H

#include <iostream>

#define GET_1D_X(x, y, width) (x + y * width)
#define GET_2D_X(x) (x % 8)
#define GET_2D_Y(x) (x / 8)

std::string BinaryToString(uint8_t binary);

#endif