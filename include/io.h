#ifndef IO_H
#define IO_H

#include "logic.h"

void save_game(GameState *game, const char *filename);
GameState* load_game(const char *filename);

#endif