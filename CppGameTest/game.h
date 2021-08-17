#pragma once

#include <vector>
#include <SDL.h>
#include "sprite.h"
#include "text.h"
#include "collider.h"

class Sprite;
class Hero;

class Game
{
public:
    static const int WIDTH = 480;
    static const int HEIGHT = 360;
    static const int SCALE = 2;
    static const int FPS = 60;

    Game(SDL_Renderer* renderer, SDL_Texture* texture);
    ~Game();
    void update();
    void render();
    void hero_just_jumped(Hero* hero);
    void hero_just_landed();
    std::vector<Collider*> get_colliders_with_mask(Collider::Mask mask);
    template <class T> std::vector<T*> get_sprites_of_type();
    Text* debug_text;
    std::vector<Sprite*> sprites;

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    Hero* hero;
    Sprite* coin;
    bool coin_collected = false;
    bool can_spawn_monster = false;
};

