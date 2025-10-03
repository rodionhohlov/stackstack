#include<stdio.h>
#include<assert.h>
#include<errno.h>
#include<string.h>

#include "stkType.h"
#include "calc.h"

int calculator(stack_t* stk) {

    FILE* algoritm = fopen("calculator.txt", "r");

    assert(algoritm);

    int num = 0;
    char func[10]= {};

    char params[25] = {};

    while (fgets(params, sizeof(params), algoritm) != NULL) {
        printf("%s\n", params);
        int res = sscanf(params, "%s %d", func, &num);
        make_func(stk, func, num, res);
    }

    return 0;
}

void make_func(stack_t* stk, char* func, int num, int res) {

    int* val1 = NULL;
    int* val2 = NULL;
    //to finish with nums
}
