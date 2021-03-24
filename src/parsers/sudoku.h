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

#ifndef SRC_PARSERS_SUDOKU_H_
#define SRC_PARSERS_SUDOKU_H_

#include "generators/sudoku.h"

void sudoku_parse(char *input);
void sudoku_check(char sudoku_solution[ROW_LENGTH][COLUMN_LENGTH]);

#endif /* SRC_PARSERS_SUDOKU_H_ */
