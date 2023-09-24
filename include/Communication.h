/**
 * @file Communication.h
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief cabeçalho da comunicação - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <MineSweeper.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ACTION_SIZE sizeof(Action)

/**
 * @brief
 *
 */
typedef enum {
    START = 0,
    REVEAL,
    SET_FLAG,
    STATE,
    REMOVE_FLAG,
    RESET,
    WIN,
    EXIT,
    GAME_OVER,
    INVALID,
} ActionType;

/**
 * @brief Struct that represents the action sent between both sides of the
 * communication.
 *
 */
typedef struct action {
    int type;
    int coordinates[2];
    int board[4][4];
} Action;

/**
 * @brief Logs and error message and aborts the program.
 *
 * @param str The error message.
 */
void logError(const char* str);

/**
 * @brief Log action.
 *
 */
void logAction(Action* action);

/**
 * @brief Sends the action.
 *
 * @param destSocket
 * @param action
 * @param buffer
 * @param size
 * @param flags
 *
 * @return int 0 in case of success and 1 otherwise.
 */
int sendAction(
    int destSocket, Action* action, char* buffer, size_t size, int flags);

/**
 * @brief Receives the action.
 *
 * @param originSocket
 * @param action
 * @param buffer
 * @param size
 * @param flags
 * @return int 0 in case of success and 1 otherwise.
 */
int recvAction(
    int originSocket, Action* action, char* buffer, size_t size, int flags);