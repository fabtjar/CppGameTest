#pragma once
struct Collider
{
public:
    enum class Mask { none, solid, hero, monster, coin };
    Mask mask;
    int x, y, width, height;
    bool is_overlapping(Collider* other);
    Collider();
    Collider(int x, int y, int width, int height);
};

