#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "draw.h"

#define CELL_SIZE_PX 10
#define BORDER_SIZE_PX 1

// Input-related functions: mouse
// bool IsMouseButtonPressed(int button);                  // Check if a mouse button has been pressed once
// bool IsMouseButtonDown(int button);                     // Check if a mouse button is being pressed
// bool IsMouseButtonReleased(int button);                 // Check if a mouse button has been released once
// bool IsMouseButtonUp(int button);                       // Check if a mouse button is NOT being pressed
// Vector2 GetMousePosition(void);                         // Get mouse position XY

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage:\n\t./create [filename.txt] [width] [height]\n");
    }

    FILE *file = fopen(argv[1], "w");
    if (!file)
    {
        fprintf(stderr, "Failed to open file: %s\n", argv[1]);
    }

    int game_width = atoi(argv[2]);
    int game_height = atoi(argv[3]);

    bool *grid = calloc(game_width * game_height, sizeof(bool));
    int screen_width = game_width * (CELL_SIZE_PX + 1) + 1;
    int screen_height = game_height * (CELL_SIZE_PX + 1) + 1;

    Vector2 mouse_position;
    SetTargetFPS(180);
    while (!WindowShouldClose())
    {

    }

    InitWindow(screen_width, screen_height, "Create Conway Gamefile");

    return 0;
}

