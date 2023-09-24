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
#include <string.h>

#define SPACING "\t\t"
#define BOARD_SIZE sizeof(BOARD_CELL[4][4])

/**
 * @brief Enum for each type of cell in the mine sweeper board.
 *
 */
typedef enum {
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

/**
 * @brief Function that prints a minesweeper board.
 *
 * @param board The board to be printed.
 */
void printMineSweeper(BOARD_CELL board[4][4]);

/**
 * @brief Function that reveals a game coordinate and returns the status of this
 * movement.
 *
 * @param mine
 * @param x
 * @param y
 * @return int 0 Revealed ok, 1 win, 2 game over
 */
int revealCoordinate(MineSweeper* mine, int x, int y);

/**
 * @brief Set a flag at the coordinate.
 *
 * @param board
 * @param x
 * @param y
 */
void setFlagAt(BOARD_CELL board[4][4], int x, int y);

/**
 * @brief Removes a flag from this board cell.
 *
 * @param board
 * @param x
 * @param y
 */
void removeFlagAt(BOARD_CELL board[4][4], int x, int y);

/**
 * @brief Resets the board to ocult cells.
 *
 * @param board
 */
void resetBoard(BOARD_CELL board[4][4]);