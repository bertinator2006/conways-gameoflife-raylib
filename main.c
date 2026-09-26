#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "conway.h"

#define CELL_SIZE_PX 10

static void draw_grid(bool *grid, int width, int height);
static inline void draw_cell(int x, int y);

int main(void)
{
    const int game_width = 80;
    const int game_height = 80;

    const int screen_width = game_width * CELL_SIZE_PX;
    const int screen_height = game_height * CELL_SIZE_PX;

    InitWindow(screen_width, screen_height, "Conway's Game of Life");

    bool *grid = calloc(game_width * game_height, sizeof(bool));
    if (!grid)
    {
        fprintf(stderr, "Error initiliasing grid.\n");
        return 1;
    }

    grid[83] = true;
    grid[164] = true;
    grid[242] = true;
    grid[243] = true;
    grid[244] = true;

    Game game = init_game(game_width, game_height, grid);
    if (!game)
    {
        fprintf(stderr, "Error initiallising game.\n");
        return 1;
    }

    SetTargetFPS(10);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(WHITE);
            draw_grid(grid, game_width, game_height);
        }
        EndDrawing();
        next_frame(game);
    }

    return 0;
}

static void draw_grid(bool *grid, int width, int height)
{
    ClearBackground(WHITE);
    int i = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (grid[i])
            {
                draw_cell(x, y);
            }
            i++;
        }
    }
}

static inline void draw_cell(int x, int y)
{
    DrawRectangle(x * CELL_SIZE_PX, y * CELL_SIZE_PX, CELL_SIZE_PX, CELL_SIZE_PX, BLACK);
}


