#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/logic.h"
#include "../include/io.h"
#include "../include/ui.h"

int main() {
    srand(time(NULL));
    GameState *game = init_game(5);

    add_random_tile(game);
    add_random_tile(game);

    run_game_loop(game);

    free_game(game);
    return 0;
}