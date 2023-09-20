/**
 * @file MineSweeper.c
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief cabeçalho do campo minado - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <MineSweeper.h>
#include <sys/socket.h>

void createMineSweeper(MineSweeper* mine, char* inputFileName) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* file = fopen(inputFileName, "r");
    if(file == NULL) {
        printf("error: File doesn't exist.");
        exit(EXIT_FAILURE);
    }

    while((read = getline(&line, &len, file)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    fclose(file);
    if(line) free(line);
}

void destroyMineSweeper(MineSweeper* mine) { free(mine); }