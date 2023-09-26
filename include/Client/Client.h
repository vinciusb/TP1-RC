#pragma once

/**
 * @file Client.h
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief cabeçalho do client - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <Communication.h>
#include <MineSweeper.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Struct that represents the client side of this server-client service.
 *
 */
typedef struct Client {
    /**
     * @brief
     *
     */
    struct sockaddr_storage storage;
    /**
     * @brief
     *
     */
    struct sockaddr* addr;
    /**
     * @brief The socket ID.
     *
     */
    int socket;
    /**
     * @brief The mine sweeper game board.
     *
     */
    BOARD_CELL board[4][4];
    /**
     * @brief The buffer for communication.
     *
     */
    char buffer[ACTION_SIZE];
    /**
     * @brief Flag that indicates if the game have already started.
     *
     */
    int started;
} Client;

/**
 * @brief Create a client object.
 *
 * @param client The Client struct.
 * @param IPvx The IP.
 * @param port The port used by the client.
 */
void createClient(Client* client, char* IP, char* port);

/**
 * @brief Destructor for client.
 *
 * @param client The client to be destructed.
 */
void destroyClient(Client* client);

/**
 * @brief Starts the client side.
 *
 * @param client The client to be started.
 */
void run(Client* client);

/**
 * @brief Get the next action from cli.
 *
 * @param action The action to be sent to the server.
 */
void getNextActionFromCli(Action* action);

/**
 * @brief Function that process an action and creates an action to be sent to
 * the server side.
 *
 * @param client The client to process the action.
 * @param action The action itself.
 */
void processAction(Client* client, Action* action);

/**
 * @brief Function that verifies if an action is valid. Prints in the prompt if
 * any well known error happend.
 *
 * @return int 1 if is valid, 0 otherwise.
 */
int actionIsValid(Client* client, Action* action);

/**
 * @brief Function that tries to parse the IP.
 *
 * @param IP The IP address.
 * @param port The port.
 * @param storage The address storage struct.
 * @return int Returns 1 if fails, 0 if the IP is IPv4 or IPv6.
 */
int addrParse(char* IP, char* port, struct sockaddr_storage* storage);
