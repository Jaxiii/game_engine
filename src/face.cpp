#include "../include/internal/face.hpp"
#include "../include/internal/camera.hpp"
#include "../include/internal/input_manager.hpp"

Face::Face(GameObject &associated) : Component::Component(associated),
                                     hitpoints(30) {
}

void Face::Damage(int damage) {
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        Sound* sound = (Sound *)associated.GetComponent("Sound").get();
        if (sound != nullptr) sound->Play();

    }
}

void Face::Update(float delta_time) {
    int new_x = InputManager::GetInstance().GetMouseX() - Camera::pos.x;
    int new_y = InputManager::GetInstance().GetMouseY() - Camera::pos.y;
    
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        if (associated.box.Contains(new_x, new_y)) {
            int damage = rand() % 10 + 10;
            Damage(damage);
        }
    }
}

void Face::Render() {}

bool Face::Is(string type) {
    return type == "Face" ? true : false;
}
