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
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "generators/sudoku.h"
#include "parsers/sudoku.h"

void sudoku_parse(char *input) {
    const char separator[2]     = " ";
    uint16_t   loaded_from_file = 0;
    char *     token_data       = NULL;
    char *     data             = NULL;
    size_t     data_len         = 0;

    if (file_exists(input)) {
        FILE *f = fopen(input, "rt");
        readall(f, &data, &data_len);
        fclose(f);
        loaded_from_file = 1;
    } else {
        data     = input;
        data_len = strlen(data);
    }

    char *token = strtok_r(data, separator, &token_data);

    while (token != NULL) {
        uint16_t values[4];

        for (int i = 0; i < 4; i++) {
            do {
                values[i] = atoi(token);
                token     = strtok_r(NULL, separator, &token_data);
            } while (token != NULL && values[i] == 0);

            if (token == NULL) {
                break;
            }
        }

        if (token == NULL) {
            break;
        }

        uint16_t position = values[0] - 1;
        uint16_t row      = position % ROW_LENGTH;
        uint16_t column   = position / ROW_LENGTH;
        uint16_t value    = (values[1] - 1) % ROW_LENGTH + 1;

        printf("%2d %2d %2d\n", row, column, value);

        assert(row < ROW_LENGTH);
        assert(column < COLUMN_LENGTH);

        assert(value > 0);
        assert(value <= MAX_VALUE);
    }

    if (loaded_from_file) {
        free(data);
    }
}
