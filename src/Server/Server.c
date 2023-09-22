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
}

void destroyServer(Server* server) {
    destroyMineSweeper(server->game);
    close(server->socket);
}

void run(Server* server) {
    // Logs the answer in the terminal
    printMineSweeper(server->game->answer);
    char buffer[ACTION_SIZE];
    memset(buffer, 0, ACTION_SIZE);

    // Server infinite loop
    while(1) {
        // Accept the connection with the client and gets the socket to
        // communicate with him
        struct sockaddr_storage clientStorage;
        struct sockaddr* clientAddr = (struct sockaddr*)&clientStorage;
        int clientSocket =
            accept(server->socket, clientAddr, sizeof(clientStorage));
        if(clientSocket == -1) logError("error: Failed to accept client.");

        // Receives message from client socket
        size_t recvBytes = recv(clientSocket, buffer, ACTION_SIZE, 0);
        Action* action = (Action*)buffer;
        logAction(action);

        // Sends message to client
        sprintf(buffer, "oioi");
        size_t sentBytes = send(clientSocket, buffer, strlen(buffer) + 1, 0);
        if(sentBytes != strlen(buffer) + 1)
            logError("error: Didn't send all the bytes");

        // Closes the connection
        close(clientSocket);
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