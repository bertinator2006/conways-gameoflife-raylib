#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "conway.h"

#define CELL_SIZE_PX 10

static void draw_grid(bool *grid, int width, int height);
static inline void draw_cell(int x, int y);

int main(int argc, char *argv[])
{
    Game game;
    bool *grid;

    int game_width;
    int game_height;

    if (argc == 1)
    {
        game_width = 10;
        game_height = 10;
        grid = calloc(game_width * game_height, sizeof(bool));
        if (!grid)
        {
            fprintf(stderr, "Error initiliasing grid.\n");
            return 1;
        }

        grid[game_width + 1] = true;
        grid[2 * game_width + 2] = true;
        grid[3 * game_width] = true;
        grid[3 * game_width + 1] = true;
        grid[3 * game_width + 2] = true;

        game = init_game(game_width, game_height, grid);
        if (!game)
        {
            fprintf(stderr, "Error initiallising game.\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (argc == 2)
    {
        game = init_game_file(argv[1]);
        if (!game)
        {
            fprintf(stderr, "Error initiallising game.\n");
            exit(EXIT_FAILURE);
        }
        game_width = get_game_width(game);
        game_height = get_game_height(game);
        grid = get_game_grid(game);
    }

    int screen_width = game_width * CELL_SIZE_PX;
    int screen_height = game_height * CELL_SIZE_PX;

    InitWindow(screen_width, screen_height, "Conway's Game of Life");

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

    free(grid);
    destroy_game(game);
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

