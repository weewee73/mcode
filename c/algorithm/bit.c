#include <stdint.h>

/*Bitwise left rotation*/
static inline uint32_t rol32(uint32_t i, int n)
{
    return (i << n | i >> (32 - n));
}

/*Bitwise right rotation*/
static inline uint32_t ror32(uint32_t i, int n)
{
    return (i << (32 - n) | i >> n);
}
