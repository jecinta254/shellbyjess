#include "shell.h"

void jnj_getline(char *watho, size_t size) {
    if (fgets(watho, size, stdin) == NULL) {
        if (feof(stdin)) {
            jnj_print("\n");
            exit(EXIT_SUCCESS);
        } else {
            perror("Error reading command");
            exit(EXIT_FAILURE);
        }
    }

    watho = trim_spaces(watho);

    if (watho[0] == '\0') {
        jnj_prompt();
        jnj_getline(watho, size);
    }
}

