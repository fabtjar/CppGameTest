#pragma once

#include "sprite.h"

class Hero : public Sprite
{
public:
    int vel_x, vel_y;
    int max_vel;
    int jump_force;

    Hero(Game* game, int x = 0, int y = 0);
    void update();

private:
    void try_move(int move_x, int move_y, Collider::Mask collider_mask);
    bool was_on_ground = false;
};

