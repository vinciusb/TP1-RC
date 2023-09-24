#pragma once

/**
 * @file Server.h
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief cabeçalho do servidor - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <Communication.h>
#include <MineSweeper.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Struct that represents the server side of this server-client service.
 *
 */
typedef struct Server {
    /**
     * @brief The server address storage.
     *
     */
    struct sockaddr_storage storage;
    /**
     * @brief The server address.
     *
     */
    struct sockaddr* addr;
    /**
     * @brief The server socket ID.
     *
     */
    int socket;
    /**
     * @brief The socket to communicate with client.
     *
     */
    int clientSocket;
    /**
     * @brief The mine sweeper game board.
     *
     */
    MineSweeper* game;
    /**
     * @brief The buffer for communication.
     *
     */
    char buffer[ACTION_SIZE];
} Server;

/**
 * @brief Create a Server object.
 *
 * @param server The Server struct.
 * @param IPvx The IP version (v4 or v6).
 * @param port The port used by the server.
 * @param inputFilePath The input file path with the answer matrix.
 */
void createServer(Server* server, char* IPvx, char* port, char* inputFilePath);

/**
 * @brief Destructor for Server.
 *
 * @param server The server to be destructed.
 */
void destroyServer(Server* server);

/**
 * @brief Starts the server side.
 *
 * @param server The server to be started.
 */
void run(Server* server);

/**
 * @brief Function that process an action and creates an action to be sent to
 * the client side.
 *
 * @param server The server to process the action.
 * @param action The action itself.
 */
void processAction(Server* server, Action* action);

/**
 * @brief Function that tries to parse the server address.
 *
 * @param IPvx v4 or v6.
 * @param port The port.
 * @param storage The address storage struct.
 * @return int Returns 1 if fails, 0 otherwise.
 */
int addrParse(char* IPvx, char* port, struct sockaddr_storage* storage);