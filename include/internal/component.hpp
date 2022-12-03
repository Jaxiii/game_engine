
class Component;
#ifndef _GAME_COMPONENT_H_
#define _GAME_COMPONENT_H_

#include <iostream>
#include "game_object.hpp"

class Component {

  protected:
    GameObject &associated;

  public:

    explicit Component(GameObject &associated);
    virtual ~Component();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) = 0;

};

#endif