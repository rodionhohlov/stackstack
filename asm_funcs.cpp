#include<stdio.h>
#include<assert.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

#include "asm_funcs.h"
#include "stkType.h"

void do_sum(stack_t* stk) {

    assert(stk);

    int val1 = stack_pop(stk);
    int val2 = stack_pop(stk);

    stack_push(stk, val1 + val2);
}

void do_sub(stack_t* stk) {

    assert(stk);

    int val1 = stack_pop(stk);
    int val2 = stack_pop(stk);

    stack_push(stk, val2 + val1);
}

void do_mul(stack_t* stk) {

    assert(stk);

    int val1 = stack_pop(stk);
    int val2 = stack_pop(stk);

    stack_push(stk, val2 * val1);
}

void do_div(stack_t* stk) {

    assert(stk);

    int val1 = stack_pop(stk);
    int val2 = stack_pop(stk);

    stack_push(stk, val2 / val1);
}

void do_sqrt(stack_t* stk) {

    assert(stk);

    int val = stack_pop(stk);

    int i = 0;

    for(; i*i < val; i++) {}

    stack_push(stk, i);
}

void do_hlt(stack_t* stk) {

    assert(stk);

    printf("hlt is called. program is finished\n");
}

void do_out(stack_t* stk) {

    assert(stk);

    //printf("out started------------------------\n");

    int* out_buffer = (int*)calloc(stk->stk_size, sizeof(int));

    assert(out_buffer);
    
    //printf("flag is %d\n", stk->flag);

    for (size_t i = 1; i < stk->flag; i++)
        printf("OUT value %d\n", stk->buffer[i]);

    //printf("out finished------------------------\n");

    free(out_buffer);
}

void do_in(stack_t* stk) {

    assert(stk);

    int val = 0;

    for (int i = stk->flag; scanf("%d", &val) != 0; i++) {

        stack_push(stk, val);
    }
}

void do_dump(int line, const char* file) {
    printf("%s: dump is called from LINE %d\n", file, line);
    printf("error of uncoding command");
}