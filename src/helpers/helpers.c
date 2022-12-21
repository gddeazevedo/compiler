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
