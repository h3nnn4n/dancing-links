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

#ifndef __GENERATORS_SUDOKU
#define __GENERATORS_SUDOKU

#include <stdint.h>
#include <stdio.h>

// TODO(h3nnn4n) These shouldnt be hardcoded. They could be either infered from
// the input size, or taken from the cli. People usually only care about the
// 9x9 sudoku, so we should be fine for a while. As a stop-gap solution we are
// setting it at compile time.
#if !defined(GRID_SIZE)
#define GRID_SIZE 3
#define N_GRIDS   3
#endif

#define BLOCK_SIZE    (GRID_SIZE * GRID_SIZE)
#define ROW_LENGTH    (GRID_SIZE * N_GRIDS)
#define COLUMN_LENGTH (GRID_SIZE * N_GRIDS)
#define N_CELLS       (GRID_SIZE * GRID_SIZE * N_GRIDS * N_GRIDS)
#define MAX_VALUE     (GRID_SIZE * GRID_SIZE)

void       sudoku_generator(FILE *sudoku_output, char *sudoku_input);
void       build_cover_set(FILE *f, uint16_t row, uint16_t column, uint16_t value);
uint16_t   global_to_in_block_position(uint16_t row, uint16_t column, uint16_t value);
uint16_t **load_and_parse_sudoku(char *input, uint16_t *n_clues);
void       unload_clues(uint16_t **clues, uint16_t n_clues);

#endif /* end of include guard */
