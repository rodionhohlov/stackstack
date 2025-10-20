#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "translate_funcs.h"

cmd_t* fill_cmd_buffer(const char* file_name, int* cnt) {
    assert(file_name);
    assert(cnt);

    printf("name is \"%s\"\n", file_name);

    FILE* reader = fopen(file_name, "r");
    
    //fclose(reader);

    //FILE* reader = fopen(file_name, "r");

    printf("file ptr %p\n", reader);

    assert(reader);

    *cnt = file_line_cnt(reader);

    cmd_t* cmd_buffer = NULL;

    printf("lines are %d\n", *cnt);

    printf("sz is %d\n", sizeof(cmd_t));

    cmd_buffer = (cmd_t*)calloc(*cnt, sizeof(cmd_t));

    for (int i = 0; i < *cnt; i++) {
        //  printf("swag\n");

        fscanf(reader, "%s %d %d\n", (cmd_buffer + i)->cmd_name, &((cmd_buffer + i)->cmd_code), &((cmd_buffer + i)->expected_args));

        assert((cmd_buffer + i)->cmd_name);

        //  printf("%d\n", scn);
    }

    fclose(reader);

    return cmd_buffer;
}

void make_code_buffer(byte_t* bytecode, const char* file_name, cmd_t* cmd_buffer, int cmd_cnt) {
    assert(cmd_buffer);
    assert(bytecode);
    assert(file_name);

    FILE* reader = fopen(file_name, "r");

    assert(reader);

    printf("file nameis \"%s\"\n", file_name);

    int index = 0;
    int read_size = 100;
    
    int code_lines_cnt = file_line_cnt(reader);
    
    bytecode->capasity = code_lines_cnt * 2;

    char* input = (char*)calloc(read_size, sizeof(char));

    bytecode->buffer = (int*)calloc(bytecode->capasity, sizeof(int));

    // printf("bimbimbambam\n");

    while (fgets(input, read_size, reader) != NULL) {

        //printf("bimbimbambam line %d\n", __LINE__);

        translate_cmd(bytecode, cmd_buffer, cmd_cnt, input, &index); // translate_commands

        //printf("from lime 99: %s (|) %d\n", cmd, value);
        //printf("commands count: %d\n", cmd_cnt);
    }
    // printf("%p\n", reader);

    free(cmd_buffer);
}

void translate_cmd(byte_t* bytecode, cmd_t* cmd_buffer, int cmd_cnt, char* input, int* index) {

    assert(bytecode);
    assert(cmd_buffer);
    assert(input);

    int value = 0;
    char cmd[30] = {};

    int scanned = sscanf(input, "%s %d;  \n", cmd, &value);

    //printf("line is _%s %d %s_\n", cmd, value, comment);

    int found = 0;

    for (int i = 0; i < cmd_cnt; i++) {

       // printf("optimus prime:(\n");

        if (strcmp(cmd_buffer[i].cmd_name, cmd) == 0) {

          //  printf("%s (|) %d\n", cmd, value);
            if (scanned == 2 || scanned == cmd_buffer[i].expected_args) {

                bytecode->buffer[*index]   = cmd_buffer[i].cmd_code;
                bytecode->buffer[*index+1] = value;
            }

            else if (scanned == 1 || scanned == cmd_buffer[i].expected_args)
                bytecode->buffer[*index]   = cmd_buffer[i].cmd_code;

            else
                printf("syntax error, undefined command in line %d\n", (*index/2) + 1);

            printf("original %s %d\n", cmd_buffer[i].cmd_name, value);
            printf("in buffer %d %d\n", bytecode->buffer[*index], bytecode->buffer[*index+1]);
           // printf("i = %d\n", i);
            printf("index = %d\n\n", *index);

            found = 1;

            *index += 2;

            break;
        }
    }

    if (found == 0)
        printf("error: line %d current command not found\n", (*index/2) + 1);

}

void print_in_byte_code(byte_t* bytecode) {

    FILE* out = fopen("bytecode.txt", "w");

    for (int i = 0; i < bytecode->capasity; i++)
        fprintf(out, "%d ", bytecode->buffer[i]);

    fclose(out);
    free(bytecode);
}

int file_line_cnt(FILE* reader) {

    char cur[50] = {};
    int cnt = 0;

    while(fgets(cur, 50, reader) != NULL)
        cnt++;

    rewind(reader);

    return cnt;
}

