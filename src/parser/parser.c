#include "parser.h"

void start_compilation(char* file_name) {
    init_assembly_file();
    read_file(file_name);
}

static void init_assembly_file() {
    FILE* file = fopen("program.asm", "w");

    if (file == NULL) {
        fprintf(stderr, "Error in opening file!\n");
        exit(1);
    }

    char* str[] = {
        "section .data\n\tformat: db \"%d\", 0\n",
        "section .bss\n\tr: resd 32\n",
        "section .text\n\textern printf\n\textern scanf\n\tglobal main\n",
        "main:\n"
    };

    for (int i = 0; i < 4; i++) { 
        fputs(str[i], file);
    }

    fclose(file);
}

static void read_file(char* file_name) {
    FILE* program_file = fopen(file_name, "r");
    char content[256];

    if (program_file == NULL) {
        fprintf(stderr, "Error in opening file!\n");
        exit(1);
    }

    while (fgets(content, 256, program_file)) {
        parse_line(trim(content));
    }
 
    fclose(program_file);
}

static void parse_line(char* line) {
    regex_t regex_scan,
        regex_print,
        regex_atr,
        regex_while,
        regex_if,
        regex_else,
        regex_endif,
        regex_endwhile;

    int error_scan = regcomp(&regex_scan, SCAN, 0);
    int error_print = regcomp(&regex_print, PRINT, 0);
    int error_atr = regcomp(&regex_atr, ASSIGNMENT, 0);
    int error_while = regcomp(&regex_while, WHILE, 0);
    int error_if = regcomp(&regex_if, IF, 0);
    int error_else = regcomp(&regex_else, ELSE, 0);
    int error_endif = regcomp(&regex_endif, ENDIF, 0);
    int error_endwhile = regcomp(&regex_endwhile, ENDWHILE, 0);

    int error = error_scan || error_print ||
        error_atr || error_while ||
        error_if || error_else || 
        error_endif || error_endwhile;

    if (error) {
        printf("Erro de compilação");
        exit(1);
    }

    FILE* file = fopen("program.asm", "a+");

    if (!regexec(&regex_scan, line, 0, NULL, 0)) {
        printf("scan\n");
        parse_scan(file);
        fclose(file);
    } else if (!regexec(&regex_print, line, 0, NULL, 0)) {
        printf("print\n");
        parse_print(file);
        fclose(file);
    } else if (!regexec(&regex_atr, line, 0, NULL, 0)) {
        printf("atribuição\n");
        parse_assignment(file);
        fclose(file);
    } else if (!regexec(&regex_while, line, 0, NULL, 0)) {
        printf("while\n");
        parse_while(file);
        fclose(file);
    } else if (!regexec(&regex_if, line, 0, NULL, 0)) {
        printf("if\n");
        parse_if(file);
        fclose(file);
    } else if (!regexec(&regex_else, line, 0, NULL, 0)) {
        printf("else\n");
        parse_else(file);
        fclose(file);
    } else if (!regexec(&regex_endif, line, 0, NULL, 0)) {
        printf("endif\n");
        parse_endif(file);
        fclose(file);
    } else if (!regexec(&regex_endwhile, line, 0, NULL, 0)) {
        printf("endwhile\n");
        parse_endwhile(file);
        fclose(file);
    }
}

static void parse_scan(FILE* file) {
    fputs("mov ebx, r\n", file);
    fputs("pusha\n", file);
    fputs("push ebx\n", file);
    fputs("push format\n", file);
    fputs("call scanf\n", file);
    fputs("popa\n", file);
    fputs("add esp, 8\n", file);
}

static void parse_print(FILE* file) {
    fputs("mov ebx, r\n", file);
    fputs("pusha\n", file);
    fputs("push ebx\n", file);
    fputs("push format\n", file);
    fputs("call printf\n", file);
    fputs("popa\n", file);
    fputs("add esp, 8\n", file);
}

static void parse_assignment(FILE* file) {

}

static void parse_while(FILE* file) {

}

static void parse_if(FILE* file) {

}

static void parse_else(FILE* file) {

}

static void parse_endif(FILE* file) {

}

static void parse_endwhile(FILE* file) {
    
}
