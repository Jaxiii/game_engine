#pragma once

class GameObject;
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_


#include <iostream>
#include <memory>
#include <vector>

#include "rect.hpp"
#include "component.hpp"



class GameObject
{
private:

  std::vector <std::unique_ptr<Component>> components;

  bool isDead;

public:

  bool started;

  GameObject();

  ~GameObject();

  void Update(float dt);

  void Render();

  bool IsDead();

  void Start();

  void RequestDelete();

  void AddComponent(Component *cpt);

  void RemoveComponent(Component *cpt);

  Component* GetComponent(std::string type);
  
  Rect box;
};

#endif