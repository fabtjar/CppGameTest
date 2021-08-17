#pragma once

#include <SDL.h>
#include <map>

class Keyboard
{
public:
    bool static get_key_down(SDL_Scancode scan_code);
    void static set_key_down(SDL_Scancode scan_code, bool is_down);
    bool static get_key_just_pressed(SDL_Scancode);
    bool static get_key_just_released(SDL_Scancode);
    void static update();
private:
    static Keyboard instance;
    std::map<SDL_Scancode, bool> keys, old_keys;
};

