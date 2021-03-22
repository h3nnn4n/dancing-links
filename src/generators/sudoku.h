#ifndef __GENERATORS_SUDOKU
#define __GENERATORS_SUDOKU

#include <stdint.h>

void     sudoku_generator();
void     build_cover_set(FILE *f, uint16_t row, uint16_t column, uint16_t value, uint16_t grid_size, uint16_t n_grids);
uint16_t global_to_in_block_position(uint16_t row, uint16_t column, uint16_t value, uint16_t grid_size,
                                     uint16_t n_grids);

#endif /* end of include guard */
