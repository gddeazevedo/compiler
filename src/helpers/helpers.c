#include "helpers.h"

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
