#include "random.h"

uint16_t lfsr = 0xACE1u;
uint32_t bit;

uint16_t rand()
{
	bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
	return lfsr =  (lfsr >> 1) | (bit << 15);
}
