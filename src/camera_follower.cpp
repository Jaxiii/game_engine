#include "../include/internal/camera_follower.hpp"
#include "../include/internal/camera.hpp"

CameraFollower::CameraFollower(GameObject& associated) : Component::Component(associated) {}

void CameraFollower::Update(float delta_time) {
    associated.box.x = -Camera::pos.x;
    associated.box.y = -Camera::pos.y;
}

void CameraFollower::Render(){}

bool CameraFollower::Is(std::string type) {
    return type == "CameraFollower" ? true : false;
}