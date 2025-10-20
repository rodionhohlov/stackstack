#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>

#include "stkType.h"
#include "calc.h"

int main(void) {
    stack_t super_stk = {};
    stack_init(&super_stk, 5);

    program_slave();  

    stack_push(&super_stk, 12);

    //show_stk(&super_stk, __LINE__);

    //printf("flag is: %d\n", super_stk.flag);

    //printf("%d %d\n", super_stk.buffer[0], super_stk.buffer[1]);
    //printf("size is: %d\n", super_stk.stk_size);

    int get_val = stack_pop(&super_stk);

    printf("\npopped value: %d\n\n", get_val);

    stack_destroy(&super_stk);

    printf("ptr on stk: %p\n", super_stk.buffer);

    return 0;
}




