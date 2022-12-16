#pragma once

#include <string>
#include "game_object.hpp"

using namespace std;

class GameObject;

class Component {
  
  public:
    Component(GameObject &associated);
    virtual ~Component();
    virtual void Start();
    virtual void Update(float delta_time) = 0;
    virtual void Render() = 0;
    virtual bool Is(string type) = 0;

  protected:
    GameObject &associated;

};