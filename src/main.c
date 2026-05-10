#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/logic.h"
#include "../include/io.h"
#include "../include/ui.h"

int main() {
    // Initialization of the random number generator
    srand(time(NULL));
    GameState *game = init_game(5); // Memory allocation 

    add_random_tile(game);
    add_random_tile(game);

    run_game_loop(game);

    free_game(game); // Release all memory
    return 0;
}