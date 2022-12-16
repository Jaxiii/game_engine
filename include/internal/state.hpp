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
    void LoadAssets();
    void Start();
    bool QuitRequested();
    void Update(float delta_time);
    void Render();
    weak_ptr<GameObject> AddObject(GameObject *game_object);
    weak_ptr<GameObject> GetObjectPtr(GameObject *game_object);
  
  private:
    Music music;
    bool quitRequested;
    bool started;
    void Input();
    vector<shared_ptr<GameObject>> objectArray;
};

#endif