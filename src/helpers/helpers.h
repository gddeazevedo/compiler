#ifndef __helpers_h
#define __helpers_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void gen_assembly();
char* trim(char* string);
int get_number_from_string(char* str);
void write_in_assembly(char* content);


#endif