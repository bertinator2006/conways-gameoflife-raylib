#include <stdio.h>

#define CELL_SIZE_PX 10
#define BORDER_SIZE_PX 1

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage:\n\t./create [width] [height]\n");
    }

    int game_width = atoi(argv[1]);
    int game_height = atoi(argv[2]);

    int screen_width = game_width * (CELL_SIZE_PX + 1) + 1;
    int screen_height = game_height * (CELL_SIZE_P + 1) + 1;

    return 0;
}
