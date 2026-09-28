#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "draw.h"

#define BORDER_SIZE_PX 1
#define MODE_ADD 0
#define MODE_REMOVE 1

// Input-related functions: mouse
// bool IsMouseButtonPressed(int button);                  // Check if a mouse button has been pressed once
// bool IsMouseButtonDown(int button);                     // Check if a mouse button is being pressed
// bool IsMouseButtonReleased(int button);                 // Check if a mouse button has been released once
// bool IsMouseButtonUp(int button);                       // Check if a mouse button is NOT being pressed
// Vector2 GetMousePosition(void);                         // Get mouse position XY

typedef struct pos {
    int x;
    int y;
} Pos;

static void draw_preview_cell(int x, int y, int cell_size_px);
static Pos get_hovered_cell(Vector2 mouse_position, int cell_size_px);
static bool within_bounds(Pos cell, int width, int height);
static void append_char(char *buffer, char c);


int main(int argc, char *argv[])
{
    int cell_size_px = 5;
    int game_width;
    int game_height;
    FILE *file;

    if (argc < 2 || argc > 4)
    {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "\t./create [filename.txt] [width] [height]\n");
        fprintf(stderr, "\t./create [width] [height]\n");
        fprintf(stderr, "\t./create [square_length]\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 2)
    {
        file = fopen("test.txt", "w");
        if (!file)
        {
            fprintf(stderr, "File: test.txt unable to be open.\n");
            exit(EXIT_FAILURE);
        }
        game_width = atoi(argv[1]);
        game_height = atoi(argv[1]);
    }
    else if (argc == 3)
    {
        file = fopen("test.txt", "w");
        if (!file)
        {
            fprintf(stderr, "File: test.txt unable to be open.\n");
            exit(EXIT_FAILURE);
        }
        game_width = atoi(argv[1]);
        game_height = atoi(argv[2]);
    }
    else if (argc == 4)
    {
        file = fopen(argv[1], "w");
        if (!file)
        {
            fprintf(stderr, "File: test.txt unable to be open.\n");
            exit(EXIT_FAILURE);
        }
        game_width = atoi(argv[2]);
        game_height = atoi(argv[3]);
    }

    bool *grid = calloc(game_width * game_height, sizeof(bool));
    int screen_width = game_width * (cell_size_px + 1) + 1;
    int screen_height = game_height * (cell_size_px + 1) + 1;

    if (game_width > 4 && game_height > 4)
    {
        grid[game_width + 1] = true;
        grid[2 * game_width + 2] = true;
        grid[3 * game_width] = true;
        grid[3 * game_width + 1] = true;
        grid[3 * game_width + 2] = true;
    }

    Pos cell;

    SetTraceLogLevel(LOG_NONE);
    InitWindow(screen_width, screen_height, "Create Conway Gamefile");
    SetTargetFPS(180);
    while (!WindowShouldClose())
    {
        cell = get_hovered_cell(GetMousePosition(), cell_size_px);
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && within_bounds(cell, game_width, game_height))
        {
            grid[cell.y * game_width + cell.x] = false;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && within_bounds(cell, game_width, game_height))
        {
            grid[cell.y * game_width + cell.x] = true;
        }

        BeginDrawing();
        {
            ClearBackground(WHITE);
            draw_grid_with_borders(grid, game_width, game_height, cell_size_px);
        }
        EndDrawing();
    }

    // save the file
    int i = 0;
    for (int y = 0; y < game_height; y++)
    {
        char buffer[2048];
        buffer[0] = '\0';
        for (int x = 0; x < game_width; x++)
        {
            char c = '0';
            if (grid[i]) c = '1';
            append_char(buffer, c);
            i++;
        }
        if (y != game_height - 1) append_char(buffer, '\n');
        fprintf(file, "%s", buffer);
    }

    fclose(file);
    free(grid);

    CloseWindow();
    return 0;
}

static void append_char(char *buffer, char c)
{
    int i = 0;
    while (buffer[i] != '\0') i++;

    buffer[i] = c;
    buffer[i + 1] = '\0';
}

static Pos get_hovered_cell(Vector2 mouse_position, int cell_size_px)
{
    Pos result;
    result.x = mouse_position.x / (cell_size_px + 1);
    result.y = mouse_position.y / (cell_size_px + 1);
    return result;
}

static void draw_preview_cell(int x, int y, int cell_size_px)
{
    // TODO
}

static bool within_bounds(Pos cell, int width, int height)
{
    if (cell.x >= width) return false;
    if (cell.y >= height) return false;
    if (cell.x < 0) return false;
    if (cell.y < 0) return false;
    return true;
}

