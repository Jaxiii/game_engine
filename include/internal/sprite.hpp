#pragma once

#include <iostream>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include <SDL2/SDL.h>
#include "game_object.hpp"
#include "component.hpp"

using namespace std;

class Sprite : public Component {

    public:
        Sprite(string file);
        Sprite(GameObject &associated);
        Sprite(GameObject &associated, string file);
        ~Sprite();
        void Open(string file);
        void SetClip(int x, int y,
                    int w, int h);
        void Render();
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        int QueryTexture();
        void Update(float delta_time);
        bool Is(string type);
    private:
        SDL_Texture *texture;
        int width;
        int height;
        SDL_Rect clipRect;
};