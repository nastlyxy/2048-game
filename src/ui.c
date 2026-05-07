#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "ui.h"
#include "logic.h"
#include "io.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
#define TILE_SIZE 100

void run_game_loop(GameState *game) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    TTF_Font *font = TTF_OpenFont("font.ttf", 36);

    int quit = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                int moved = 0;
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT: moved = move_left(game); break;
                    case SDLK_RIGHT: moved = move_right(game); break;
                    case SDLK_UP: moved = move_up(game); break;
                    case SDLK_DOWN: moved = move_down(game); break;
                    case SDLK_s: save_game(game, "save.txt"); break;
                }
                if (moved) {
                    add_random_tile(game);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < game->size; i++) {
            for (int j = 0; j < game->size; j++) {
                SDL_Rect tile_rect = { j * TILE_SIZE + 10, i * TILE_SIZE + 10, TILE_SIZE - 20, TILE_SIZE - 20 };
                
                if (game->board[i][j] == 0) {
                    SDL_SetRenderDrawColor(renderer, 205, 193, 180, 255);
                } else if (game->board[i][j] == 2) {
                    SDL_SetRenderDrawColor(renderer, 238, 228, 218, 255);
                } else if (game->board[i][j] == 4) {
                    SDL_SetRenderDrawColor(renderer, 237, 224, 200, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 242, 177, 121, 255);
                }
                
                SDL_RenderFillRect(renderer, &tile_rect);

                if (game->board[i][j] != 0 && font != NULL) {
                    char num_str[10];
                    sprintf(num_str, "%d", game->board[i][j]);
                    SDL_Color textColor = {119, 110, 101, 255};
                    SDL_Surface *textSurface = TTF_RenderText_Solid(font, num_str, textColor);
                    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                    
                    int text_w = textSurface->w;
                    int text_h = textSurface->h;
                    SDL_Rect text_rect = { j * TILE_SIZE + 10 + (TILE_SIZE - 20 - text_w) / 2, i * TILE_SIZE + 10 + (TILE_SIZE - 20 - text_h) / 2, text_w, text_h };
                    
                    SDL_RenderCopy(renderer, textTexture, NULL, &text_rect);
                    SDL_FreeSurface(textSurface);
                    SDL_DestroyTexture(textTexture);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if (font != NULL) TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}