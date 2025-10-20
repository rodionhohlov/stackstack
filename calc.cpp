#include<stdio.h>
#include<assert.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

#include "stkType.h"
#include "calc.h"
#include "asm_funcs.h"

enum command_t {
    PUSH = 1,
    POP  = 2,
    SUM  = 3,
    SUB  = 4,
    MUL  = 5,
    DIV  = 6,
    SQRT = 7,
    OUT  = 8,
    HLT  = 9,
    IN   = 10
};

void program_slave(void) {

    FILE* algoritm = fopen("bytecode.txt", "r");

    assert(algoritm);

    byte_t bytecode = fill_bytecode_buffer(algoritm);

    fclose(algoritm);

    /*printf("buffer[0] = %d\n", byte_buffer[0]);
    printf("buffer[1] = %d\n", byte_buffer[1]);
    printf("buffer[2] = %d\n", byte_buffer[2]);  */

    solve_slave(&bytecode);


}

void solve_slave(byte_t* bytecode) {

    stack_t stk = {};
    stack_init(&stk, 5);

    int value = 0;

    for (int i = 0; i <= bytecode->flag; i+=2) {

        //printf("values from bytecode: %d, %d\n", bytecode->buffer[i], bytecode->buffer[i+1]);

        switch(bytecode->buffer[i]) {

        case PUSH:
            stack_push(&stk, bytecode->buffer[i+1]);
            break;

        case POP: // enum
            value = stack_pop(&stk);
            break;

        case SUM:
            do_sum(&stk);
            break;

        case SUB:
            do_sub(&stk);
            break;

        case MUL:
            do_mul(&stk);
            break;

        case DIV:
            do_div(&stk);
            break;

        case SQRT:
            do_sqrt(&stk);
            break;

        case OUT:
            do_out(&stk);
            break;

        case HLT:
            do_hlt(&stk);
            return;

        case IN:
            do_in(&stk);
            break;

        default:
            do_dump(i/2 + 1, "output_window.txt");
        }
    }

}

byte_t fill_bytecode_buffer(FILE* reader) {
    byte_t code = {};

    code.capacity = 5;
    
    code.buffer = (int*)calloc(code.capacity, sizeof(int));

    for (size_t i = 0; fscanf(reader, "%d", &(code.buffer[i])) != EOF; i++) {

        if (i >= code.capacity) {

            code.capacity *= 2;

            code.buffer = (int*)realloc(code.buffer, code.capacity*sizeof(int));
        }

        //printf("value from bytecode: %d\n", code.buffer[i]);

        code.flag++;
    }

    return code;
}


