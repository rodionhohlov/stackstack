#include<stdio.h>
#include<assert.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

#define ASSERTED
#define STACK_VERIFY stack_verify(stk, __FILE__, __LINE__)

#include "stkType.h"

int canary_value = 0xDEADBEEF;

void stack_init(stack_t* stk, int min_stk_size) {
    stk->stk_size = min_stk_size;

    stk->buffer = (int*)calloc(min_stk_size + 2, sizeof(int));

    stk->buffer[0] = canary_value;

    stk->buffer[stk->stk_size + 1] = canary_value;

    stk->registers = (int*)calloc(4, sizeof(int));

    #ifdef ASSERTED
        STACK_VERIFY;
    #endif
}

void stack_push(stack_t* stk, int num) {

    #ifdef ASSERTED
        STACK_VERIFY;
    #endif

    size_t ind = stk->flag;

    //printf("we push %d\n", num);

    stk->buffer[ind] = num;

    stk->flag++;

    if (ind > (stk->stk_size - 1)) {
        stk->stk_size *= 2;

        stk->buffer = (int*)realloc(stk->buffer, (stk->stk_size + 2)*sizeof(int));
    }

    stk->buffer[stk->stk_size + 1] = canary_value;

    #ifdef ASSERTED
        STACK_VERIFY;
    #endif
}

int stack_pop(stack_t* stk) {

    #ifdef ASSERTED
        STACK_VERIFY;
    #endif

    stk->flag--;

    int value = stk->buffer[stk->flag];

    //printf("we got %d\n", value);

    #ifdef ASSERTED
        STACK_VERIFY;
    #endif

    return value;
}

void stack_destroy(stack_t* stk) {

    #ifdef ASSERTED
        STACK_VERIFY;
    #endif

    free(stk->buffer);
    free(stk->registers);

    stk->stk_size = 0;

    stk->flag = 1;

    stk->buffer = NULL;

    stk->registers = NULL;
}

void stack_verify(stack_t* stk, const char* file, int line) {

    if (stk->buffer == NULL)
        stk->err = NULL_BUF;

    else if (stk->flag > stk->stk_size)
        stk->err = FILL_SIZE;

    else if (stk->buffer[0] != canary_value)
        stk->err = ATTACK_LEFT;

    else if (stk->buffer[stk->stk_size + 1] != canary_value)
        stk->err = ATTACK_RIGHT;

    else if (stk->stk_size < 0)
        stk->err = LESS_NUL_SZ;

    else if (stk == NULL)
        stk->err = NULL_STACK;

    else if (stk->flag <= 0)
        stk->err = LESS_NUL_FLAG;

    else if (stk->registers == NULL)
        stk->err = NULL_REGISTERS;

    if (stk->err != NO_ERROR)
        stack_dump(stk, file, line);

}

void stack_dump(stack_t* stk, const char* file, int line) {
    FILE* output = fopen("output_window.txt", "a");

    fprintf(output, "stack_dump is called from %s: %d\n", file, line);
    fprintf(output, "stack[%p]\n", stk);
    fprintf(output, "size = %d \ncapacity = %d \ndata = %p\n", stk->stk_size, stk->flag - 1, stk->buffer);

    size_t i = 0;

    printf("\n\n the flag is %d\n\n", stk->flag - 1);

    char err_str[50] = {};

    translate_err_code(stk, err_str);

    printf("my mistake is: %s\n\n", err_str);
    printf("line is %d\n", line);
    printf("-----------\nsize and flag are %d %d\n---------\n", stk->stk_size, stk->flag);

    for (; i < (stk->flag - 1); i++)
        fprintf(output, "%10s [%d] = %d\n", "filled", i, stk->buffer[i]);

    for (;i < stk->stk_size; i++)
        fprintf(output, "%10s [%d] = %d\n", "empty", i, stk->buffer[i]);

    fprintf(output, "\n");

    fclose(output);
}

void translate_err_code(stack_t* stk, char* str) {

    err_code num = stk->err;

    switch(num) {
        case NO_ERROR:
            sprintf(str, "successful_buffer");
            break;

        case NULL_BUF:
            sprintf(str, "buffer pointer specifyes to NULL");
            break;

        case FILL_SIZE:
            sprintf(str, "size of buffer is overfilled");
            break;

        case ATTACK_LEFT:
            sprintf(str, "front canary is damaged");
            break;

        case ATTACK_RIGHT:
            sprintf(str, "back canary is damaged");
            break;

        case LESS_NUL_SZ:
            sprintf(str, "size less than 0");
            break;

        case NULL_STACK:
            sprintf(str, "null stack pointer");
            break;

        case LESS_NUL_FLAG:
            sprintf(str, "flag is out of range");
            break;
        
        case NULL_REGISTERS:
            sprintf(str, "reguster ptr is NULL");

        default:
            sprintf(str, "undefined error");
    }
}

void clear_previous_result(const char* file_name) {
    FILE* reader = fopen(file_name, "w");
    fclose(reader);
}


