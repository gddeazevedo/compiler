#ifndef __parser_h
#define __parser_h

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../helpers/helpers.h"


void read_file(char* file_name);
void parse_if();
void parse_else();
void parse_while();
void parse_print();
void parse_scan();
void parse_assignment(char* instruction);

#endif