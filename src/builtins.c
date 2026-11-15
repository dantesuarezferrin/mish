/**
 * @file builtins.c
 * @brief Implementación de los comandos internos (built-ins) del shell.
 */

#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int handleBuiltin(char **args, int *shouldExit) {
    if (args == NULL || args[0] == NULL) {
        return 1;
    }

    if (strcmp("cd", args[0]) == 0) {
        char *path = NULL;

        if (args[1] == NULL) {
            path = getenv("HOME");
            if (path == NULL) {
                fprintf(stderr, "cd: HOME not set\n");
                return -1;
            }
        } else if (args[2] != NULL) {
            fprintf(stderr, "cd: too many arguments\n");
            return -1;
        } else {
            path = args[1];
        }

        if (chdir(path) == -1) {
            perror("cd");
            return -1;
        }
        return 1;
    }

    if (strcmp("help", args[0]) == 0) {
        printf("mish - Mini Shell\n");
        printf("Comandos internos soportados:\n");
        printf("  cd [dir]  - Cambia el directorio actual\n");
        printf("  help      - Muestra esta ayuda\n");
        printf("  exit      - Sale del shell\n");
        return 1;
    }

    if (strcmp("exit", args[0]) == 0) {
        if (shouldExit != NULL) {
            (*shouldExit) = 1;
        }
        return 1;
    }

    return 0;
}
