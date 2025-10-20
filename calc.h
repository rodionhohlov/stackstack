#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

#include "stkType.h"

struct byte_t {
    int* buffer;
    size_t capacity;
    int flag;
};

void program_slave(void);

void solve_slave(byte_t* bytecode);

byte_t fill_bytecode_buffer(FILE* reader);

#endif // CALC_H_INCLUDED
