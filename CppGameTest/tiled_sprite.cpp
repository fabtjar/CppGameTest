#include "tiled_sprite.h"

TiledSprite::TiledSprite(Game* game, int x, int y, int width, int height, SDL_Rect src_rect) : Sprite(game, x, y, src_rect)
{
    this->width = width;
    this->height = height;
}

void TiledSprite::render(SDL_Renderer* renderer, SDL_Texture* texture)
{
    for (int tile_x = x; tile_x < width; tile_x += src_rect.w)
    {
        for (int tile_y = y; tile_y < height; tile_y += src_rect.h)
        {
            SDL_Rect dest_rect = { tile_x, tile_y, src_rect.w, src_rect.h };
            SDL_Rect tileRect = src_rect;

            if (tile_x + tileRect.w > width)
            {
                tileRect.w = width - tile_x;
                dest_rect.w = tileRect.w;
            }
            if (tile_y + tileRect.h > height)
            {
                tileRect.h = height - tile_y;
                dest_rect.h = tileRect.h;
            }

            SDL_RenderCopy(renderer, texture, &tileRect, &dest_rect);
        }
    }
}