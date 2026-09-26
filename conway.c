#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "conway.h"

#define CELL_MASK 0x80
#define COUNT_MASK 0x7F

struct game
{
    int height;
    int width;
    uint8_t *grid;
    bool *public_grid;
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


Game init_game(int height, int width, bool *grid_data)
{
    Game g = malloc(sizeof(struct game));
    g->grid = calloc(width * height, sizeof(uint8_t));
    g->height = height;
    g->width = width;
    g->public_grid = grid_data;

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
    char *ret = fgets(2048, buffer, game_file);
    if (ret == NULL)
    {
  //      fprintf(stderr, "errno: %i.\n", errno);
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
    }
    rewind(game_file);

}

void destroy_game(Game g)
{
    free(g->grid);
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

