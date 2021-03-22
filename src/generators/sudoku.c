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
#include <string.h>

#include "generators/sudoku.h"

void sudoku_generator() {
    FILE *f = fopen("sudoku_test.dat", "wt");

    char buffer[256];
    // This is a placeholder string that we add when creating the file because
    // it is easier to replace at the beggining of a file than to add.
    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    snprintf(buffer, sizeof(buffer), "xxxxxxxxxxxxxxxxxxxx\n");
    fwrite(buffer, strlen(buffer), 1, f);

    uint16_t clues[4][3] = {0};
    uint16_t grid_size   = 2;
    uint16_t n_grids     = 2;

    uint16_t n_columns = (grid_size * grid_size * n_grids * n_grids) * 4;
    uint16_t n_rows    = 0;
    uint16_t n_n       = grid_size * grid_size * n_grids * n_grids;

    clues[0][0] = 0;
    clues[0][1] = 1;
    clues[0][2] = 1;

    clues[1][0] = 1;
    clues[1][1] = 2;
    clues[1][2] = 2;

    clues[2][0] = 2;
    clues[2][1] = 0;
    clues[2][2] = 3;

    clues[3][0] = 3;
    clues[3][1] = 3;
    clues[3][2] = 4;

    for (int i = 0; i < 4; i++) {
        uint16_t row    = clues[i][0];
        uint16_t column = clues[i][1];
        uint16_t value  = clues[i][2];

        build_cover_set(f, row, column, value, grid_size, n_grids);
        n_rows += 1;
    }

    for (int value_i = 1; value_i <= grid_size * grid_size; value_i++) {
        for (int row_i = 0; row_i < grid_size * n_grids; row_i++) {
            for (int column_i = 0; column_i < grid_size * n_grids; column_i++) {
                int skip = 0;

                for (int i = 0; i < 4; i++) {
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

                build_cover_set(f, row_i, column_i, value_i, grid_size, n_grids);
                n_rows += 1;
            }
        }
    }

    printf("\n");

    rewind(f);
    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    snprintf(buffer, sizeof(buffer), "%d %d %d", n_columns, n_rows, n_n);
    size_t buf_len = strlen(buffer);

    for (uint16_t i = 0; i <= 20 - buf_len; i++) {
        buffer[i + buf_len] = ' ';
    }
    buffer[20] = '\0';

    fwrite(buffer, strlen(buffer), 1, f);

    fclose(f);
}

void build_cover_set(FILE *f, uint16_t row, uint16_t column, uint16_t value, uint16_t grid_size, uint16_t n_grids) {
    int cell_written = 0;
    // Position Constrain
    // Each cell has to be occupied by exactly one number
    uint16_t position = column * (grid_size * n_grids) + row;
    for (int row_i = 0; row_i < grid_size * n_grids; row_i++) {
        for (int col_i = 0; col_i < grid_size * n_grids; col_i++) {
            if (position == col_i * (grid_size * n_grids) + row_i) {
                fprintf(f, "1 ");
                cell_written += 1;
            } else {
                fprintf(f, "0 ");
            }
        }
    }

    assert(cell_written == 1);

    fprintf(f, "  ");

    // Row constraint
    // Each row has to have exactly one of each number

    // Build an index where the row and the value are the coordinates
    // Note that row and column are 0 indexed, value is not
    uint16_t row_coordinate = row * (grid_size * n_grids) + value - 1;
    for (int row_i = 0; row_i < grid_size * n_grids; row_i++) {
        for (int value_i = 0; value_i < grid_size * n_grids; value_i++) {
            if (row_coordinate == row_i * (grid_size * n_grids) + value_i) {
                fprintf(f, "1 ");
                cell_written += 1;
            } else {
                fprintf(f, "0 ");
            }
        }
    }

    assert(cell_written == 2);

    fprintf(f, "  ");

    // Column Constraint
    // Each column has to have exactly one of each number

    // Build an index where the column and the value are the coordinates
    // Note that row and column are 0 indexed, value is not
    uint16_t col_coordinate = column * (grid_size * n_grids) + value - 1;
    for (int col_i = 0; col_i < grid_size * n_grids; col_i++) {
        for (int value_i = 0; value_i < grid_size * n_grids; value_i++) {
            if (col_coordinate == col_i * (grid_size * n_grids) + value_i) {
                fprintf(f, "1 ");
                cell_written += 1;
            } else {
                fprintf(f, "0 ");
            }
        }
    }

    assert(cell_written == 3);

    fprintf(f, "  ");

    // Block Constraint
    // Each block has to have exactly one of each number
    uint16_t block_coordinate = global_to_in_block_position(row, column, value, grid_size, n_grids);
    for (int block_i = 0; block_i < grid_size * n_grids; block_i++) {
        for (int value_i = 0; value_i < grid_size * n_grids; value_i++) {
            if (block_coordinate == block_i * (grid_size * n_grids) + value_i) {
                fprintf(f, "1 ");
                cell_written += 1;
            } else {
                fprintf(f, "0 ");
            }
        }
    }

    assert(cell_written == 4);

    fprintf(f, "\n");
}

uint16_t global_to_in_block_position(uint16_t row, uint16_t column, uint16_t value, uint16_t grid_size,
                                     uint16_t n_grids) {
    // Figure out which block we are dealing with
    uint16_t block_row    = row / grid_size;
    uint16_t block_col    = column / grid_size;
    uint16_t block_number = block_col * n_grids + block_row;

    // Figure out where in the block we are
    // uint16_t in_block_row      = row % grid_size;
    // uint16_t in_block_col      = column % grid_size;
    // uint16_t in_block_position = in_block_col * (grid_size) + in_block_row;

    // Build a global coordinate that combines the block number with the value inside
    // Note that row and column are 0 indexed, value is not
    uint16_t block_coordinate = block_number * (grid_size * grid_size) + value - 1;
    return block_coordinate;
}
