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
    struct sockaddr_storage storage;
    struct sockaddr* clientAddr;
    /**
     * @brief
     *
     */
    int isIPv6;
    /**
     * @brief
     *
     */
    int port;
    /**
     * @brief The socket ID.
     *
     */
    int socket;
    MineSweeper* game;
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