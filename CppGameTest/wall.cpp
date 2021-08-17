#include "wall.h"

Wall::Wall(Game* game, int grid_x, int grid_y) : Sprite(game, grid_x * 32, grid_y * 32, SDL_Rect{ 64, 32, 32, 32 })
{
    get_collider()->mask = Collider::Mask::solid;
}

void Wall::hide()
{
    x = y = -100;
}

bool Wall::is_hidden()
{
    return x < 0 || y < 0;
}