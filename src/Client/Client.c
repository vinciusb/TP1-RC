/**
 * @file Client.c
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief implementação do client - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <Client.h>

void getXY(char* str, int* x, int* y);

//========== CLIENT ============================================================
void createClient(Client* client, char* IP, char* port) {
    // Parses the IP address
    if(addrParse(IP, port, &client->storage))
        logError("error: Failed at IP parsing.");
    client->addr = (struct sockaddr*)&client->storage;

    // Creates the socket
    client->socket = socket(client->storage.ss_family, SOCK_STREAM, 0);
    if(client->socket == -1) logError("error: Socket not created.");

    // Tries to connect to the server
    if(connect(client->socket, client->addr, sizeof(client->storage)))
        logError("error: Connect failed.");

    // Cleans the client communication buffer
    memset(client->buffer, 0, ACTION_SIZE);

    client->started = 0;
}

void destroyClient(Client* client) { close(client->socket); }

void run(Client* client) {
    Action* action = (Action*)malloc(sizeof(Action));

    // Client infinite loop
    while(1) {
        getNextActionFromCli(action);

        // Validades this action
        if(actionIsValid(client, action)) {
            // Send action to server
            if(sendAction(
                   client->socket, action, client->buffer, ACTION_SIZE, 0)) {
                // Closes the connection
                close(client->socket);
                logError("error: Didn't send all the bytes");
            }

            // If it's desired to quit the game
            if(action->type == EXIT) break;

            // Receives message from server
            if(recvAction(
                   client->socket, action, client->buffer, ACTION_SIZE, 0)) {
                // Closes the connection
                close(client->socket);
                logError("error: Didn't receive all the bytes");
            }

            // Process this action
            processAction(client, action);
        }
    }
    // Closes the connection
    close(client->socket);
    free(action);
}

void processAction(Client* client, Action* action) {
    switch(action->type) {
        case STATE: break;
        case WIN: printf("WIN!\n"); break;
        case GAME_OVER: printf("GAME OVER!\n"); break;
    }

    // Since there are only 3 actions that the client is going to receive (and
    // all of them need to show the board, then just copy and prints all the
    // time)
    memcpy(client->board, action->board, BOARD_SIZE);
    printMineSweeper(client->board);
}

void getNextActionFromCli(Action* action) {
    // Reads the input command
    char* input = NULL;
    size_t ss;
    ssize_t lineSize = getline(&input, &ss, stdin);
    input[lineSize - 1] = '\0';

    // Check the known commands
    if(!strcmp(input, "start")) {
        action->type = START;
        return;
    }
    if(!strcmp(input, "reset")) {
        action->type = RESET;
        return;
    }
    if(!strcmp(input, "exit")) {
        action->type = EXIT;
        return;
    }

    // Check more complex commands
    regex_t regex;
    // Reveal
    int a = regcomp(&regex, "reveal [0-9]+,[0-9]+", REG_EXTENDED | REG_NOSUB);
    if((regexec(&regex, input, 0, (regmatch_t*)NULL, 0)) == 0) {
        getXY(input, action->coordinates, action->coordinates + 1);
        action->type = REVEAL;
        return;
    }
    // Remove flag
    int c =
        regcomp(&regex, "remove_flag [0-9]+,[0-9]+", REG_EXTENDED | REG_NOSUB);
    if((regexec(&regex, input, 0, (regmatch_t*)NULL, 0)) == 0) {
        getXY(input, action->coordinates, action->coordinates + 1);
        action->type = REMOVE_FLAG;
        return;
    }
    // Flag
    int b = regcomp(&regex, "flag [0-9]+,[0-9]+", REG_EXTENDED | REG_NOSUB);
    if((regexec(&regex, input, 0, (regmatch_t*)NULL, 0)) == 0) {
        getXY(input, action->coordinates, action->coordinates + 1);
        action->type = SET_FLAG;
        return;
    }

    // No valid action was found, then this action is invalidated
    action->type = INVALID;
}

int actionIsValid(Client* client, Action* action) {
    // Make sure to start the game
    if(action->type == START) {
        client->started = 1;
        return 1;
    }
    // If the game has not started, then no action is valid other then START
    if(!client->started) return 0;

    int x = action->coordinates[0], y = action->coordinates[1];
    switch(action->type) {
        case REVEAL:
            // If the coordinate is outside the board
            if(!((0 <= x && x <= 3) && (0 <= y && y <= 3))) {
                printf("error: invalid cell\n");
                return 0;
            }
            // Trying to reveal an already revealed cell
            if(client->board[x][y] >= ZERO) {
                printf("error: cell already revealed\n");
                return 0;
            }
            break;
        case SET_FLAG:
            // Trying to put flag in a cell that already have flag
            if(client->board[x][y] == FLAG) {
                printf("error: cell already has a flag\n");
                return 0;
            }
            // Trying to flag an already revealed cell
            if(client->board[x][y] >= ZERO) {
                printf("error: cannot insert flag in revealed cell\n");
                return 0;
            }
            break;
        case INVALID: printf("error: command not found\n"); return 0;
    }
    return 1;
}

int addrParse(char* IP, char* portstr, struct sockaddr_storage* storage) {
    if(IP == NULL || portstr == NULL) return 1;

    // PORT PARSING
    uint16_t port = (uint16_t)atoi(portstr);
    // Not valid port number
    if(port == 0) return 1;

    // Network byte order - Host to network short
    port = htons(port);

    // IP PARSING
    struct in_addr inaddr4;  // 32-bit
    if(inet_pton(AF_INET, IP, &inaddr4)) {
        struct sockaddr_in* addr4 = (struct sockaddr_in*)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_port = port;
        addr4->sin_addr = inaddr4;
        return 0;
    }

    struct in6_addr inaddr6;  // 128-bit
    if(inet_pton(AF_INET6, IP, &inaddr6)) {
        struct sockaddr_in6* addr6 = (struct sockaddr_in6*)storage;
        addr6->sin6_family = AF_INET6;
        addr6->sin6_port = port;
        memcpy(&(addr6->sin6_addr), &inaddr6, sizeof(inaddr6));
        return 0;
    }

    return 1;
}

//=========== UTILS FUNCTIONS ==================================================
void getXY(char* str, int* x, int* y) {
    int len = strlen(str), i;
    for(i = 0; i < len; i++) {
        if(str[i] == ',') break;
    }
    // Gets Y
    *y = atoi(str + i + 1);
    str[i] = '\0';

    // Search for the X
    while(--i >= 0) {
        if(str[i] == ' ') {
            *x = atoi(str + i + 1);
            return;
        }
    }
}