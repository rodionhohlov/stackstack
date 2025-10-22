#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void my_a_to_i(char* digit_str, int* res);

int main(void) {

    char* lalala = (char*)"0";

    int res = NULL;

    my_a_to_i(lalala, res);

    assert(res);

    printf("%d\n", *res);

    return 0;
}

int* my_a_to_i(char* digit_str, int* res) {
    printf("len is %d\n", strlen(digit_str));

    int arg = 0;

    printf("digit_str[0] = %c\n", digit_str[0]);

    if ((strlen(digit_str) == 1) && (digit_str[0] == '0')) { //
        *res = 0;
        printf("my love\n");
        printf("ptr %p\n", )
    }
        
    else if ((arg = atoi(digit_str)) == 0) {
        printf("gay\n");
        return;
    }
        
    else {
        *res = atoi(digit_str);     
        printf("deadliness\n");
    }
        
    printf("my value is %s\n", digit_str);
    printf("result is %d\n\n", *res);
}