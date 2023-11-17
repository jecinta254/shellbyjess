#include "shell.h"

void execute_commands(char *commands) {
    char *token = strtok(commands, ";");
    while (token != NULL) {
        if (token[0] != '\0' && token[0] != '\n') {
            execute_logical_commands(trim_spaces(token));
        }
        token = strtok(NULL, ";");
    }
}

void execute_logical_commands(char *commands) {
    char *token_and = strtok(commands, "&&");
    while (token_and != NULL) {
        if (token_and[0] != '\0' && token_and[0] != '\n') {
            jnj_execute(trim_spaces(token_and));
        }
        token_and = strtok(NULL, "&&");
    }
    
    char *token_or = strtok(commands, "||");
    while (token_or != NULL) {
        if (token_or[0] != '\0' && token_or[0] != '\n') {
            jnj_execute(trim_spaces(token_or));
        }
        token_or = strtok(NULL, "||");
    }
}

