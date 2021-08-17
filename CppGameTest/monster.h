#pragma once

#include "sprite.h"

class Monster : public Sprite
{
public:
    Monster(Game* game);
    void update();

private:
    int vel_x, vel_y;
    void try_move(int move_x, int move_y, Collider::Mask collider_mask);
    bool is_over_edge(int offset_x = 0, int offset_y = 0);
    bool is_on_screen = false;
};

