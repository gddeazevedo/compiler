#include "parser.h"

void start_compilation(char* file_name) {
    init_assembly_file();
    read_file(file_name);
}

static void init_assembly_file() {  //cria o arquivo de saída em assembly
    FILE* file = fopen("program.asm", "w");

    if (file == NULL) {
        fprintf(stderr, "Error in opening file!\n");
        exit(1);
    }

    char* str[] = {
        "section .data\n\tformat: db \"%d\", 0\n",
        "section .bss\n\tr: resd 32\n",
        "section .text\n\textern printf\n\textern scanf\n\tglobal main\n",
        "\nmain:\n"
    };

    for (int i = 0; i < 4; i++) { 
        fputs(str[i], file);
    }

    fclose(file);
}

static void read_file(char* file_name) { //recebe linha por linha do arquivo e começa a leitura
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

static void parse_line(char* line) { //compara as linhas do documento recebido através do regex
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

    int error = error_scan || error_print ||    //se o regcomp for verdadeiro, dá erro de compilação
        error_atr || error_while ||
        error_if || error_else || 
        error_endif || error_endwhile;

    if (error) {
        printf("Erro de compilação");
        exit(1);
    }

    FILE* file = fopen("program.asm", "a+");    //printa no arquivo a tradução

    if (!regexec(&regex_scan, line, 0, NULL, 0)) {
        parse_scan(file);
    } else if (!regexec(&regex_print, line, 0, NULL, 0)) {
        parse_print(file);
    } else if (!regexec(&regex_atr, line, 0, NULL, 0)) {
        parse_assignment(file, line);
    } else if (!regexec(&regex_while, line, 0, NULL, 0)) {
        parse_while(file);
    } else if (!regexec(&regex_if, line, 0, NULL, 0)) {
        parse_if(file);
    } else if (!regexec(&regex_else, line, 0, NULL, 0)) {
        parse_else(file);
    } else if (!regexec(&regex_endif, line, 0, NULL, 0)) {
        parse_endif(file);
    } else if (!regexec(&regex_endwhile, line, 0, NULL, 0)) {
        parse_endwhile(file);
    }

    fclose(file);
}

/********************************* Scan *********************************************/

static void parse_scan(FILE* file) {
    fputs("\tmov ebx, r\n", file);
    fputs("\tpusha\n", file);
    fputs("\tpush ebx\n", file);
    fputs("\tpush format\n", file);
    fputs("\tcall scanf\n", file);
    fputs("\tpopa\n", file);
    fputs("\tadd esp, 8\n", file);
}

/********************************* Print *********************************************/

static void parse_print(FILE* file) {
    fputs("\tmov ebx, r\n", file);
    fputs("\tpusha\n", file);
    fputs("\tpush ebx\n", file);
    fputs("\tpush format\n", file);
    fputs("\tcall printf\n", file);
    fputs("\tpopa\n", file);
    fputs("\tadd esp, 8\n", file);
}

/****************************** Atribuição ******************************************/

static void parse_assignment(FILE* file, char* line) {
    char str[50];
    int value = get_number_from_string(line);
    fputs("\tmov esi, 0\n", file);
    sprintf(str, "\tmov eax, %d\n", value);
    fputs(str, file);
    fputs("\tmov edx, r\n", file);
    fputs("\tmov dword [edx + 4 * esi], eax\n", file);
}

/******************************** While ********************************************/

static void parse_while(FILE* file) {
    fputs("\tWHILE:\n", file);
}

/********************************* If *********************************************/

static void parse_if(FILE* file) {
    fputs("\tIF:\n", file);
}

/********************************* Else *********************************************/

static void parse_else(FILE* file) {
    fputs("\tELSE:\n", file);
}

/********************************* Endif *********************************************/

static void parse_endif(FILE* file) {
    fputs("\tENDIF:\n", file);
}

/********************************* Endwhile *********************************************/

static void parse_endwhile(FILE* file) {
    fputs("\tjmp WHILE\n", file);
    fputs("\tENDWHILE:\n", file);
}
