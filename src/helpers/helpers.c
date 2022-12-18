#include "helpers.h"

void gen_assembly() {
    FILE* file = fopen("program.asm", "w");

    if (file == NULL) {
        fprintf(stderr, "Error in opening file!\n");
        exit(1);
    }

    char* str[] = {
        "section .data\n",
        "section .bss\n",
        "section .text\n\textern printf\n\textern scanf\n\tglobal main\n",
        "main:\n\n"
    };

    for (int i = 0; i < 4; i++) { 
        fputs(str[i], file);
    }

    fclose(file);
}

char* trim(char* string) {
    char* newString = strdup(string);

    while(isspace((unsigned char)*newString)) {
        newString++;
    }

    char* end = newString + strlen(newString) - 1;

    while(isspace((unsigned char)*end)) {
        end--;
    }

    end[1] = '\0';

    return newString;
}

int get_number_from_string(char* str) {
    char* ptr = str;
    int counter = 0;

    while (*ptr) {
        if (isdigit(*ptr)) {
            int val = (int)strtol(ptr,&ptr, 10);
            counter++;
            
            if (counter == 2) {
                return val;
            }

        } else {
            ptr++;
        }
    }
}

void write_in_assembly(char* content) {
    FILE* file = fopen("program.asm", "a+");

    if (file == NULL) {
        fprintf(stderr, "Error in opening file!\n");
        exit(1);
    }

    fputs(content, file);
    fputs("\n", file);
    fclose(file);
}
