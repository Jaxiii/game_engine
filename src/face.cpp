#include "../include/internal/face.hpp"
#include "../include/internal/sound.hpp"

using namespace std;

Face::Face(GameObject &associated) : Component::Component(associated),
                                     hitpoints(30) {}

void Face::Damage(int damage) {
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        //Sound* sound = (Sound *)associated->GetComponent("Sound").get();
        //if (sound != nullptr) {
        //sound->Play();
        //}
    }
}

void Face::Update(float delta_time) {}

void Face::Render() {}

bool Face::Is(string type) {
    return (type == "Face") ? true : false;
}