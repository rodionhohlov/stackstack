#ifndef ASM_FUNCS_H_INCLUDED
#define ASM_FUNCS_H_INCLUDED

#include "stkType.h"

void do_sum(stack_t* stk);

void do_sub(stack_t* stk);

void do_mul(stack_t* stk);

void do_div(stack_t* stk);

void do_sqrt(stack_t* stk);

void do_hlt(stack_t* stk);

void do_out(stack_t* stk);

void do_in(stack_t* stk);

void do_dump(int line, const char* file);

int get_num(void);

void do_popr(stack_t* stk);

#endif