#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "hero.h"
#include "game.h"
#include "keyboard.h"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    SDL_Window* window = SDL_CreateWindow("Fab C++ Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::WIDTH * Game::SCALE, Game::HEIGHT * Game::SCALE, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetScale(renderer, Game::SCALE, Game::SCALE);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_Surface* surface = IMG_Load("assets/tiles.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (TTF_Init() < 0)
        std::cout << "Error: " << TTF_GetError() << std::endl;

    Game game = Game(renderer, texture);

    bool quit = false;
    while (!quit)
    {
        int old_ticks = SDL_GetTicks();

        Keyboard::update();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                Keyboard::set_key_down(event.key.keysym.scancode, true);
                break;
            case SDL_KEYUP:
                Keyboard::set_key_down(event.key.keysym.scancode, false);
                break;
            }
        }

        game.update();
        game.render();

        SDL_RenderPresent(renderer);

        if (Keyboard::get_key_just_pressed(SDL_SCANCODE_ESCAPE))
            quit = true;

        int new_ticks = SDL_GetTicks();
        if (new_ticks - old_ticks < 1000.0 / Game::FPS)
            SDL_Delay(new_ticks - old_ticks);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}