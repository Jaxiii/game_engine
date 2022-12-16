#pragma once

#define BULLET_SPRITE_PATH "assets/img/minionbullet1"

#include <iostream>
#include "sprite.hpp"
#include "component.hpp"
#include "game_object.hpp"
#include "vec2.hpp"

class Bullet : public Component {
    public:
        Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite);
        void Update(float delta_time);
        void Render();
        bool Is(string type);
        int GetDamage();

    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
};