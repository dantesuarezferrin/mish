/**
 * @file shell.c
 * @brief Punto de entrada y bucle principal (REPL) del shell.
 */

#define _POSIX_C_SOURCE 200809L

#include "builtins.h"
#include "executor.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *line = NULL;
    size_t lineSize = 0;
    int shouldExit = 0;
    char **args = NULL;

    while (!shouldExit) {
        printf("mish> ");
        fflush(stdout);

        if (getline(&line, &lineSize, stdin) == -1) {
            printf("\n");
            break;
        }

        args = parseLine(line);
        if (args != NULL) {
            if (args[0] != NULL) {
                if ( handleBuiltin(args, &shouldExit) == 0) {
                    executeCommand(args);
                }
            }
            free(args);
        } else {
            fprintf(stderr, "mish: error al analizar la línea\n");
        }
    }

    free(line);
    return 0;
}
