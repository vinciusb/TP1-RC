/**
 * @file main.c
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief main do client - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <Client.h>
#include <stdio.h>
#include <unistd.h>

typedef struct ArgsDesc {
    char* IP;
    char* port;
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
    Client client;
    createClient(&client, args.IP, args.port);

    // Runs the server
    run(&client);

    // Destroies the server
    destroyClient(&client);

    return 0;
}

int describeArgs(int argc, char** argv, ArgsDesc* args) {
    args->IP = argv[1];
    args->port = argv[2];

    return 0;
}