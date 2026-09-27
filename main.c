#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "conway.h"
#include "draw.h"


int main(int argc, char *argv[])
{
    Game game;
    bool *grid;

    int game_width;
    int game_height;
    int cell_size_px = 50;

    if (argc == 1)
    {
        game_width = 10;
        game_height = 10;
        grid = calloc(game_width * game_height, sizeof(bool));
        if (!grid)
        {
            fprintf(stderr, "Error initiliasing grid.\n");
            exit(EXIT_FAILURE);
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
    else if (argc == 2 || argc == 3)
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

        if (argc == 3)
        {
            cell_size_px = atoi(argv[2]);
        }
    }

    int screen_width = 1 + game_width + game_width * cell_size_px;
    int screen_height = 1 + game_height + game_height * cell_size_px;

    InitWindow(screen_width, screen_height, "Conway's Game of Life");

    SetTargetFPS(10);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(WHITE);
            draw_grid_with_borders(grid, game_width, game_height, cell_size_px);
        }
        EndDrawing();
        next_frame(game);
    }

    free(grid);
    destroy_game(game);
    return 0;
}

