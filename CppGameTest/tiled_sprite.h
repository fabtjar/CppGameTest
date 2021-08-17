#pragma once

#include "sprite.h"

class TiledSprite : public Sprite
{
public:
    int width, height;
    TiledSprite(Game* game, int x, int y, int width, int height, SDL_Rect src_rect);
    void render(SDL_Renderer* renderer, SDL_Texture* texture);
};

