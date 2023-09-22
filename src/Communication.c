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