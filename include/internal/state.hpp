#ifndef STATE_H
#define STATE_H

#pragma once

#include <vector>
#include <memory>
#include "sprite.hpp"
#include "sound.hpp"
#include "game_object.hpp"
#include "music.hpp"
#include "tile_map.hpp"
#include "tile_set.hpp"
#include "camera_follower.hpp"

using namespace std;

class State {
  public:
    State();
    ~State();
    bool QuitRequested();
    void Update(float delta_time);
    void Render();

  private:
    Music music;
    bool quitRequested;
    void Input();
    void AddObject(int mouseX, int mouseY);
    vector<shared_ptr<GameObject>> objectArray;

};

#endif