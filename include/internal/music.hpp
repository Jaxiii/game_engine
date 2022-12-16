#pragma once


#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER

#include <iostream>
#include <memory>
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
        void StopAndFree();
        ~Music();

    private:
        Mix_Music* music;

};