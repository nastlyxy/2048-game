#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "ui.h"
#include "logic.h"
#include "io.h"

#define TILE_SIZE 100

int can_move(GameState *game, char dir) {
    GameState *temp = init_game(game->size);
    for(int i=0; i<game->size; i++) {
        for(int j=0; j<game->size; j++) {
            temp->board[i][j] = game->board[i][j];
        }
    }
    int moved = 0;
    if(dir == 'L') moved = move_left(temp);
    if(dir == 'R') moved = move_right(temp);
    if(dir == 'U') moved = move_up(temp);
    if(dir == 'D') moved = move_down(temp);
    free_game(temp);
    return moved;
}

void set_tile_color(SDL_Renderer *renderer, int value) {
    switch(value) {
        case 0: SDL_SetRenderDrawColor(renderer, 205, 193, 180, 255); break;
        case 2: SDL_SetRenderDrawColor(renderer, 238, 228, 218, 255); break;
        case 4: SDL_SetRenderDrawColor(renderer, 237, 224, 200, 255); break;
        case 8: SDL_SetRenderDrawColor(renderer, 242, 177, 121, 255); break;
        case 16: SDL_SetRenderDrawColor(renderer, 245, 149, 99, 255); break;
        case 32: SDL_SetRenderDrawColor(renderer, 246, 124, 95, 255); break;
        case 64: SDL_SetRenderDrawColor(renderer, 246, 94, 59, 255); break;
        case 128: SDL_SetRenderDrawColor(renderer, 237, 207, 114, 255); break;
        case 256: SDL_SetRenderDrawColor(renderer, 237, 204, 97, 255); break;
        case 512: SDL_SetRenderDrawColor(renderer, 237, 200, 80, 255); break;
        case 1024: SDL_SetRenderDrawColor(renderer, 237, 197, 63, 255); break;
        case 2048: SDL_SetRenderDrawColor(renderer, 237, 194, 46, 255); break;
        default: SDL_SetRenderDrawColor(renderer, 60, 58, 50, 255); break;
    }
}

void draw_button(SDL_Renderer *renderer, TTF_Font *font, int x, int y, int w, int h, const char *label, int is_hovered, int is_valid) {
    SDL_Rect rect = {x, y, w, h};
    if (is_hovered) {
        if (is_valid) {
            SDL_SetRenderDrawColor(renderer, 100, 200, 100, 255); 
        } else {
            SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255); 
        }
    } else {
        SDL_SetRenderDrawColor(renderer, 205, 193, 180, 255); 
    }
    SDL_RenderFillRect(renderer, &rect);

    if (font != NULL) {
        SDL_Color textColor = {119, 110, 101, 255};
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, label, textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        int text_w = textSurface->w;
        int text_h = textSurface->h;
        SDL_Rect text_rect = { x + (w - text_w) / 2, y + (h - text_h) / 2, text_w, text_h };
        SDL_RenderCopy(renderer, textTexture, NULL, &text_rect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void run_game_loop(GameState *game) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    int screen_w = game->size * TILE_SIZE + 20;
    int screen_h = game->size * TILE_SIZE + 120;

    SDL_Window *window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_w, screen_h, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    TTF_Font *font = TTF_OpenFont("font.ttf", 36);
    TTF_Font *btn_font = TTF_OpenFont("font.ttf", 24);
    TTF_Font *go_font = TTF_OpenFont("font.ttf", 48);

    SDL_Cursor *cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_Cursor *cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor *cursor_no = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);

    int quit = 0;
    SDL_Event e;

    int btn_w = 60, btn_h = 60, spacing = 20;
    int total_btns_w = 4 * btn_w + 3 * spacing;
    int start_x = (screen_w - total_btns_w) / 2;

    SDL_Rect btn_left = {start_x, screen_h - 90, btn_w, btn_h};
    SDL_Rect btn_down = {start_x + btn_w + spacing, screen_h - 90, btn_w, btn_h};
    SDL_Rect btn_up = {start_x + 2*(btn_w + spacing), screen_h - 90, btn_w, btn_h};
    SDL_Rect btn_right = {start_x + 3*(btn_w + spacing), screen_h - 90, btn_w, btn_h};

    while (!quit) {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        int hover_left = (mouse_x >= btn_left.x && mouse_x <= btn_left.x + btn_left.w && mouse_y >= btn_left.y && mouse_y <= btn_left.y + btn_left.h);
        int hover_down = (mouse_x >= btn_down.x && mouse_x <= btn_down.x + btn_down.w && mouse_y >= btn_down.y && mouse_y <= btn_down.y + btn_down.h);
        int hover_up = (mouse_x >= btn_up.x && mouse_x <= btn_up.x + btn_up.w && mouse_y >= btn_up.y && mouse_y <= btn_up.y + btn_up.h);
        int hover_right = (mouse_x >= btn_right.x && mouse_x <= btn_right.x + btn_right.w && mouse_y >= btn_right.y && mouse_y <= btn_right.y + btn_right.h);

        int valid_left = can_move(game, 'L');
        int valid_down = can_move(game, 'D');
        int valid_up = can_move(game, 'U');
        int valid_right = can_move(game, 'R');

        int is_game_over = !(valid_left || valid_down || valid_up || valid_right);

        if (!is_game_over) {
            if (hover_left) SDL_SetCursor(valid_left ? cursor_hand : cursor_no);
            else if (hover_down) SDL_SetCursor(valid_down ? cursor_hand : cursor_no);
            else if (hover_up) SDL_SetCursor(valid_up ? cursor_hand : cursor_no);
            else if (hover_right) SDL_SetCursor(valid_right ? cursor_hand : cursor_no);
            else SDL_SetCursor(cursor_arrow);
        } else {
            SDL_SetCursor(cursor_arrow);
        }

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN && !is_game_over) {
                int moved = 0;
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT: moved = move_left(game); break;
                    case SDLK_RIGHT: moved = move_right(game); break;
                    case SDLK_UP: moved = move_up(game); break;
                    case SDLK_DOWN: moved = move_down(game); break;
                    case SDLK_s: save_game(game, "save.txt"); break;
                    case SDLK_l: 
                        {
                            GameState* loaded = load_game("save.txt");
                            if (loaded) {
                                free_game(game);
                                game = loaded;
                            }
                        }
                        break;
                }
                if (moved) add_random_tile(game);
            } else if (e.type == SDL_MOUSEBUTTONDOWN && !is_game_over) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int moved = 0;
                    if (hover_left && valid_left) moved = move_left(game);
                    else if (hover_down && valid_down) moved = move_down(game);
                    else if (hover_up && valid_up) moved = move_up(game);
                    else if (hover_right && valid_right) moved = move_right(game);

                    if (moved) add_random_tile(game);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < game->size; i++) {
            for (int j = 0; j < game->size; j++) {
                SDL_Rect tile_rect = { j * TILE_SIZE + 10, i * TILE_SIZE + 10, TILE_SIZE - 20, TILE_SIZE - 20 };
                
                set_tile_color(renderer, game->board[i][j]);
                SDL_RenderFillRect(renderer, &tile_rect);

                if (game->board[i][j] != 0 && font != NULL) {
                    char num_str[10];
                    sprintf(num_str, "%d", game->board[i][j]);
                    
                    SDL_Color textColor = (game->board[i][j] <= 4) ? (SDL_Color){119, 110, 101, 255} : (SDL_Color){249, 246, 242, 255};
                    
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

        draw_button(renderer, btn_font, btn_left.x, btn_left.y, btn_left.w, btn_left.h, "L", hover_left, valid_left);
        draw_button(renderer, btn_font, btn_down.x, btn_down.y, btn_down.w, btn_down.h, "D", hover_down, valid_down);
        draw_button(renderer, btn_font, btn_up.x, btn_up.y, btn_up.w, btn_up.h, "U", hover_up, valid_up);
        draw_button(renderer, btn_font, btn_right.x, btn_right.y, btn_right.w, btn_right.h, "R", hover_right, valid_right);

        if (is_game_over) {
            SDL_SetRenderDrawColor(renderer, 238, 228, 218, 180);
            SDL_Rect overlay = {0, 0, screen_w, screen_h};
            SDL_RenderFillRect(renderer, &overlay);

            if (go_font != NULL) {
                SDL_Color goColor = {119, 110, 101, 255};
                SDL_Surface *goSurface = TTF_RenderText_Solid(go_font, "GAME OVER", goColor);
                SDL_Texture *goTexture = SDL_CreateTextureFromSurface(renderer, goSurface);
                SDL_Rect go_rect = { (screen_w - goSurface->w) / 2, (game->size * TILE_SIZE - goSurface->h) / 2, goSurface->w, goSurface->h };
                SDL_RenderCopy(renderer, goTexture, NULL, &go_rect);
                SDL_FreeSurface(goSurface);
                SDL_DestroyTexture(goTexture);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_FreeCursor(cursor_arrow);
    SDL_FreeCursor(cursor_hand);
    SDL_FreeCursor(cursor_no);

    if (btn_font != NULL) TTF_CloseFont(btn_font);
    if (font != NULL) TTF_CloseFont(font);
    if (go_font != NULL) TTF_CloseFont(go_font);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}