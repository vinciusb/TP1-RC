/**
 * @file MineSweeper.c
 * @author Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
 * @brief cabeçalho do campo minado - Redes de Computadores - UFMG
 * @version 1.0
 * @date 2023-09-19
 *
 */

#include <MineSweeper.h>
#include <sys/socket.h>

void createMineSweeper(MineSweeper* mine, char* inputFileName) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // Tries to open the input file
    FILE* file = fopen(inputFileName, "r");
    if(file == NULL) {
        printf("error: File doesn't exist.");
        exit(EXIT_FAILURE);
    }

    // Reads the input file and fill the game board
    int l = 0;
    while((read = getline(&line, &len, file)) != -1) {
        int start = 0, column = 0;

        // Iterates over the line
        for(int i = 0; i < read; i++) {
            // Gets the current number
            if(line[i] == ',' || line[i] == '\n') {
                line[i] = '\0';
                // Converts string to and board cell
                mine->answer[l][column] = atoi(line + start);
                // Sets new start of number
                start = i + 1;
                column++;
            }
        }
        // If it's the last line and has no '\n' in the end
        if(l == 3 && line[read - 1] != '\0')
            mine->answer[3][3] = atoi(line + start);

        l++;
    }

    fclose(file);
    if(line) free(line);

    // Creating the current state of the game (every cell ocult)
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) mine->current[i][j] = OCULT;
}

void destroyMineSweeper(MineSweeper* mine) { free(mine); }

void printMineSweeper(BOARD_CELL board[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            char c;
            // Casts the cell
            switch(board[i][j]) {
                case FLAG: c = '>'; break;
                case OCULT: c = '-'; break;
                case BOMB: c = '*'; break;
                default: c = board[i][j] + '0';
            }
            printf("%c", c);
            if(j < 3) printf(SPACING);
            else
                printf("\n");
        }
    }
}

int revealCoordinate(MineSweeper* mine, int x, int y) {
    // If the cell to be revealed is a bomb, then game over
    if(mine->answer[x][y] == BOMB) {
        // Copies the answer to the current board
        memcpy(mine->current, mine->answer, BOARD_SIZE);
        return 2;
    }
    // Reveals this cell
    mine->current[x][y] = mine->answer[x][y];

    int count = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            // If there are remaining cells to be revealed
            if(mine->answer[i][j] >= ZERO
               && mine->current[i][j] != mine->answer[i][j])
                return 0;

    // Else it's a win
    return 1;
}

void setFlagAt(BOARD_CELL board[4][4], int x, int y) { board[x][y] = FLAG; }

void removeFlagAt(BOARD_CELL board[4][4], int x, int y) {
    if(board[x][y] == FLAG) board[x][y] = OCULT;
}

void resetBoard(BOARD_CELL board[4][4]) {
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) board[i][j] = OCULT;
}