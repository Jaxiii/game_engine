#pragma once

#define INCLUDE_SDL_MIXER
#include "SDL_include.hpp"

#include <iostream>
#include <memory>

#include "game_object.hpp"
#include "component.hpp"

using namespace std;

class Sound : public Component {

  public:
    Sound(GameObject &associated);
    Sound(GameObject &associated, string file);
    ~Sound();
    void Play(int times = 1);
    void Stop();
    void Open(string file);
    bool IsOpen();
    void Update(float delta_time);
    void Render();
    bool Is(string type);

  private:
    Mix_Chunk *chunk;
    int channel;

};