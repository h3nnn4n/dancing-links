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

void     sudoku_generator();
void     build_cover_set(FILE *f, uint16_t row, uint16_t column, uint16_t value, uint16_t grid_size, uint16_t n_grids);
uint16_t global_to_in_block_position(uint16_t row, uint16_t column, uint16_t value, uint16_t grid_size,
                                     uint16_t n_grids);

#endif /* end of include guard */
