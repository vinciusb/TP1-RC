#pragma once

/**
 * @file MineSweeper.h
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief cabeçalho do campo minado - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief
 *
 */
typedef enum int8_t {
    FLAG = -3,
    OCULT,
    BOMB,
    ZERO = 0,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT
} BOARD_CELL;

/**
 * @brief This struct represents a playable mine sweeper game.
 *
 */
typedef struct MineSweeper {
    /**
     * @brief The answer for the mine sweeper.
     *
     */
    BOARD_CELL answer[4][4];
    /**
     * @brief The current state of the game.
     *
     */
    BOARD_CELL current[4][4];
} MineSweeper;

/**
 * @brief Constructor for MineSweeper.
 *
 * @param mine The MineSweeper struct.
 * @param inputFileName The input file path with the answer matrix.
 */
void createMineSweeper(MineSweeper* mine, char* inputFileName);

/**
 * @brief Destructor for MineSweeper.
 *
 * @param server The game to be destructed.
 */
void destroyMineSweeper(MineSweeper* mine);
