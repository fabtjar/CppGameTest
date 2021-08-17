#include <stdlib.h>
#include <SDL.h>
#include <string>
#include <algorithm>
#include "hero.h"
#include "sprite.h"
#include "game.h"
#include "keyboard.h"

Hero::Hero(Game* game, int x, int y) : Sprite(game, x, y, SDL_Rect{ 32 * 2 + 3, 3, 32 - 6, 32 - 6 })
{
    this->x = Game::WIDTH / 2 - src_rect.w / 2;
    this->y = Game::HEIGHT / 2;
    vel_x = 0;
    vel_y = 0;
    max_vel = 3;
    jump_force = 12;
    get_collider()->mask = Collider::Mask::hero;
}

void Hero::update()
{
    old_x = x;
    old_y = y;

    int hor = 0;
    bool jump_pressed = false;

    if (Keyboard::get_key_down(SDL_SCANCODE_LEFT))
        hor--;
    if (Keyboard::get_key_down(SDL_SCANCODE_RIGHT))
        hor++;
    if (Keyboard::get_key_just_pressed(SDL_SCANCODE_UP))
        jump_pressed = true;

    vel_x = hor * max_vel;
    vel_y = std::min(vel_y + 1, 20);

    bool on_ground = is_ovelapping_with_mask(Collider::Mask::solid, 0, 1);

    if (on_ground && !was_on_ground)
        game->hero_just_landed();

    was_on_ground = on_ground;

    if (on_ground && jump_pressed)
    {
        game->hero_just_jumped(this);
        vel_y = -jump_force;
    }

    try_move(vel_x, vel_y, Collider::Mask::solid);

    if (x < -32)
        x += Game::WIDTH + 32;
    else if (x > Game::WIDTH)
        x -= Game::WIDTH + 32;
    if (y < -32)
        y += Game::HEIGHT + 32;
    else if (y > Game::HEIGHT)
        y -= Game::HEIGHT + 32;

    if (on_ground)
        game->debug_text->set_text("On Ground");
    else
        game->debug_text->set_text("...");
}

void Hero::try_move(int move_x, int move_y, Collider::Mask collide_mask)
{
    int sign_x, sign_y;
    if (move_x > 0) sign_x = 1;
    else if (move_x < 0) sign_x = -1;
    if (move_y > 0) sign_y = 1;
    else if (move_y < 0) sign_y = -1;

    while (move_x != 0)
    {
        if (!is_ovelapping_with_mask(collide_mask, sign_x, 0))
        {
            x += sign_x;
            move_x -= sign_x;
        }
        else
        {
            move_x = 0;
            vel_x = 0;
        }
    }

    while (move_y != 0)
    {
        if (!is_ovelapping_with_mask(collide_mask, 0, sign_y))
        {
            y += sign_y;
            move_y -= sign_y;
        }
        else
        {
            move_y = 0;
            vel_y = 0;
        }
    }
}