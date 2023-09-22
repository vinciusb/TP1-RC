/**
 * @file main.c
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief main do server - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <Server.h>
#include <stdio.h>
#include <unistd.h>

typedef struct ArgsDesc {
    char* IPvx;
    char* port;
    char* inputFilePath;
} ArgsDesc;

//----------Protótipos de funções-----------------------------------------------
/**
 * @brief Function that extracts and describe the main program args.
 *
 * @param argc
 * @param argv
 * @param args
 */
int describeArgs(int argc, char** argv, ArgsDesc* args);

int main(int argc, char** argv) {
    ArgsDesc args;
    if(describeArgs(argc, argv, &args)) printf("error: Invalid argument.");

    // Creates the server side
    Server server;
    createServer(&server, args.IPvx, args.port, args.inputFilePath);

    // Runs the server
    run(&server);

    // Destroies the server
    destroyServer(&server);

    return 0;
}

int describeArgs(int argc, char** argv, ArgsDesc* args) {
    args->IPvx = argv[1];
    args->port = argv[2];
    args->inputFilePath = argv[4];

    return 0;
}