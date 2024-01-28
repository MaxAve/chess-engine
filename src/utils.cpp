#include "utils.h"

std::string BinaryToString(uint8_t binary)
{
    std::string str = "";
    for(int i = 7; i >= 0; --i)
        str += ((binary & (1 << i)) ? "1" : "0");
    return str;
}