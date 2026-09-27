#ifndef DRAW_H
#define DRAW_H

#include <stdbool.h>
#include "raylib.h"

// requires:
//     window_width = width * cell_size_px
//     window_height = height * cell_size_px
void draw_grid(bool *grid, int width, int height, int cell_size_px);

// requires:
//     window_width = 1 + width * (1 + cell_size_px)
//     window_height = 1 + height * (1 + cell_size_px)
void draw_grid_with_borders(bool *grid, int width, int height, int cell_size_px);

#endif

