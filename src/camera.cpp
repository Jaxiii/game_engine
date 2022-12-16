#include "../include/internal/camera.hpp"
#include "../include/internal/input_manager.hpp"

GameObject* Camera::focus;

Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float delta_time) {

    if (focus == nullptr)  {
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
            speed.x = base_speed;
        } else {
            if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
                speed.x = (-1) * base_speed;
            } else {
                speed.x = 0;
            }   
        }
        
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_EY)) {
            speed.y = (-1) * base_speed;
        } else {
            if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
                speed.y = base_speed;
            } else {
                speed.y = 0;
            }
        }

        pos.x += delta_time * speed.x;
        pos.y += delta_time * speed.y;

    }
}