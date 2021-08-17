#include "Text.h"

Text::Text(SDL_Renderer* renderer, const char* file, int size)
{
    this->renderer = renderer;
    font = TTF_OpenFont(file, size);
    set_text("");

    x = y = 0;
}

void Text::set_text(const char* text)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, SDL_Colour{ 255, 255, 255, 255 });
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

void Text::render()
{
    rect.x = x;
    rect.y = y;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}