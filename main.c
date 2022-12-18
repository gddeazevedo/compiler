
#include <stdio.h>
#include <stdlib.h>
#include "src/helpers/helpers.h"
#include <regex.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Error! Command accepts only one parameter! ./run.out <file>.ml\n");
        exit(1);
    }

    // scan\s?[r]\d\d?

    char pattern[] = "scan\\s?[r][[:digit:]][[:digit:]]?";
    regex_t regex;
    int error = regcomp(&regex, pattern, 0);


    if (error == 1) {
        printf("Compile error\n");
        return 1;
    } else {
        printf("Ok\n");
    }

    int match = regexec(&regex, pattern, 0, NULL, 0);

    if (!match) {
        printf("FOUND!\n");
    } else if (match == REG_NOMATCH) {
        printf("NOT FOUND\n");
    } else {
        printf("ERROR\n");
    }

    return 0;
}