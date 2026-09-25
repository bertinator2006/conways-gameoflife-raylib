#include <stdbool.h>

typedef struct game *Game;

Game init_game(int height, int width, bool *grid_data);
Game init_game_file(char *file_path);
void destroy_game(Game g);

int get_game_width(Game g);
int get_game_height(Game g);

void next_frame(Game g);


// to get the state of a cell:
//     check grid_data[y * width + x];
// NOTE: you must store grid data yourself

