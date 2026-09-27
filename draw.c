#include <stdbool.h>
#include <raylib.h>
#include "draw.h"

static void draw_cell(int x, int y, int cell_size_px);
static void draw_bordered_cell(int x, int y, int cell_size_px);
static void draw_vertical_line(int x, int height);
static void draw_horizontal_line(int y, int width);

void draw_grid(bool *grid, int width, int height, int cell_size_px)
{
    ClearBackground(WHITE);
    int i = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (grid[i])
            {
                draw_cell(x, y, cell_size_px);
            }
            i++;
        }
    }
}

void draw_grid_with_borders(bool *grid, int width, int height, int cell_size_px)
{
    ClearBackground(WHITE);
    int i = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (grid[i]) draw_bordered_cell(x, y, cell_size_px);
            i++;
        }
    }
    for (int y = 0; y < height; y++)
    {
        draw_horizontal_line(y + y * cell_size_px, width + width * cell_size_px);
    }
    draw_horizontal_line(height + height * cell_size_px, width + width * cell_size_px);
    for (int x = 0; x < width; x++)
    {
        draw_vertical_line(x + x * cell_size_px, height + height * cell_size_px);
    }
    draw_vertical_line(height + height * cell_size_px, width + width * cell_size_px);
}

static void draw_vertical_line(int x, int height)
{
    DrawRectangle(x, 0, 1, height, BLACK);
}

static void draw_horizontal_line(int y, int width)
{
    DrawRectangle(0, y, width, 1, BLACK);
}

static void draw_bordered_cell(int x, int y, int cell_size_px)
{
    int posx = 1 + (1 + cell_size_px) * x;
    int posy = 1 + (1 + cell_size_px) * y;
    DrawRectangle(posx, posy, cell_size_px, cell_size_px, BLACK);
}

static void draw_cell(int x, int y, int cell_size_px)
{
    DrawRectangle(x * cell_size_px, y * cell_size_px, cell_size_px, cell_size_px, BLACK);
}

