#ifndef ASCII_H
#define ASCII_H

#include "types.h"

void ascii_init(void);
void ascii_print_at(char* string, int8_t x, int8_t y);
void ascii_clear();

#endif // ASCII_H