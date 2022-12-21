
#include "src/parser/parser.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Error! Command accepts only one parameter! ./run.out <file>.ml\n");
        exit(1);
    }

    start_compilation(argv[1]); //o argumento que estamos recebendo é o ./<nome do arquivo>

    return 0;
}
