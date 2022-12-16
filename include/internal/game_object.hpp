#pragma once

class GameObject;
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_


#include <iostream>
#include <memory>
#include <vector>

#include "rect.hpp"
#include "component.hpp"

using namespace std;

class Component;

class GameObject {
  public:
    GameObject();
    ~GameObject();
    void Update(float delta_time);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(shared_ptr<Component> component);
    void RemoveComponent(shared_ptr<Component> component);
    shared_ptr<Component> GetComponent(string type);
    Rect box;

  private:
    vector<shared_ptr<Component>> components;
    bool isDead;
};

#endif