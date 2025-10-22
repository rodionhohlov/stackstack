#ifndef STKTYPE_H_INCLUDED
#define STKTYPE_H_INCLUDED

enum err_code {
    NO_ERROR       = 0,
    NULL_BUF       = 1,
    FILL_SIZE      = 2,
    ATTACK_LEFT    = 3,
    ATTACK_RIGHT   = 4,
    LESS_NUL_SZ    = 5,
    NULL_STACK     = 6,
    LESS_NUL_FLAG  = 7,
    NULL_REGISTERS = 8
};

enum registers {
    AX = 0,
    BX = 1,
    CX = 2,
    DX = 3
};

struct stack_t {
    size_t stk_size = 0;
    int* buffer = {};
    int* registers = {};
    int command_counter= 0;
    size_t flag = 1;
    err_code err = NO_ERROR;
};

void stack_init(stack_t* stk, int min_stk_size);

void stack_push(stack_t* stk, int num);

int stack_pop(stack_t* stk);

void stack_destroy(stack_t* stk);

void stack_verify(stack_t* stk, const char* file, int line);

void stack_dump(stack_t* stk, const char* file, int line);

void translate_err_code(stack_t* stk, char* str);

void clear_previous_result(const char* file_nam);

#endif // STKTYPE_H_INCLUDED
