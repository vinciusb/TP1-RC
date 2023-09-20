/**
 * @file Server.c
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief cabeçalho do server - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <Server.h>
#include <sys/socket.h>

void createServer(Server* server, char* IPvx, char* port, char* inputFilePath) {
    // Init the mine sweeper game
    MineSweeper* game = (MineSweeper*)malloc(sizeof(MineSweeper));
    createMineSweeper(game, inputFilePath);
}

void destroyServer(Server* server) { destroyMineSweeper(server->game); }

void run(Server* server) {}