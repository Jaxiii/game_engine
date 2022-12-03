
#include "../include/internal/game_object.hpp"

#include <algorithm>
#include <memory>

using namespace std;

GameObject::GameObject()
{
  isDead = false;
  started = false;
}

GameObject::~GameObject()
{
  components.clear();
}

void GameObject::Update(float dt)
{
  for (auto &component : components)
    component->Update(dt);
}

void GameObject::Render()
{
  for (auto &component : components)
    component->Render();
}

bool GameObject::IsDead()
{
  return isDead;
}

void GameObject::RequestDelete() {
  isDead = true;
}

void GameObject::AddComponent(Component *input_component) {
}

void GameObject::RemoveComponent(Component *input_component) {
  remove_if(components.begin(), 
            components.end(), 
            [=](unique_ptr<Component> &allocated_component) { 
            return input_component == allocated_component.get(); 
            });
}

void GameObject::Start(){}

Component *GameObject::GetComponent(string type) {
  vector<unique_ptr<Component>>::iterator it;

  if (it == components.end()) {
    return nullptr;
  } else {
    return it->get();
  }
}