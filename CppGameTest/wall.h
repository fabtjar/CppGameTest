#pragma once

#include "sprite.h"

class Wall : public Sprite
{
public:
    Wall(Game* game, int grid_x = 0, int grid_y = 0);
    void hide();
    bool is_hidden();
};
