#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "conway.h"
#include "draw.h"

static float average_float(float values[], int n);

int main(int argc, char *argv[])
{
    Game game;
    bool *grid;
    bool grid_freed = true;

    int game_width;
    int game_height;
    int cell_size_px = 50;

    if (argc == 1)
    {
        game_width = 10;
        game_height = 10;
        grid = calloc(game_width * game_height, sizeof(bool));
        grid_freed = false;

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
    else
    {
        fprintf(stderr, "Too many arguments.\n");
        exit(EXIT_FAILURE);
    }

    int screen_width = game_width * cell_size_px;
    int screen_height = game_height * cell_size_px;
    // int screen_width = 1 + game_width + game_width * cell_size_px;
    // int screen_height = 1 + game_height + game_height * cell_size_px;

    SetTraceLogLevel(LOG_NONE);
    InitWindow(screen_width, screen_height, "Conway's Game of Life");

    float frame_times[256];
    int frame_i = 0;
    char buffer[256];
    printf("Target FPS: ");
    fgets(buffer, 255, stdin);
    SetTargetFPS(atoi(buffer));

    while (!WindowShouldClose())
    {
        frame_times[frame_i] = GetFrameTime();
        frame_i = (frame_i + 1) % 256;

        if (IsKeyDown(KEY_SPACE)) next_frame(game);

        BeginDrawing();
        {
            ClearBackground(WHITE);
            draw_grid(grid, game_width, game_height, cell_size_px);
        }
        EndDrawing();
    }

    printf("average frametime: %f\n", average_float(frame_times, 256));
    CloseWindow();
    if (!grid_freed) free(grid);
    destroy_game(game);
    fprintf(stderr, "You got to the end of the program.\n");
    return 0;
}

static float average_float(float values[], int n)
{
    float total = 0.0f;
    for (int i = 0; i < n; i++)
    {
        total += values[i];
    }

    return total / (float) n;
}

