#include <type_traits>
#include "game.h"
#include "tiled_sprite.h"
#include "hero.h"
#include "keyboard.h"
#include "wall.h"
#include "monster.h"

Game::Game(SDL_Renderer* renderer, SDL_Texture* texture)
{
    this->renderer = renderer;
    this->texture = texture;

    TiledSprite* bg = new TiledSprite(this, 0, 0, WIDTH, HEIGHT, SDL_Rect{ 0, 0, 64, 64 });
    sprites.push_back(bg);

    for (int i = 0; i < 5; i++)
        sprites.push_back(new Wall(this, i + 5, 6));

    hero = new Hero(this);
    sprites.push_back(hero);

    while (hero->is_ovelapping_with_mask(Collider::Mask::solid))
        hero->y--;

    coin = new Sprite(this, WIDTH / 2 - 16, 32, { 32 * 3, 0, 32, 32 });
    sprites.push_back(coin);

    debug_text = new Text(renderer, "assets/PressStart2P.ttf", 8);
    debug_text->x = debug_text->y = 2;
}

Game::~Game()
{
    for (Sprite* s : sprites)
        delete s;

    delete debug_text;
}

void Game::update()
{
    for (Sprite* s : sprites)
        s->update();

    if (hero->is_overlapping(coin))
    {
        float sqr_dist = 0;
        do
        {
            coin->change_position();

            auto h = hero->get_collider();
            auto c = coin->get_collider();
            auto hx = h->x + h->width / 2.0f;
            auto hy = h->y + h->height / 2.0f;
            auto cx = c->x + c->width / 2.0f;
            auto cy = c->y + c->height / 2.0f;
            auto dx = hx - cx;
            auto dy = hy - cy;

            sqr_dist = dx * dx + dy * dy;
        }
        while (sqr_dist < 200 * 200);

        coin_collected = true;
    }

    if (can_spawn_monster)
    {
        can_spawn_monster = false;
        sprites.push_back(new Monster(this));
    }

    for (Monster* m : get_sprites_of_type<Monster>())
    {
        if (hero->is_overlapping(m))
        {
            if (hero->old_y + hero->get_collider()->height <= m->y)
            {
                hero->vel_y = -hero->jump_force;
                m->y += 32;
                m->kill = true;
            }
        }
    }

    for (int i = 0; i < sprites.size(); i++)
        if (sprites[i]->kill)
            sprites.erase(sprites.begin() + i);
}

void Game::hero_just_jumped(Hero* hero)
{
    for (Wall* w : get_sprites_of_type<Wall>())
        if (w->is_overlapping(hero, 0, -1))
            w->hide();
}

void Game::hero_just_landed()
{
    for (Wall* w : get_sprites_of_type<Wall>())
        if (w->is_hidden())
            w->change_position();

    if (coin_collected)
    {
        coin_collected = false;
        can_spawn_monster = true;
    }
}

void Game::render()
{
    for (Sprite* s : sprites)
        s->render(renderer, texture);
}

std::vector<Collider*> Game::get_colliders_with_mask(Collider::Mask mask)
{
    std::vector<Collider*> colliders;

    for (Sprite* s : sprites)
    {
        Collider* c = s->get_collider();
        if (c->mask == mask)
            colliders.push_back(c);
    }

    return colliders;
}

template <class T>
std::vector<T*> Game::get_sprites_of_type()
{
    std::vector<T*> sprites_of_type;

    for (Sprite* s : sprites)
    {
        auto t = dynamic_cast<T*>(s);
        if (t != NULL)
            sprites_of_type.push_back(t);
    }

    return sprites_of_type;
}