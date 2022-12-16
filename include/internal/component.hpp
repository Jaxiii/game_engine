
class Component;
#ifndef _GAME_COMPONENT_H_
#define _GAME_COMPONENT_H_

#include <iostream>
#include "game_object.hpp"

using namespace std;

class GameObject;

class Component {
    public:
      Component(GameObject &associated);
      virtual ~Component();
      virtual void Update(float delta_time) = 0;
      virtual void Render() = 0;
      virtual bool Is(string type) = 0;

  protected:
    GameObject &associated;
};

#endif