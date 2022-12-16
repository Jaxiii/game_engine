#pragma once

#define MINION_SPRITE_PATH "assets/img/minion.png"
#define MINION_ANG_VEL -50
#define MINION_BULLET_SPEED 50.0
#define MINION_BULLET_DAMAGE 30.0
#define MINION_BULLET_SPRITE_PATH "assets/img/minionbullet1.png"

#include <iostream>
#include <memory>
#include <math.h>
#include "sprite.hpp"
#include "game_object.hpp"
#include "component.hpp"
#include "vec2.hpp"
#include "bullet.hpp"

using namespace std;

class Minion : public Component {
    public:
        Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
        void Update(float dt);
        void Render();
        bool Is(string type);
        void Shoot(Vec2 target);

    private:
        Vec2 radius;
        weak_ptr<GameObject> alienCenter;
        float arc;
};