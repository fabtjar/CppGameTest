#pragma once

#include <SDL.h>
#include "game.h"
#include "collider.h"

class Game;

class Sprite
{
public:
    int x, y, old_x, old_y;
    Sprite(Game* game, int x, int y, SDL_Rect scr_rect);
    virtual void update();
    virtual void render(SDL_Renderer* renderer, SDL_Texture* texture);
    void change_position();
    Collider* get_collider(int offset_x = 0, int offset_y = 0);
    bool is_overlapping(Sprite* other, int offset_x = 0, int offset_y = 0);
    bool is_ovelapping_with_mask(Collider::Mask mask, int offset_x = 0, int offset_y = 0);
    bool is_ovelapping_any(int offset_x = 0, int offset_y = 0);
    bool kill = false;

protected:
    Game* game;
    SDL_Rect src_rect;

private:
    Collider collider;
};