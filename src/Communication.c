/**
 * @file Communication.c
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief implementação da comunicação - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <Communication.h>

//=========== UTILS FUNCTIONS ==================================================
void logError(const char* str) {
    printf("%s\n", str);
    exit(EXIT_FAILURE);
}

void logAction(Action* action) {
    printf("[log] Type: %d, X: %d, Y: %d\n",
           action->type,
           action->coordinates[0],
           action->coordinates[1]);
    printMineSweeper(action->board);
}