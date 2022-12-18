#include "helpers.h"

void write_assembly() {
    FILE* file = fopen("program.asm", "w");


    if (file == NULL) {
        fprintf(stderr, "Error in opening file!\n");
        exit(1);
    }

    char* str[] = {
        "section .data\n",
        "section .bss\n",
        "section .text\n\textern printf\n\textern scanf\n\tglobal main\n",
        "main:\n"
    };

    for (int i = 0; i < 4; i++) { 
        fputs(str[i], file);
    }

    fclose(file);
}

void read_file(char* file_name) {
    FILE* program_file = fopen(file_name, "r");
    char content[256];

    if (program_file == NULL) {
        fprintf(stderr, "Error in opening file!\n");
        exit(1);
    }

    while (fgets(content, 256, program_file)) {
        printf("%s", content);
    }

    fclose(program_file);
}
