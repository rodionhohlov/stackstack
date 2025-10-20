#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "translate_funcs.h"

int main(void) {

    const char* lang_commands = "converter/command_info.txt";
    const char user_file_name[100] = "user_win.asm";

    int cnt = 0;     //count of commands in file with array of commands

    cmd_t* cmd_buffer = fill_cmd_buffer(lang_commands, &cnt);

    //for (int i = 0; i < 11; i++)
        //printf("%s | %d\n", (cmd_buffer[i]).cmd_name, (cmd_buffer[i]).cmd_code);

    byte_t bytecode = {};

    make_code_buffer(&bytecode, user_file_name, cmd_buffer, cnt);

    printf("fucking cnt is %d\n", cnt);

    for (int i = 0; i < bytecode.capasity; i++) {
        if (i % 2 == 0)
            printf("pause\n");
        printf("super res is %d\n", bytecode.buffer[i]);
    }

    assert(bytecode.buffer);

   // print_in_byte_code(code_buffer);

    print_in_byte_code(&bytecode);

    return 0;
}
