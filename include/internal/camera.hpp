#pragma once

#include "game_object.hpp"
#include "vec2.hpp"

class Camera {

    public:
        static void Follow (GameObject* newFocus);
        static void Unfollow();
        static void Update(float delta_time);
        static Vec2 pos;
        static Vec2 speed;
        static const int base_speed = 100;

    private:
        static GameObject* focus;

};