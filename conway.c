#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conway.h"

#define CELL_MASK 0x80
#define COUNT_MASK 0x7F

struct game
{
    int height;
    int width;
    uint8_t *grid;
    bool *public_grid;
    bool caller_owned_public_grid;
};

struct vector {
    int x;
    int y;
};

static void increment_neighbours(Game g, int index);
static void decrement_neighbours(Game g, int index);
static void change_neighbours(Game g, int index, int dx);
static void turn_cell_on(Game g, int i);
static void turn_cell_off(Game g, int i);
static void strip_newline(char *buf);


Game init_game(int height, int width, bool *grid_data)
{
    Game g = malloc(sizeof(struct game));
    g->grid = calloc(width * height, sizeof(uint8_t));
    g->height = height;
    g->width = width;
    g->public_grid = grid_data;
    g->caller_owned_public_grid = true;

    // we load the public_grid data
    for (int i = 0; i < width * height; i++)
    {
        if (grid_data[i])
        {
            turn_cell_on(g, i);
        }
    }

    return g;
}

Game init_game_file(char *file_path)
{
    FILE *game_file = fopen(file_path, "r");
    if (!game_file)
    {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    Game g = malloc(sizeof(struct game));
    if (!g)
    {
        fprintf(stderr, "Error allocating memory for game.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[2048];
    char *ret = fgets(buffer, 2048, game_file);
    if (ret == NULL)
    {
        fprintf(stderr, "Couldn't get first line of file during initialisation.\n");
        exit(EXIT_FAILURE);
    }

    // width calculations
    int width = 0;
    for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++)
    {
        width++;
    }

    if (!width)
    {
        g->width = 0;
        g->height = 0;
        g->grid = NULL;
        g->public_grid = NULL;
        g->caller_owned_public_grid = false;
    }

    rewind(game_file);

    int height = 0;
    while (fgets(buffer, 2048, game_file))
    {
        strip_newline(buffer);
        if (strlen(buffer) != width)
        {
            fprintf(stderr, "Inconsistent grid width found in file duiring initialisation.\n");
            exit(EXIT_FAILURE);
        }
        height++;
    }

    g->width = width;
    g->height = height;
    g->grid = calloc(width * height, sizeof(uint8_t));
    if (!(g->grid))
    {
        fprintf(stderr, "calloc failed for uint8_t grid in conway.\n");
        exit(EXIT_FAILURE);
    }
    g->public_grid = calloc(width * height, sizeof(bool));
    if (!(g->public_grid))
    {
        fprintf(stderr, "calloc failed for uint8_t grid in conway.\n");
        exit(EXIT_FAILURE);
    }
    g->caller_owned_public_grid = false;

    rewind(game_file);
    for (int y = 0; y < height; y++)
    {
        fgets(buffer, 2048, game_file);
        for (int x = 0; x < width; x++)
        {
            turn_cell_on(g, y * width + x);
        }
    }

    return g;
}

void destroy_game(Game g)
{
    free(g->grid);
    if (!(g->caller_owned_public_grid)) free(g->public_grid);
    free(g);
}

int get_game_width(Game g)
{
    return g->width;
}

int get_game_height(Game g)
{
    return g->height;
}

bool *get_game_grid(Game g)
{
    return g->public_grid;
}

void next_frame(Game g)
{
    int cell_count = g->width * g->height;
    uint8_t *grid = g->grid;
    bool *public_grid = g->public_grid;
    for (int i = 0; i < cell_count; i++)
    {
        bool cell_on = (grid[i] & CELL_MASK);
        int neighbour_count = grid[i] & COUNT_MASK;

        if (cell_on && neighbour_count < 2)
        {
            public_grid[i] = false;
        }
        else if (cell_on && neighbour_count > 3)
        {
            public_grid[i] = false;
        }
        else if (!cell_on && neighbour_count == 3)
        {
            public_grid[i] = true;
        }
    }

    for (int i = 0; i < cell_count; i++)
    {
        if (public_grid[i] && !(grid[i] & CELL_MASK))
        {
            grid[i] |= CELL_MASK;
            increment_neighbours(g, i);
        }
        else if (!public_grid[i] && (grid[i] & CELL_MASK))
        {
            grid[i] &= COUNT_MASK;
            decrement_neighbours(g, i);
        }
    }
}

static void strip_newline(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            return;
        }
    }
}

static void turn_cell_off(Game g, int i)
{
    g->public_grid[i] = false;
    g->grid[i] &= COUNT_MASK;
    decrement_neighbours(g, i);
}

static void turn_cell_on(Game g, int i)
{
    g->public_grid[i] = true;
    g->grid[i] |= CELL_MASK;
    increment_neighbours(g, i);
}

static void decrement_neighbours(Game g, int index)
{
    change_neighbours(g, index, -1);
}

static void increment_neighbours(Game g, int index)
{
    change_neighbours(g, index, 1);
}

static void change_neighbours(Game g, int index, int dx)
{
    int height = g->height;
    int width = g->width;

    uint8_t *grid = g->grid;

    int x = index % width;
    int y = index / width;

    struct vector iter[8] = {
        {-1,-1}, {0,-1}, {1,-1},
        {-1,0}, {1,0},
        {-1,1}, {0,1}, {1,1}
    };

    for (int i = 0; i < 8; i++)
    {
        int cx = x + iter[i].x;
        int cy = y + iter[i].y;
        bool within_x_bounds = (cx < width && cx >= 0);
        bool within_y_bounds = (cy < height && cy >= 0);
        if (within_x_bounds && within_y_bounds)
        {
            grid[cy * width + cx] += dx;
        }
    }
}

