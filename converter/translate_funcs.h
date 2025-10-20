#ifndef TRANSLATE_FUNCS_H_INCLUDED
#define TRANSLATE_FUNCS_H_INCLUDED

struct cmd_t {
    char cmd_name[20];
    int cmd_code;
    int expected_args;
};

struct byte_t {   //my bytecode array
    int* buffer;
    int capasity;
};

cmd_t* fill_cmd_buffer(const char* file_name, int* cnt);

void make_code_buffer(byte_t* byte_code, const char* file_name, cmd_t* cmd_buffer, int cmd_cnt);

void translate_cmd(byte_t* bytecode, cmd_t* cmd_buffer, int cmd_cnt, char* input, int* index);

void print_in_byte_code(byte_t* bytecode);

int file_line_cnt(FILE* reader);

#endif // TRANSLATE_FUNCS_H_INCLUDED
