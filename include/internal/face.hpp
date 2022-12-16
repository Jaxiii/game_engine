#pragma once

#define INCLUDE_SDL

#include <iostream>
#include <memory>
#include "game_object.hpp"
#include "component.hpp"
#include "sound.hpp"

using namespace std;

class Face : public Component {

  public:
    Face(GameObject &associated);
    void Damage(int damage);
    void Update(float delta_time);
    void Render();
    bool Is(string type);

  private:
    int hitpoints;

};