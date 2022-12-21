#ifndef __parser_h
#define __parser_h

#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include "../helpers/helpers.h"

#define SCAN "^scan"
#define PRINT "^print"
#define ASSIGNMENT "^r[1-9]*[^a-qs-z]*"
#define WHILE "^whiler[1-9]*[^a-qs-z]*"
#define IF "^if"
#define ELSE "^else"
#define ENDIF "^endif"
#define ENDWHILE "^endwhile"

static int r[32];

void start_compilation(char* file_name);
static void parse_line(char* line);
static void read_file(char* file_name);
static void init_assembly_file();

static void parse_scan(FILE* file);
static void parse_print(FILE* file);
static void parse_assignment(FILE* file);
static void parse_while(FILE* file);
static void parse_if(FILE* file);
static void parse_else(FILE* file);
static void parse_endif(FILE* file);
static void parse_endwhile(FILE* file);

#endif