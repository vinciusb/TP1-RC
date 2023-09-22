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

    // Define protocol infos
    // TODO: Define server->storage; aqui
    server->isIPv6 = strcmp(IPvx, "v4");
    server->port = atoi(port);

    // Creates the socket
    server->socket =
        socket(server->isIPv6 ? AF_INET6 : AF_INET, SOCK_STREAM, 0);
    if(server->socket == -1) logError("error: Socket not created.");

    // Binds the port to the socket
    server->clientAddr = &server->storage;
    if(bind(server->socket, server->clientAddr, sizeof(server->storage))) {
        logError("error: binding.");
    }

    // Start to liste
    if(listen(server->socket, 10)) {
        logError("error: listening.");
    }
}

void destroyServer(Server* server) {
    destroyMineSweeper(server->game);
    close(server->socket);
}

void run(Server* server) {
    // Server infinite loop
    while(1) {
        break;
    }
}