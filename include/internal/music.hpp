#pragma once

#include <iostream>
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.hpp"
using namespace std;

class Music {
    public:
        Music();
        Music(string file);
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(string file);
        bool IsOpen();
        ~Music();
    private:
        Mix_Music* music;
};