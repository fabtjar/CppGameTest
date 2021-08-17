#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Text
{
public:
    Text(SDL_Renderer* renderer, const char* file, int size);
    void set_text(const char* text);
    void render();
    int x, y;
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Rect rect;
};

