#include "Collider.h"

Collider::Collider()
{
    this->x = this->y = this->width = this->height = 0;
    this->mask = Mask::none;
}

Collider::Collider(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool Collider::is_overlapping(Collider* other)
{
    return x < other->x + other->width && x + width > other->x && y < other->y + other->height && y + height > other->y;;
}