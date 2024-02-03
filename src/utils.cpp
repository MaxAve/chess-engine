#include "utils.h"

std::string BinaryToString(uint8_t n)
{
    std::string str = "";
    for(int i = 7; i >= 0; --i)
        str += ((n & (1 << i)) ? "1" : "0");
    return str;
}

uint8_t CountBits(uint64_t n)
{
    uint8_t count = 0;
    while(n)
    {
        n &= (n - 1);
        count++;
    }
    return count;
}