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
    // Allocates the mine sweeper game
    client->game = (MineSweeper*)malloc(sizeof(MineSweeper));

    // Parses the IP address
    if(addrParse(IP, port, &client->storage))
        logError("error: Failed at IP parsing.");
    client->addr = (struct sockaddr*)&client->storage;

    // Creates the socket
    client->socket = socket(client->storage.ss_family, SOCK_STREAM, 0);
    if(client->socket == -1) logError("error: Socket not created.");

    // Connects to the server
    if(connect(client->socket, &client->addr, sizeof(client->storage)))
        logError("error: Connect failed.");
}

void destroyClient(Client* client) {
    destroyMineSweeper(client->game);
    close(client->socket);
}

void run(Client* client) {
    int shouldContinue = 1;
    // Client infinite loop
    while(shouldContinue) {
        int x, y;
        ActionType action = getNextActionFromCli(&x, &y);

        // Execute the action
        switch(action) {
            case START: break;
            case REVEAL: break;
            case SET_FLAG: break;
            case REMOVE_FLAG:
                // client->game.removeFlag();
                break;
            case RESET: break;
            case EXIT: shouldContinue = 0; break;
            case INVALID: printf("error: command not found\n"); break;
        }
    }
}

ActionType getNextActionFromCli(int* x, int* y) {
    // Reads the input command
    char* input = NULL;
    size_t ss;
    ssize_t lineSize = getline(&input, &ss, stdin);
    input[lineSize - 1] = '\0';

    // Check the known commands
    if(!strcmp(input, "start")) return START;
    if(!strcmp(input, "reset")) return RESET;
    if(!strcmp(input, "exit")) return EXIT;

    // Check more complex commands
    regex_t regex;
    // Reveal
    int a = regcomp(&regex, "reveal [0-9]+,[0-9]+", REG_EXTENDED | REG_NOSUB);
    if((regexec(&regex, input, 0, (regmatch_t*)NULL, 0)) == 0) {
        getXY(input, x, y);
        return REVEAL;
    }
    // Remove flag
    int c =
        regcomp(&regex, "remove_flag [0-9]+,[0-9]+", REG_EXTENDED | REG_NOSUB);
    if((regexec(&regex, input, 0, (regmatch_t*)NULL, 0)) == 0) {
        getXY(input, x, y);
        return REMOVE_FLAG;
    }
    // Flag
    int b = regcomp(&regex, "flag [0-9]+,[0-9]+", REG_EXTENDED | REG_NOSUB);
    if((regexec(&regex, input, 0, (regmatch_t*)NULL, 0)) == 0) {
        getXY(input, x, y);
        return SET_FLAG;
    }

    // No valid action was found, then this action is invalidated
    return INVALID;
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