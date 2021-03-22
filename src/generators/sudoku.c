/*
 * Copyright (C) 2021  h3nnn4n, aka Renan S. Silva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "generators/sudoku.h"

void sudoku_generator(char *sudoku_input) {
    FILE *f = fopen("sudoku_test.dat", "wt");

    char buffer[256];
    // This is a placeholder string that we add when creating the file because
    // it is easier to replace at the beggining of a file than to add.
    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    snprintf(buffer, sizeof(buffer), "xxxxxxxxxxxxxxxxxxxx\n");
    fwrite(buffer, strlen(buffer), 1, f);

    uint16_t   n_clues   = 0;
    uint16_t **clues     = load_and_parse_sudoku(sudoku_input, &n_clues);
    uint16_t   grid_size = 2;
    uint16_t   n_grids   = 2;

    uint16_t n_columns = N_CELLS * 4;
    uint16_t n_rows    = 0;
    uint16_t n_n       = N_CELLS;

    /*printf("making coverset with clues\n");*/

    for (int i = 0; i < n_clues; i++) {
        uint16_t row    = clues[i][0];
        uint16_t column = clues[i][1];
        uint16_t value  = clues[i][2];

        /*printf("%2d %d %d %d\n", i, row, column, value);*/
        build_cover_set(f, row, column, value);
        n_rows += 1;
    }

    for (int value_i = 1; value_i <= grid_size * grid_size; value_i++) {
        for (int row_i = 0; row_i < grid_size * n_grids; row_i++) {
            for (int column_i = 0; column_i < grid_size * n_grids; column_i++) {
                int skip = 0;

                for (int i = 0; i < n_clues; i++) {
                    uint16_t row    = clues[i][0];
                    uint16_t column = clues[i][1];
                    uint16_t value  = clues[i][2];

                    if (row == row_i && column == column_i && value == value_i) {
                        skip = 1;
                        break;
                    }
                }

                if (skip)
                    continue;

                build_cover_set(f, row_i, column_i, value_i);
                n_rows += 1;
            }
        }
    }

    /*printf("\n");*/

    rewind(f);
    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    snprintf(buffer, sizeof(buffer), "%d %d %d", n_columns, n_rows, n_n);
    size_t buf_len = strlen(buffer);

    for (uint16_t i = 0; i <= 20 - buf_len; i++) {
        buffer[i + buf_len] = ' ';
    }
    buffer[20] = '\0';

    fwrite(buffer, strlen(buffer), 1, f);

    unload_clues(clues, n_clues);

    fclose(f);
}

void build_cover_set(FILE *f, uint16_t row, uint16_t column, uint16_t value) {
    /*printf("%d %d %c\n", row, column, value);*/
    assert(value > 0);
    assert(value <= MAX_VALUE);

    int cell_written = 0;
    // Position Constrain
    // Each cell has to be occupied by exactly one number
    uint16_t position = column * ROW_LENGTH + row;
    for (int row_i = 0; row_i < ROW_LENGTH; row_i++) {
        for (int col_i = 0; col_i < ROW_LENGTH; col_i++) {
            if (position == col_i * ROW_LENGTH + row_i) {
                fprintf(f, "1 ");
                cell_written += 1;
            } else {
                fprintf(f, "0 ");
            }
        }
    }

    fflush(f);
    assert(cell_written == 1);

    fprintf(f, "  ");

    // Row constraint
    // Each row has to have exactly one of each number

    // Build an index where the row and the value are the coordinates
    // Note that row and column are 0 indexed, value is not
    uint16_t row_coordinate = row * (ROW_LENGTH) + value - 1;
    for (int row_i = 0; row_i < ROW_LENGTH; row_i++) {
        for (int value_i = 0; value_i < ROW_LENGTH; value_i++) {
            if (row_coordinate == row_i * (ROW_LENGTH) + value_i) {
                fprintf(f, "1 ");
                cell_written += 1;
            } else {
                fprintf(f, "0 ");
            }
        }
    }

    fflush(f);
    assert(cell_written == 2);

    fprintf(f, "  ");

    // Column Constraint
    // Each column has to have exactly one of each number

    // Build an index where the column and the value are the coordinates
    // Note that row and column are 0 indexed, value is not
    uint16_t col_coordinate = column * (ROW_LENGTH) + value - 1;
    for (int col_i = 0; col_i < ROW_LENGTH; col_i++) {
        for (int value_i = 0; value_i < ROW_LENGTH; value_i++) {
            if (col_coordinate == col_i * (ROW_LENGTH) + value_i) {
                fprintf(f, "1 ");
                cell_written += 1;
            } else {
                fprintf(f, "0 ");
            }
        }
    }

    fflush(f);
    assert(cell_written == 3);

    fprintf(f, "  ");

    // Block Constraint
    // Each block has to have exactly one of each number
    uint16_t block_coordinate = global_to_in_block_position(row, column, value);
    for (int block_i = 0; block_i < ROW_LENGTH; block_i++) {
        for (int value_i = 0; value_i < ROW_LENGTH; value_i++) {
            if (block_coordinate == block_i * (ROW_LENGTH) + value_i) {
                fprintf(f, "1 ");
                cell_written += 1;
            } else {
                fprintf(f, "0 ");
            }
        }
    }

    fflush(f);
    assert(cell_written == 4);

    fprintf(f, "\n");
}

uint16_t global_to_in_block_position(uint16_t row, uint16_t column, uint16_t value) {
    // Figure out which block we are dealing with
    uint16_t block_row    = row / GRID_SIZE;
    uint16_t block_col    = column / GRID_SIZE;
    uint16_t block_number = block_col * N_GRIDS + block_row;

    // Figure out where in the block we are
    // uint16_t in_block_row      = row % grid_size;
    // uint16_t in_block_col      = column % grid_size;
    // uint16_t in_block_position = in_block_col * (grid_size) + in_block_row;

    // Build a global coordinate that combines the block number with the value inside
    // Note that row and column are 0 indexed, value is not
    uint16_t block_coordinate = block_number * ROW_LENGTH + value - 1;
    return block_coordinate;
}

uint16_t **load_and_parse_sudoku(char *input, uint16_t *n_clues) {
    uint16_t loaded_from_file = 0;
    char *   data             = NULL;
    size_t   data_len         = 0;
    uint16_t clue_count       = 0;

    // A sudoku wont ever have more than N_CELLS clues
    uint16_t **clues = (uint16_t **)malloc(sizeof(uint16_t *) * N_CELLS);

    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    memset(clues, 0, N_CELLS);

    if (file_exists(input)) {
        FILE *f = fopen(input, "rt");
        readall(f, &data, &data_len);
        fclose(f);
        loaded_from_file = 1;
    } else {
        data     = input;
        data_len = strlen(data);
    }

    /*printf("parsing %s\n", data);*/

    for (size_t i = 0; i < data_len; i++) {
        char value = data[i];

        // FIXME(h3nnn4n): Skip whitespace
        // FIXME(h3nnn4n): The '9' should use MAX_VALUE as a char
        // Not a clue. It is an empty cell
        if (value < '1' || value > '9') {
            continue;
        }

        clues[clue_count]    = (uint16_t *)malloc(sizeof(uint16_t) * 3);
        uint16_t row         = i / MAX_VALUE;
        uint16_t col         = i % MAX_VALUE;
        clues[clue_count][0] = row;
        clues[clue_count][1] = col;
        clues[clue_count][2] = value - '0';

        /*printf("%2d %d %d %d\n", clue_count, row, col, clues[clue_count][2] [> the parsed value <]);*/

        clue_count++;
    }

    *n_clues = clue_count;

    /*printf("finished parsing\n");*/

    if (loaded_from_file) {
        free(data);
    }

    return clues;
}

void unload_clues(uint16_t **clues, __attribute__((unused)) uint16_t n_clues) {
    for (int i = 0; i < N_CELLS; i++) {
        if (clues[i] == NULL) {
            continue;
        }

        free(clues[i]);
    }

    free(clues);
}
