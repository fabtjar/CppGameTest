#include "sprite.h"

Sprite::Sprite(Game* game, int x, int y, SDL_Rect src_rect)
{
    this->game = game;
    this->x = x;
    this->y = y;
    this->src_rect = src_rect;

    collider.width = src_rect.w;
    collider.height = src_rect.h;
}

void Sprite::update()
{

}

void Sprite::render(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_Rect dest_rect = { x, y, src_rect.w, src_rect.h };
    SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect);
}

Collider* Sprite::get_collider(int offset_x, int offset_y)
{
    collider.x = x + offset_x;
    collider.y = y + offset_y;
    return &collider;
}

bool Sprite::is_overlapping(Sprite* other, int offset_x, int offset_y)
{
    return get_collider(offset_x, offset_y)->is_overlapping(other->get_collider());
}

bool Sprite::is_ovelapping_with_mask(Collider::Mask mask, int offset_x, int offset_y)
{
    Collider collider = *get_collider(offset_x, offset_y);

    for (Collider* c : game->get_colliders_with_mask(mask))
        if (collider.is_overlapping(c))
            return true;

    return false;
}

bool Sprite::is_ovelapping_any(int offset_x, int offset_y)
{
    for (Sprite* s : game->sprites)
        if (s->get_collider()->mask != Collider::Mask::none && is_overlapping(s, offset_x, offset_y))
            return true;

    return false;
}

void Sprite::change_position()
{
    Sprite s = Sprite(game, 0, 0, SDL_Rect{ 0, 0, 32, 32 });

    do
    {
        s.x = (rand() % (Game::WIDTH / 32 - 2) + 1) * 32;
        s.y = (rand() % (Game::HEIGHT / 32 - 3) + 2) * 32;
    }
    while (s.is_ovelapping_any());

    x = s.x;
    y = s.y;
}