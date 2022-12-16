#include "../include/internal/game_object.hpp"

GameObject::GameObject() : box(0, 0, 0, 0),
                           isDead(false) {
}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Start() {
    for (int i = 0; i < (int)components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}

void GameObject::Update(float delta_time){   
    for (int i = components.size() - 1; i >= 0; --i) {
        components[i]->Update(delta_time);
    }
}

void GameObject::Render() {   
    for (int i = components.size() -1; i >= 0; --i) {   
        components[i]->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(shared_ptr<Component> component) {
    components.emplace_back(component);
}

void GameObject::RemoveComponent(shared_ptr<Component> component) {
    for (int i = components.size() - 1; i >= 0; i--) {   
        if (components[i] == component) components.erase(components.begin()+i);
    }
}

shared_ptr<Component> GameObject::GetComponent(string type) {
    for (int i = components.size() - 1; i >= 0; i--){
        if (components[i]->Is(type)) return components[i];
    }
    return nullptr;
}