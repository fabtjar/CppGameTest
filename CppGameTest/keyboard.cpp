#include "keyboard.h"

bool Keyboard::get_key_down(SDL_Scancode scan_code)
{
    return instance.keys[scan_code];
}

void Keyboard::set_key_down(SDL_Scancode scan_code, bool is_down)
{
    instance.keys[scan_code] = is_down;
}

bool Keyboard::get_key_just_pressed(SDL_Scancode scan_code)
{
    return !instance.old_keys[scan_code] && instance.keys[scan_code];
}

bool Keyboard::get_key_just_released(SDL_Scancode scan_code)
{
    return instance.old_keys[scan_code] && !instance.keys[scan_code];
}

void Keyboard::update()
{
    instance.old_keys = instance.keys;
}

Keyboard Keyboard::instance;