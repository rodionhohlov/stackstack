#ifndef STKTYPE_H_INCLUDED
#define STKTYPE_H_INCLUDED

/*struct err_t {
    int err_code = 0;
    char err_txt[50] = {};
}; */

struct stack_t {
    size_t stk_size = 0;
    int* buffer = {};
    size_t flag = 1;
   // err_t err = {.err_code = 0; .err_txt = "NO ERROR"};
};

#endif // STKTYPE_H_INCLUDED
