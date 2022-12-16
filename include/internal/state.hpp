#pragma once

#include <vector>
#include <memory>
#include "sprite.hpp"
#include "sound.hpp"
#include "game_object.hpp"

using namespace std;

class State {
  public:
    State();
    ~State();
    bool QuitRequested();
    void Update(float delta_time);
    void Render();

  private:
    GameObject background;
    Sprite *bg_sprite;
    Sound *bg_sound;
    bool quitRequested;
    void Input();
    void AddObject(int mouseX, int mouseY);
    vector<shared_ptr<GameObject>> objectArray;

};