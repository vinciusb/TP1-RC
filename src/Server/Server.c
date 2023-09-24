/**
 * @file Server.c
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief implementação do server - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <Server.h>

void createServer(Server* server, char* IPvx, char* port, char* inputFilePath) {
    // Init the mine sweeper game
    server->game = (MineSweeper*)malloc(sizeof(MineSweeper));
    createMineSweeper(server->game, inputFilePath);

    // Parse the address
    if(addrParse(IPvx, port, &server->storage))
        logError("error: Failed at address parsing.");

    // Creates the socket
    server->socket = socket(server->storage.ss_family, SOCK_STREAM, 0);
    if(server->socket == -1) logError("error: Socket not created.");

    // Binds the port to the socket
    server->addr = (struct sockaddr*)&server->storage;
    if(bind(server->socket, server->addr, sizeof(server->storage)))
        logError("error: binding.");

    // Start to listen and allow 10 pendent requests
    if(listen(server->socket, 10)) logError("error: listening.");

    // Logs the answer in the terminal
    printMineSweeper(server->game->answer);

    // Cleans the server communication buffer
    memset(server->buffer, 0, ACTION_SIZE);
}

void destroyServer(Server* server) {
    destroyMineSweeper(server->game);
    close(server->socket);
}

void run(Server* server) {
    // Accept the connection with a new client and gets the socket to
    // communicate with him
    struct sockaddr_storage clientStorage;
    struct sockaddr* clientAddr = (struct sockaddr*)&clientStorage;
    socklen_t clientAddrLen = sizeof(clientStorage);

    Action* action = (Action*)malloc(sizeof(Action));

    // Infinite loop for each client that connects to the server
    while(1) {
        // Resets the game board
        resetBoard(server->game->current);
        // Waits for the client to connect and accept him
        server->clientSocket =
            accept(server->socket, clientAddr, &clientAddrLen);
        if(server->clientSocket == -1)
            logError("error: Failed to accept client.");

        // Server infinite loop
        while(1) {
            // Receives message from client socket
            if(recvAction(server->clientSocket,
                          action,
                          server->buffer,
                          ACTION_SIZE,
                          0))
                logError("error: Didn't receive all the bytes");

            // Process this action
            processAction(server, action);
            // If the client quited the game
            if(action->type == EXIT) break;

            // Send message back to client
            if(sendAction(server->clientSocket,
                          action,
                          server->buffer,
                          ACTION_SIZE,
                          0))
                logError("error: Didn't send all the bytes");
        }
        // Close the communication with the client
        close(server->clientSocket);
    }

    free(action);
}

void processAction(Server* server, Action* action) {
    switch(action->type) {
        // Sends the first state of the game
        case START:
            // Client successfully connected
            printf("client connected\n");
            action->type = STATE;
            memcpy(action->board, server->game->current, BOARD_SIZE);
            break;

        case REVEAL:
            // Reveals a coordinate
            int gameStatus = revealCoordinate(
                server->game, action->coordinates[0], action->coordinates[1]);

            if(gameStatus == 0) action->type = STATE;
            else if(gameStatus == 1)
                action->type = WIN;
            else
                action->type = GAME_OVER;

            memcpy(action->board, server->game->current, BOARD_SIZE);
            break;
        case SET_FLAG:
            setFlagAt(server->game->current,
                      action->coordinates[0],
                      action->coordinates[1]);

            action->type = STATE;
            memcpy(action->board, server->game->current, BOARD_SIZE);
            break;
        case REMOVE_FLAG:
            removeFlagAt(server->game->current,
                         action->coordinates[0],
                         action->coordinates[1]);

            action->type = STATE;
            memcpy(action->board, server->game->current, BOARD_SIZE);
            break;
        case RESET:
            printf("starting new game\n");

            resetBoard(server->game->current);
            action->type = STATE;
            memcpy(action->board, server->game->current, BOARD_SIZE);
            break;
        case EXIT: printf("client disconnected\n"); break;
        case GAME_OVER:
            /* code */
            break;
    }
}

int addrParse(char* IPvx, char* portstr, struct sockaddr_storage* storage) {
    if(IPvx == NULL || portstr == NULL) return 1;

    // PORT PARSING
    uint16_t port = (uint16_t)atoi(portstr);
    // Not valid port number
    if(port == 0) return 1;

    // Network byte order - Host to network short
    port = htons(port);

    memset(storage, 0, sizeof(storage));

    // Is IPv4
    if(strcmp(IPvx, "v4") == 0) {
        struct sockaddr_in* addr4 = (struct sockaddr_in*)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_port = port;
        addr4->sin_addr.s_addr =
            INADDR_ANY;  // Any address that the pc has at his network interface
        return 0;
    }
    // IPv6
    else if(strcmp(IPvx, "v6") == 0) {
        struct sockaddr_in6* addr6 = (struct sockaddr_in6*)storage;
        addr6->sin6_family = AF_INET6;
        addr6->sin6_port = port;
        addr6->sin6_addr = in6addr_any;
        return 0;
    }
    return 1;
}