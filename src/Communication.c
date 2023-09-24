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
    char type[25];
    switch(action->type) {
        case START: strcpy(type, "START"); break;
        case REVEAL: strcpy(type, "REVEAL"); break;
        case SET_FLAG: strcpy(type, "FLAG"); break;
        case STATE: strcpy(type, "STATE"); break;
        case REMOVE_FLAG: strcpy(type, "REMOVE_FLAG"); break;
        case RESET: strcpy(type, "RESET"); break;
        case WIN: strcpy(type, "WIN"); break;
        case EXIT: strcpy(type, "EXIT"); break;
        case GAME_OVER: strcpy(type, "GAME_OVER"); break;
        case INVALID: strcpy(type, "INVALID"); break;
    }
    printf("[log] Type: %s, X: %d, Y: %d\n",
           type,
           action->coordinates[0],
           action->coordinates[1]);
    printMineSweeper(action->board);
}

int sendAction(
    int destSocket, Action* action, char* buffer, size_t size, int flags) {
    // Copies the action as an byte string
    memcpy(buffer, action, size);
    // Sends the message
    if(send(destSocket, buffer, size, flags) != size) return 1;
    return 0;
}

int recvAction(
    int originSocket, Action* action, char* buffer, size_t size, int flags) {
    // Receives the message
    if(recv(originSocket, buffer, ACTION_SIZE, flags) != size) return 1;
    // Copies the content from the buffer to the action variable
    memcpy(action, buffer, size);
    return 0;
}