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
    Action* convertedAction = (Action*)malloc(sizeof(Action));
    // Convert to big endian
    convertedAction->type = htonl(action->type);
    convertedAction->coordinates[0] = htonl(action->coordinates[0]);
    convertedAction->coordinates[1] = htonl(action->coordinates[1]);
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            convertedAction->board[i][j] = htonl(action->board[i][j]);

    // Copies the action as an byte string
    memcpy(buffer, convertedAction, size);
    // Since the buffer has already copied the value, then frees this tmp action
    free(convertedAction);
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

    // Convert from big endian
    action->type = ntohl(action->type);
    action->coordinates[0] = ntohl(action->coordinates[0]);
    action->coordinates[1] = ntohl(action->coordinates[1]);
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            action->board[i][j] = ntohl(action->board[i][j]);

    return 0;
}