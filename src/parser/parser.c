#include "parser.h"


void read_file(char* file_name) {
    FILE* program_file = fopen(file_name, "r");
    char content[256];

    if (program_file == NULL) {
        fprintf(stderr, "Error in opening file!\n");
        exit(1);
    }

    while (fgets(content, 256, program_file)) {
        char* str = trim(content);

        if (str[0] == 'i') {
            parse_if();
            printf("IF\n");
        } else if (str[1] == 'l') {
            parse_else();
            printf("ELSE\n");
        } else if (str[0] == 'w') {
            parse_while();
            printf("WHILE\n");
        } else if (str[0] == 'r') {
            parse_assignment(str);
            printf("Assignment\n");
        } else if (str[0] == 'p') {
            parse_print();
            printf("PRINT\n");
        } else if (str[0] == 's') {
            parse_scan();
            printf("SCAN\n");
        }
    }

    fclose(program_file);
}


void parse_if() {

}

void parse_else() {

}

void parse_while() {

}

void parse_print() {

}

void parse_scan() {

}

void parse_assignment(char* instruction) {
    char snum[50];
    int num = get_number_from_string(instruction);

    sprintf(snum, "mov eax, %d", num);

    write_in_assembly(snum);
}
