#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "rect.hpp"
#include "component.hpp"

using namespace std;

class Component;

class GameObject {

  public:
    GameObject();
    ~GameObject();
    void Start();
    void Update(float delta_time);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(shared_ptr<Component> component);
    void RemoveComponent(shared_ptr<Component> component);
    shared_ptr<Component> GetComponent(string type);
    Rect box;
    bool started;

  private:
    vector<shared_ptr<Component>> components;
    bool isDead;

};