#include <stdint.h>
#include <stdio.h>

#include "generators/sudoku.h"

void sudoku_generator() {
    FILE *f = fopen("sudoku_test.dat", "wt");

    uint16_t clues[4][3] = {0};
    uint16_t grid_size   = 2;
    uint16_t n_grids     = 2;

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

    /*clues[0][2] = 2;*/
    /*clues[1][2] = 2;*/
    /*clues[2][2] = 2;*/
    /*clues[3][2] = 2;*/

    for (int i = 0; i < 4; i++) {
        uint16_t row      = clues[i][0];
        uint16_t column   = clues[i][1];
        uint16_t value    = clues[i][2];
        uint16_t position = column * (grid_size * n_grids) + row;

        printf("%d - %d %d %d\n", i, row, column, value);

        // Position Constrain
        // Each cell has to be occupied by exactly one number
        for (int row_i = 0; row_i < grid_size * n_grids; row_i++) {
            for (int col_i = 0; col_i < grid_size * n_grids; col_i++) {
                if (position == col_i * (grid_size * n_grids) + row_i) {
                    fprintf(f, "1 ");
                } else {
                    fprintf(f, "0 ");
                }
            }
        }

        fprintf(f, "  ");

        // Row constraint
        // Each row has to have exactly one of each number

        // Build an index where the row and the value are the coordinates
        // Note that row and column are 0 indexed, value is not
        uint16_t row_coordinate = row * (grid_size * n_grids) + value - 1;
        for (int row_i = 0; row_i < grid_size * n_grids; row_i++) {
            for (int col_i = 0; col_i < grid_size * n_grids; col_i++) {
                if (row_coordinate == col_i * (grid_size * n_grids) + row_i) {
                    fprintf(f, "1 ");
                } else {
                    fprintf(f, "0 ");
                }
            }
        }

        fprintf(f, "  ");

        // Column Constraint
        // Each column has to have exactly one of each number

        // Build an index where the column and the value are the coordinates
        // Note that row and column are 0 indexed, value is not
        uint16_t col_coordinate = column * (grid_size * n_grids) + value - 1;
        for (int row_i = 0; row_i < grid_size * n_grids; row_i++) {
            for (int col_i = 0; col_i < grid_size * n_grids; col_i++) {
                if (col_coordinate == col_i * (grid_size * n_grids) + row_i) {
                    fprintf(f, "1 ");
                } else {
                    fprintf(f, "0 ");
                }
            }
        }

        fprintf(f, "\n");
    }

    printf("\n");

    fclose(f);
}
