#include <stdio.h>
#include <stdlib.h>
#include "src/parser/parser.h"
#include "src/helpers/helpers.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Error! Command accepts only one parameter! ./run.out <file>.ml\n");
        exit(1);
    }

    gen_assembly();
    read_file(argv[1]);

    return 0;
}