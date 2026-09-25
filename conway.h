#include <stdbool.h>

typedef struct game *Game;

Game init_game(int height, int width, bool *grid_data);
void destroy_game(Game g);

void next_frame(Game g);
void load_game_from_file(Game g, char *file_path);


// to get the state of a cell:
//     check grid_data[y * width + x];
// NOTE: you must store grid data yourself

