#include <stdlib.h>
#include <SDL.h>
#include <string>
#include "monster.h"
#include <algorithm>
#include "sprite.h"
#include "game.h"

Monster::Monster(Game* game) : Sprite(game, 0, 0, SDL_Rect{ 32 * 3 + 1, 32 * 1 + 1, 32 - 2, 32 - 2 })
{
    x = rand() % (Game::WIDTH - src_rect.w);
    y = Game::HEIGHT;
    vel_x = x < Game::WIDTH / 2 ? 1 : -1;
    vel_y = -1;
    get_collider()->mask = Collider::Mask::monster;
}

void Monster::update()
{
    old_x = x;
    old_y = y;

    if (!is_on_screen && !is_over_edge())
        is_on_screen = true;

    try_move(vel_x, vel_y, Collider::Mask::solid);
}

void Monster::try_move(int move_x, int move_y, Collider::Mask collide_mask)
{
    int sign_x, sign_y;
    if (move_x > 0) sign_x = 1;
    else if (move_x < 0) sign_x = -1;
    if (move_y > 0) sign_y = 1;
    else if (move_y < 0) sign_y = -1;

    while (move_x != 0)
    {
        if (!is_ovelapping_with_mask(collide_mask, sign_x, 0) && (!is_over_edge(sign_x, 0) || !is_on_screen))
        {
            x += sign_x;
            move_x -= sign_x;
        }
        else
        {
            move_x = 0;
            vel_x *= -1;
        }
    }

    while (move_y != 0)
    {
        if (!is_ovelapping_with_mask(collide_mask, 0, sign_y) && (!is_over_edge(0, sign_y) || !is_on_screen))
        {
            y += sign_y;
            move_y -= sign_y;
        }
        else
        {
            move_y = 0;
            vel_y *= -1;
        }
    }
}

bool Monster::is_over_edge(int offset_x, int offset_y)
{
    auto left = x + offset_x;
    auto right = x + src_rect.w + offset_x;
    auto top = y + offset_y;
    auto bottom = y + src_rect.h + offset_y;
    return left < 0 || right > Game::WIDTH || top < 0 || bottom > Game::HEIGHT;
}